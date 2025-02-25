#include "rendering_pipeline/shaders/include/clipping_shader.h"

#include <array>
#include <cassert>
#include <memory>
#include <string>

#include "app/include/debug.h"
#include "asset/include/vertex.h"
#include "math/include/frustum.h"
#include "math/include/math_utils.h"
#include "rendering_pipeline/pipeline_objects/include/line.h"
#include "rendering_pipeline/pipeline_objects/include/point.h"
#include "rendering_pipeline/pipeline_objects/include/primitive.h"
#include "rendering_pipeline/pipeline_objects/include/triangle.h"

namespace ho_renderer {
ClippingShader::ClippingShader() = default;
ClippingShader::~ClippingShader() = default;

void ho_renderer::ClippingShader::ClipPointAgainstFrustum(
    std::vector<Vertex>& clip_coordinate_buffer,
    std::vector<Primitive*>& primitive_buffer) const {
  for (auto point_itr = primitive_buffer.begin();
       point_itr != primitive_buffer.end(); point_itr++) {
    Point& point = *(static_cast<Point*>(*point_itr));
    if (point.is_outof_frustum()) {
      continue;
    }
    Vector4 point_coordinate =
        clip_coordinate_buffer[point.index0()].coordinate();
    // check point is outof left, right plane
    if (point_coordinate.x() < -point_coordinate.w() ||
        point_coordinate.x() > point_coordinate.w()) {
      point.set_is_outof_frustum(true);
      continue;
    }
    // check point is outof top, bottom plane
    if (point_coordinate.y() < -point_coordinate.w() ||
        point_coordinate.y() > point_coordinate.w()) {
      point.set_is_outof_frustum(true);
      continue;
    }
    // check point is outof projection, far plane
    if (point_coordinate.z() < 0.f ||
        point_coordinate.z() > point_coordinate.w()) {
      point.set_is_outof_frustum(true);
      continue;
    }
  }
}

void ho_renderer::ClippingShader::ClipLineAgainstFrustum(
    std::vector<Vertex>& clip_coordinate_buffer,
    std::vector<Primitive*>& primitive_buffer) const {
  std::array<Frustum::PlanePosition, 6> plane_positions = {
      Frustum::PlanePosition::kLEFT,       Frustum::PlanePosition::kRIGHT,
      Frustum::PlanePosition::kBOTTOM,     Frustum::PlanePosition::kTOP,
      Frustum::PlanePosition::kPROJECTION, Frustum::PlanePosition::kFAR};
  std::array<CoordinateState, 2> index_states;
  std::array<int, 2> index_buffer;
  int num_inside;
  for (auto plane_position_itr = plane_positions.cbegin();
       plane_position_itr != plane_positions.cend(); plane_position_itr++) {
    for (int i = 0; i < primitive_buffer.size(); i++) {
      Line& line = *(static_cast<Line*>(primitive_buffer[i]));
      if (line.is_outof_frustum()) {
        continue;
      }
      index_buffer[0] = line.index0();
      index_buffer[1] = line.index1();
      num_inside = 0;
      index_states[0] = CheckCoordinateState(
          clip_coordinate_buffer[index_buffer[0]].coordinate(), num_inside,
          *plane_position_itr);
      index_states[1] = CheckCoordinateState(
          clip_coordinate_buffer[index_buffer[1]].coordinate(), num_inside,
          *plane_position_itr);
      switch (num_inside) {
        // line is totally outside
        case 0:
          line.set_is_outof_frustum(true);
          break;
        case 1:
          ShrinkLine(clip_coordinate_buffer, primitive_buffer, index_states,
                     index_buffer, *plane_position_itr, line.color_bit());
          line.set_is_outof_frustum(true);
          break;
        case 2:
          // line is totally inside
          line.set_is_outof_frustum(false);
      }
    }
  }
}

void ho_renderer::ClippingShader::ClipTriangleAgainstFrustum(
    std::vector<Vertex>& clip_coordinate_buffer,
    std::vector<Primitive*>& primitive_buffer) const {
  std::array<Frustum::PlanePosition, 6> plane_positions = {
      Frustum::PlanePosition::kLEFT,       Frustum::PlanePosition::kRIGHT,
      Frustum::PlanePosition::kBOTTOM,     Frustum::PlanePosition::kTOP,
      Frustum::PlanePosition::kPROJECTION, Frustum::PlanePosition::kFAR};
  std::array<CoordinateState, 3> index_states;
  std::array<int, 3> index_buffer;
  int num_inside;

  for (auto plane_position_itr = plane_positions.cbegin();
       plane_position_itr != plane_positions.cend(); plane_position_itr++) {
    // newly added triangle not considerd against same plane.
    uint32_t existing_size = primitive_buffer.size();
    for (int i = 0; i < existing_size; i++) {
      Triangle& triangle = *(static_cast<Triangle*>(primitive_buffer[i]));
      // if triangle is backface, don't need to process about it.
      if (triangle.is_backface() || triangle.is_outof_frustum()) {
        continue;
      }
      index_buffer[0] = triangle.index0();
      index_buffer[1] = triangle.index1();
      index_buffer[2] = triangle.index2();
      num_inside = 0;
      index_states[0] = CheckCoordinateState(
          clip_coordinate_buffer[index_buffer[0]].coordinate(), num_inside,
          *plane_position_itr);
      index_states[1] = CheckCoordinateState(
          clip_coordinate_buffer[index_buffer[1]].coordinate(), num_inside,
          *plane_position_itr);
      index_states[2] = CheckCoordinateState(
          clip_coordinate_buffer[index_buffer[2]].coordinate(), num_inside,
          *plane_position_itr);
      switch (num_inside) {
        case 0:
          // triangle is totally outside
          triangle.set_is_outof_frustum(true);
          break;
        case 1:
          ShrinkTriangle(clip_coordinate_buffer, primitive_buffer, index_states,
                         index_buffer, *plane_position_itr,
                         triangle.color_bit());
          triangle.set_is_outof_frustum(true);
          break;
        case 2:
          DivideTriangle(clip_coordinate_buffer, primitive_buffer, index_states,
                         index_buffer, *plane_position_itr,
                         triangle.color_bit());
          // make disable existing triangle
          triangle.set_is_outof_frustum(true);
          break;
        case 3:
          // triangle totally inside
          triangle.set_is_outof_frustum(false);
          break;
      }
    }
  }
}

void ho_renderer::ClippingShader::ShrinkLine(
    std::vector<Vertex>& clip_coordinate_buffer,
    std::vector<Primitive*>& primitive_buffer,
    const std::array<CoordinateState, 2>& index_states,
    std::array<int, 2>& index_buffer, Frustum::PlanePosition position,
    std::uint32_t primitive_color) const {
  int inside_buf_index = (index_states[0] == kINSIDE) ? 0 : 1;
  int inside_index = index_buffer[inside_buf_index];
  int outside_index = index_buffer[(inside_buf_index + 1) % 2];
  // load inside/outside coordinates
  const Vector4& inside_coordinate =
      clip_coordinate_buffer[inside_index].coordinate();
  const Vector4& outside_coordinate =
      clip_coordinate_buffer[outside_index].coordinate();

  // calculate scalar
  float intersection_scalar =
      CalculateScalar(inside_coordinate, outside_coordinate, position);
  // if intersect_coordinate == outside_coordinate
  if (MathUtils::IsEqual(intersection_scalar, 1.f)) {
    intersection_scalar = 1.f - MathUtils::kEPSILON;
  }
  if (MathUtils::IsEqual(intersection_scalar, 0.f)) {
    intersection_scalar = MathUtils::kEPSILON;
  }
  // calculate intersected coordinate
  Vector4 intersected_coordinate = AffineCombination(
      inside_coordinate, outside_coordinate, intersection_scalar);

  int intersect_index = clip_coordinate_buffer.size();
  // add coordinate to buffer
  clip_coordinate_buffer.push_back(intersected_coordinate);
  // add new line to buffer
  Line new_line = {intersect_index, inside_index, primitive_color};
  new_line.set_is_outof_frustum(false);
  primitive_buffer.emplace_back(new Line(new_line));
}

void ho_renderer::ClippingShader::ShrinkTriangle(
    std::vector<Vertex>& clip_coordinate_buffer,
    std::vector<Primitive*>& primitive_buffer,
    const std::array<CoordinateState, 3>& index_states,
    std::array<int, 3>& index_buffer, Frustum::PlanePosition position,
    std::uint32_t primitive_color) const {
  int inside_buf_index =
      (index_states[0] == kINSIDE) ? 0 : ((index_states[1] == kINSIDE) ? 1 : 2);
  int inside_index = index_buffer[inside_buf_index];
  int outside_index1 = index_buffer[(inside_buf_index + 1) % 3];
  int outside_index2 = index_buffer[(inside_buf_index + 2) % 3];
  // load inside/outside coordinates
  const Vector4& inside_coordinate =
      clip_coordinate_buffer[inside_index].coordinate();
  const Vector4& outside_coordinate1 =
      clip_coordinate_buffer[outside_index1].coordinate();
  const Vector4& outside_coordinate2 =
      clip_coordinate_buffer[outside_index2].coordinate();

  // calculate scalar
  float intersection_scalar1 =
      CalculateScalar(inside_coordinate, outside_coordinate1, position);
  // if intersect_coordinate == outside_coordinate
  if (MathUtils::IsEqual(intersection_scalar1, 1.f)) {
    intersection_scalar1 = 1.f - MathUtils::kEPSILON;
  }
  if (MathUtils::IsEqual(intersection_scalar1, 0.f)) {
    intersection_scalar1 = MathUtils::kEPSILON;
  }
  float intersection_scalar2 =
      CalculateScalar(inside_coordinate, outside_coordinate2, position);
  // if intersect_coordinate == outside_coordinate
  if (MathUtils::IsEqual(intersection_scalar2, 1.f)) {
    intersection_scalar2 = 1.f - MathUtils::kEPSILON;
  }
  if (MathUtils::IsEqual(intersection_scalar2, 0.f)) {
    intersection_scalar2 = MathUtils::kEPSILON;
  }
  // shrank triangle by updating coordinate
  Vector4 intersected_coordinate1 = AffineCombination(
      inside_coordinate, outside_coordinate1, intersection_scalar1);
  Vector4 intersected_coordinate2 = AffineCombination(
      inside_coordinate, outside_coordinate2, intersection_scalar2);
  int intersect_index1 = clip_coordinate_buffer.size();
  int intersect_index2 = clip_coordinate_buffer.size() + 1;
  clip_coordinate_buffer.push_back(intersected_coordinate1);
  clip_coordinate_buffer.push_back(intersected_coordinate2);

  Triangle new_triangle = {inside_index, intersect_index1, intersect_index2,
                           primitive_color};
  new_triangle.set_is_backface(false).set_is_outof_frustum(false);
  primitive_buffer.emplace_back(new Triangle(new_triangle));
}

// DEBUG : modified index order
void ho_renderer::ClippingShader::DivideTriangle(
    std::vector<Vertex>& clip_coordinate_buffer,
    std::vector<Primitive*>& primitive_buffer,
    const std::array<CoordinateState, 3>& index_states,
    std::array<int, 3>& index_buffer, Frustum::PlanePosition position,
    std::uint32_t primitive_color) const {
  int outside_buf_index = (index_states[0] == kOUTSIDE)
                              ? 0
                              : ((index_states[1] == kOUTSIDE) ? 1 : 2);
  int outside_index = index_buffer[outside_buf_index];
  int inside_index1 = index_buffer[(outside_buf_index + 1) % 3];
  int inside_index2 = index_buffer[(outside_buf_index + 2) % 3];

  const Vector4& outside_coordinate =
      clip_coordinate_buffer[outside_index].coordinate();
  const Vector4& inside_coordinate1 =
      clip_coordinate_buffer[inside_index1].coordinate();
  const Vector4& inside_coordinate2 =
      clip_coordinate_buffer[inside_index2].coordinate();

  float intersection_scalar1 =
      CalculateScalar(outside_coordinate, inside_coordinate1, position);
  // if intersect_coordinate == outside_coordinate
  if (MathUtils::IsEqual(intersection_scalar1, 1.f)) {
    intersection_scalar1 = 1.f - MathUtils::kEPSILON;
  }
  if (MathUtils::IsEqual(intersection_scalar1, 0.f)) {
    intersection_scalar1 = MathUtils::kEPSILON;
  }
  float intersection_scalar2 =
      CalculateScalar(outside_coordinate, inside_coordinate2, position);
  // if intersect_coordinate == outside_coordinate
  if (MathUtils::IsEqual(intersection_scalar2, 1.f)) {
    intersection_scalar2 = 1.f - MathUtils::kEPSILON;
  }
  if (MathUtils::IsEqual(intersection_scalar2, 0.f)) {
    intersection_scalar2 = MathUtils::kEPSILON;
  }
  Vector4 intersected_coordinate1 = AffineCombination(
      outside_coordinate, inside_coordinate1, intersection_scalar1);
  Vector4 intersected_coordinate2 = AffineCombination(
      outside_coordinate, inside_coordinate2, intersection_scalar2);
  int intersect_index1 = clip_coordinate_buffer.size();
  int intersect_index2 = clip_coordinate_buffer.size() + 1;
  clip_coordinate_buffer.push_back(intersected_coordinate1);
  clip_coordinate_buffer.push_back(intersected_coordinate2);

  Triangle new_triangle1 = {inside_index1, inside_index2, intersect_index1,
                            primitive_color};
  Triangle new_triangle2 = {intersect_index1, inside_index2, intersect_index2,
                            primitive_color};
  new_triangle1.set_is_backface(false).set_is_outof_frustum(false);
  new_triangle2.set_is_backface(false).set_is_outof_frustum(false);
  primitive_buffer.emplace_back(new Triangle(new_triangle1));
  primitive_buffer.emplace_back(new Triangle(new_triangle2));
}

ho_renderer::ClippingShader::CoordinateState
ho_renderer::ClippingShader::CheckCoordinateState(
    const Vector4& coordinate, int& num_inside,
    Frustum::PlanePosition position) const {
  switch (position) {
    case Frustum::PlanePosition::kLEFT:
      if (coordinate.x() < -coordinate.w()) {
        return kOUTSIDE;
      } else {
        num_inside++;
        return kINSIDE;
      }
      break;
    case Frustum::PlanePosition::kRIGHT:
      if (coordinate.x() > coordinate.w()) {
        return kOUTSIDE;
      } else {
        num_inside++;
        return kINSIDE;
      }
      break;
    case Frustum::PlanePosition::kBOTTOM:
      if (coordinate.y() < -coordinate.w()) {
        return kOUTSIDE;
      } else {
        num_inside++;
        return kINSIDE;
      }
      break;
    case Frustum::PlanePosition::kTOP:
      if (coordinate.y() > coordinate.w()) {
        return kOUTSIDE;
      } else {
        num_inside++;
        return kINSIDE;
      }
      break;
    case Frustum::PlanePosition::kNEAR:
      if (coordinate.z() < -coordinate.w()) {
        return kOUTSIDE;
      } else {
        num_inside++;
        return kINSIDE;
      }
      break;
    case Frustum::PlanePosition::kFAR:
      if (coordinate.z() > coordinate.w()) {
        return kOUTSIDE;
      } else {
        num_inside++;
        return kINSIDE;
      }
      break;
    case Frustum::PlanePosition::kPROJECTION:
      if (coordinate.w() < 0.f) {
        return kOUTSIDE;
      } else {
        num_inside++;
        return kINSIDE;
      }
      break;
  }
}

// scalar s is used in affine combnination '(1-s)*Coordinate1 + s*Coordinate2'
float ho_renderer::ClippingShader::CalculateScalar(
    const Vector4& coordinate1, const Vector4& coordinate2,
    Frustum::PlanePosition position) const {
  float denominator;
  switch (position) {
    case Frustum::PlanePosition::kLEFT:
      denominator = ((coordinate1.w() + coordinate1.x()) -
                     (coordinate2.w() + coordinate2.x()));
      break;
    case Frustum::PlanePosition::kRIGHT:
      denominator = ((coordinate1.w() - coordinate1.x()) -
                     (coordinate2.w() - coordinate2.x()));
      break;
    case Frustum::PlanePosition::kBOTTOM:
      denominator = ((coordinate1.w() + coordinate1.y()) -
                     (coordinate2.w() + coordinate2.y()));
      break;
    case Frustum::PlanePosition::kTOP:
      denominator = ((coordinate1.w() - coordinate1.y()) -
                     (coordinate2.w() - coordinate2.y()));
      break;
    case Frustum::PlanePosition::kNEAR:
      denominator = ((coordinate1.w() + coordinate1.z()) -
                     (coordinate2.w() + coordinate2.z()));
      break;
    case Frustum::PlanePosition::kFAR:
      denominator = ((coordinate1.w() - coordinate1.z()) -
                     (coordinate2.w() - coordinate2.z()));
      break;
    case Frustum::PlanePosition::kPROJECTION:
      denominator = (coordinate1.w() - coordinate2.w());
      break;
  }
  if (MathUtils::IsEqual(denominator, 0.f)) {
    denominator = MathUtils::kFLOAT_MIN;
  }
  float numerator;
  switch (position) {
    case Frustum::PlanePosition::kLEFT:
      numerator = (coordinate1.w() + coordinate1.x());
      break;
    case Frustum::PlanePosition::kRIGHT:
      numerator = (coordinate1.w() - coordinate1.x());
      break;
    case Frustum::PlanePosition::kBOTTOM:
      numerator = (coordinate1.w() + coordinate1.y());
      break;
    case Frustum::PlanePosition::kTOP:
      numerator = (coordinate1.w() - coordinate1.y());
      break;
    case Frustum::PlanePosition::kNEAR:
      numerator = (coordinate1.w() + coordinate1.z());
      break;
    case Frustum::PlanePosition::kFAR:
      numerator = (coordinate1.w() - coordinate1.z());
      break;
    case Frustum::PlanePosition::kPROJECTION:
      numerator = coordinate1.w();
      break;
  }
  return numerator / denominator;
}

ho_renderer::Vector4 ho_renderer::ClippingShader::AffineCombination(
    const Vector4 coordinate1, const Vector4 coordinate2,
    const float scalar) const {
  return (1.f - scalar) * coordinate1 + scalar * coordinate2;
}

}  // namespace ho_renderer