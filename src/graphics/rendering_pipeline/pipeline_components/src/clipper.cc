#include "graphics/rendering_pipeline/pipeline_components/include/clipper.h"

#include <array>
#include <memory>
#include <vector>

#include "core/math/include/frustum.h"
#include "core/math/include/math_utils.h"
#include "core/math/include/vector3.h"
#include "core/math/include/vector4.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/line.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/point.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/primitive.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/transformed_vertex.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/triangle.h"

namespace ho_renderer {
Clipper::Clipper() = default;
Clipper::~Clipper() = default;

void ho_renderer::Clipper::ClipPoint(
    Point* p, std::vector<TransformedVertex>* v_buffer) const {
  if (p->is_outof_frustum()) {
    return;
  }
  Vector4 point_coord = (*v_buffer)[p->index0()].clip_coord();
  // check point is outof left, right plane
  if (point_coord.x() < -point_coord.w() || point_coord.x() > point_coord.w()) {
    p->set_is_outof_frustum(true);
    return;
  }
  // check point is outof top, bottom plane
  if (point_coord.y() < -point_coord.w() || point_coord.y() > point_coord.w()) {
    p->set_is_outof_frustum(true);
    return;
  }
  // check point is outof projection, far plane
  if (point_coord.z() < 0.f || point_coord.z() > point_coord.w()) {
    p->set_is_outof_frustum(true);
    return;
  }
}

void Clipper::ClipLine(Line* l,
                       std::vector<TransformedVertex>* v_buffer) const {
  std::array<Frustum::PlanePosition, 6> positions = {
      Frustum::PlanePosition::kLeft,   Frustum::PlanePosition::kRight,
      Frustum::PlanePosition::kBottom, Frustum::PlanePosition::kTop,
      Frustum::PlanePosition::kNear,   Frustum::PlanePosition::kFar};
  std::array<CoordinateState, 2> index_states;
  std::array<std::uint32_t, 2> i_buffer;
  int num_inside;
  for (auto itr = positions.cbegin(); itr != positions.cend(); itr++) {
    if (l->is_outof_frustum()) {
      break;
    }
    i_buffer[0] = l->index0();
    i_buffer[1] = l->index1();
    num_inside = 0;
    index_states[0] = CheckCoordinateState(
        (*v_buffer)[i_buffer[0]].clip_coord(), num_inside, *itr);
    index_states[1] = CheckCoordinateState(
        (*v_buffer)[i_buffer[1]].clip_coord(), num_inside, *itr);
    switch (num_inside) {
      // line is totally outside
      case 0:
        l->set_is_outof_frustum(true);
        break;
      case 1:
        ShrinkLine(l, v_buffer, index_states, i_buffer, *itr);
        l->set_is_outof_frustum(false);
        break;
      case 2:
        // line is totally inside
        l->set_is_outof_frustum(false);
    }
  }
}

std::vector<std::unique_ptr<Triangle>> Clipper::ClipTriangle(
    Triangle* t, std::vector<TransformedVertex>* v_buffer,
    IndexOrder order) const {
  std::vector<std::unique_ptr<Triangle>> t_buffer;
  t_buffer.push_back(std::make_unique<Triangle>(*t));
  t->set_is_outof_frustum(true);
  return std::move(ClipBufferedTriangle(std::move(t_buffer), v_buffer, order));
}

void ho_renderer::Clipper::ShrinkLine(
    Line* l, std::vector<TransformedVertex>* v_buffer,
    const std::array<CoordinateState, 2>& index_states,
    const std::array<std::uint32_t, 2>& i_buffer,
    Frustum::PlanePosition position) const {
  int inside_buf_index = (index_states[0] == kINSIDE) ? 0 : 1;
  int inside_index = i_buffer[inside_buf_index];
  int outside_index = i_buffer[(inside_buf_index + 1) % 2];

  // load inside/outside coords
  const TransformedVertex& inside_v = (*v_buffer)[inside_index];
  const TransformedVertex& outside_v = (*v_buffer)[outside_index];

  // calculate scalar
  float intersection_scalar =
      CalculateScalar(inside_v.clip_coord(), outside_v.clip_coord(), position);

  // if intersect_coord == outside_coord
  if (MathUtils::IsEqual(intersection_scalar, 1.f)) {
    intersection_scalar = 1.f - MathUtils::kEpsion;
  }
  if (MathUtils::IsEqual(intersection_scalar, 0.f)) {
    intersection_scalar = MathUtils::kEpsion;
  }
  // calculate intersected coords
  TransformedVertex intersected_v =
      AffineCombination(inside_v, outside_v, intersection_scalar);

  int intersect_index = v_buffer->size();
  // add coord to buffer
  v_buffer->push_back(intersected_v);
  // update line
  l->set_index0(inside_index).set_index1(intersect_index);
}

std::vector<std::unique_ptr<Triangle>> Clipper::ClipBufferedTriangle(
    std::vector<std::unique_ptr<Triangle>> t_buffer,
    std::vector<TransformedVertex>* v_buffer, IndexOrder order) const {
  std::array<Frustum::PlanePosition, 6> positions = {
      Frustum::PlanePosition::kLeft,   Frustum::PlanePosition::kRight,
      Frustum::PlanePosition::kBottom, Frustum::PlanePosition::kTop,
      Frustum::PlanePosition::kNear,   Frustum::PlanePosition::kFar};
  std::unique_ptr<Triangle> divided_part;
  std::array<CoordinateState, 3> index_states;
  std::array<std::uint32_t, 3> i_buffer;
  int num_inside;

  for (auto itr = positions.cbegin(); itr != positions.cend(); itr++) {
    std::uint32_t size = t_buffer.size();
    for (std::uint32_t i = 0; i < size; i++) {
      // if triangle is backface, don't need to proceed.
      if (t_buffer[i]->is_backface() || t_buffer[i]->is_outof_frustum()) {
        continue;
      }
      i_buffer[0] = t_buffer[i]->index0();
      i_buffer[1] = t_buffer[i]->index1();
      i_buffer[2] = t_buffer[i]->index2();
      num_inside = 0;
      index_states[0] = CheckCoordinateState(
          (*v_buffer)[i_buffer[0]].clip_coord(), num_inside, *itr);
      index_states[1] = CheckCoordinateState(
          (*v_buffer)[i_buffer[1]].clip_coord(), num_inside, *itr);
      index_states[2] = CheckCoordinateState(
          (*v_buffer)[i_buffer[2]].clip_coord(), num_inside, *itr);
      switch (num_inside) {
        case 0:
          // triangle is totally outside
          t_buffer[i]->set_is_outof_frustum(true);
          break;
        case 1:
          ShrinkTriangle(t_buffer[i].get(), v_buffer, order, index_states, i_buffer,
                         *itr);
          t_buffer[i]->set_is_outof_frustum(false);
          break;
        case 2:
          divided_part = DivideTriangle(t_buffer[i].get(), v_buffer, order,
                                        index_states, i_buffer, *itr);
          // make disable existing triangle
          t_buffer[i]->set_is_outof_frustum(false);
          divided_part->set_is_outof_frustum(false);
          t_buffer.push_back(std::move(divided_part));
          break;
        case 3:
          // triangle totally inside
          t_buffer[i]->set_is_outof_frustum(false);
          break;
      }
    }
  }
  return std::move(t_buffer);
}

void Clipper::ShrinkTriangle(Triangle* t,
                             std::vector<TransformedVertex>* v_buffer,
                             IndexOrder order,
                             const std::array<CoordinateState, 3>& index_states,
                             const std::array<std::uint32_t, 3>& i_buffer,
                             Frustum::PlanePosition position) const {
  int inside_buf_index =
      (index_states[0] == kINSIDE) ? 0 : ((index_states[1] == kINSIDE) ? 1 : 2);
  int inside_index = i_buffer[inside_buf_index];
  int outside_index1 = i_buffer[(inside_buf_index + 1) % 3];
  int outside_index2 = i_buffer[(inside_buf_index + 2) % 3];

  // load inside/outside coords
  const TransformedVertex& inside_vertex = (*v_buffer)[inside_index];
  const TransformedVertex& outside_vertex1 = (*v_buffer)[outside_index1];
  const TransformedVertex& outside_vertex2 = (*v_buffer)[outside_index2];

  // calculate scalar
  float intersection_scalar1 = CalculateScalar(
      inside_vertex.clip_coord(), outside_vertex1.clip_coord(), position);
  // if intersect_coord == outside_coord
  if (MathUtils::IsEqual(intersection_scalar1, 1.f)) {
    intersection_scalar1 = 1.f - MathUtils::kEpsion;
  }
  if (MathUtils::IsEqual(intersection_scalar1, 0.f)) {
    intersection_scalar1 = MathUtils::kEpsion;
  }
  float intersection_scalar2 = CalculateScalar(
      inside_vertex.clip_coord(), outside_vertex2.clip_coord(), position);
  // if intersect_coord == outside_coord
  if (MathUtils::IsEqual(intersection_scalar2, 1.f)) {
    intersection_scalar2 = 1.f - MathUtils::kEpsion;
  }
  if (MathUtils::IsEqual(intersection_scalar2, 0.f)) {
    intersection_scalar2 = MathUtils::kEpsion;
  }

  // shrank triangle by updating coord
  TransformedVertex intersected_vertex1 =
      AffineCombination(inside_vertex, outside_vertex1, intersection_scalar1);
  TransformedVertex intersected_vertex2 =
      AffineCombination(inside_vertex, outside_vertex2, intersection_scalar2);
  int intersect_index1 = v_buffer->size();
  int intersect_index2 = v_buffer->size() + 1;
  v_buffer->push_back(intersected_vertex1);
  v_buffer->push_back(intersected_vertex2);

  // update triangle
  t->set_index0(inside_index)
      .set_index1(intersect_index1)
      .set_index2(intersect_index2);
}

// DEBUG : modified index order
std::unique_ptr<Triangle> Clipper::DivideTriangle(
    Triangle* t, std::vector<TransformedVertex>* v_buffer, IndexOrder order,
    const std::array<CoordinateState, 3>& index_states,
    const std::array<std::uint32_t, 3>& i_buffer,
    Frustum::PlanePosition position) const {
  int outside_buf_index = (index_states[0] == kOUTSIDE)
                              ? 0
                              : ((index_states[1] == kOUTSIDE) ? 1 : 2);
  int outside_index = i_buffer[outside_buf_index];
  int inside_index1 = i_buffer[(outside_buf_index + 1) % 3];
  int inside_index2 = i_buffer[(outside_buf_index + 2) % 3];

  const TransformedVertex& outside_vertex = (*v_buffer)[outside_index];
  const TransformedVertex& inside_vertex1 = (*v_buffer)[inside_index1];
  const TransformedVertex& inside_vertex2 = (*v_buffer)[inside_index2];

  float intersection_scalar1 = CalculateScalar(
      outside_vertex.clip_coord(), inside_vertex1.clip_coord(), position);
  // if intersect_coord == outside_coord
  if (MathUtils::IsEqual(intersection_scalar1, 1.f)) {
    intersection_scalar1 = 1.f - MathUtils::kEpsion;
  }
  if (MathUtils::IsEqual(intersection_scalar1, 0.f)) {
    intersection_scalar1 = MathUtils::kEpsion;
  }
  float intersection_scalar2 = CalculateScalar(
      outside_vertex.clip_coord(), inside_vertex2.clip_coord(), position);
  // if intersect_coord == outside_coord
  if (MathUtils::IsEqual(intersection_scalar2, 1.f)) {
    intersection_scalar2 = 1.f - MathUtils::kEpsion;
  }
  if (MathUtils::IsEqual(intersection_scalar2, 0.f)) {
    intersection_scalar2 = MathUtils::kEpsion;
  }
  TransformedVertex intersected_coord1 =
      AffineCombination(outside_vertex, inside_vertex1, intersection_scalar1);
  TransformedVertex intersected_coord2 =
      AffineCombination(outside_vertex, inside_vertex2, intersection_scalar2);
  int intersect_index1 = v_buffer->size();
  int intersect_index2 = v_buffer->size() + 1;
  v_buffer->push_back(intersected_coord1);
  v_buffer->push_back(intersected_coord2);

  t->set_index0(inside_index1)
      .set_index1(inside_index2)
      .set_index2(intersect_index1);
  return std::make_unique<Triangle>(t->material(), intersect_index1,
                                    inside_index2, intersect_index2,
                                    t->normal(), t->center());
}

ho_renderer::Clipper::CoordinateState
ho_renderer::Clipper::CheckCoordinateState(
    const Vector4& coord, int& num_inside,
    Frustum::PlanePosition position) const {
  switch (position) {
    case Frustum::PlanePosition::kLeft:
      if (coord.x() < -coord.w()) {
        return kOUTSIDE;
      } else {
        num_inside++;
        return kINSIDE;
      }
      break;
    case Frustum::PlanePosition::kRight:
      if (coord.x() > coord.w()) {
        return kOUTSIDE;
      } else {
        num_inside++;
        return kINSIDE;
      }
      break;
    case Frustum::PlanePosition::kBottom:
      if (coord.y() < -coord.w()) {
        return kOUTSIDE;
      } else {
        num_inside++;
        return kINSIDE;
      }
      break;
    case Frustum::PlanePosition::kTop:
      if (coord.y() > coord.w()) {
        return kOUTSIDE;
      } else {
        num_inside++;
        return kINSIDE;
      }
      break;
    case Frustum::PlanePosition::kNear:
      if (coord.z() < -coord.w()) {
        return kOUTSIDE;
      } else {
        num_inside++;
        return kINSIDE;
      }
      break;
    case Frustum::PlanePosition::kFar:
      if (coord.z() > coord.w()) {
        return kOUTSIDE;
      } else {
        num_inside++;
        return kINSIDE;
      }
      break;
    case Frustum::PlanePosition::kProjection:
      if (coord.w() < 0.f) {
        return kOUTSIDE;
      } else {
        num_inside++;
        return kINSIDE;
      }
      break;
  }
}

// scalar s is used in affine combnination '(1-s)*Coordinate1 + s*Coordinate2'
float ho_renderer::Clipper::CalculateScalar(
    const Vector4& coord1, const Vector4& coord2,
    Frustum::PlanePosition position) const {
  float denominator;
  switch (position) {
    case Frustum::PlanePosition::kLeft:
      denominator = ((coord1.w() + coord1.x()) - (coord2.w() + coord2.x()));
      break;
    case Frustum::PlanePosition::kRight:
      denominator = ((coord1.w() - coord1.x()) - (coord2.w() - coord2.x()));
      break;
    case Frustum::PlanePosition::kBottom:
      denominator = ((coord1.w() + coord1.y()) - (coord2.w() + coord2.y()));
      break;
    case Frustum::PlanePosition::kTop:
      denominator = ((coord1.w() - coord1.y()) - (coord2.w() - coord2.y()));
      break;
    case Frustum::PlanePosition::kNear:
      denominator = ((coord1.w() + coord1.z()) - (coord2.w() + coord2.z()));
      break;
    case Frustum::PlanePosition::kFar:
      denominator = ((coord1.w() - coord1.z()) - (coord2.w() - coord2.z()));
      break;
    case Frustum::PlanePosition::kProjection:
      denominator = (coord1.w() - coord2.w());
      break;
  }
  if (MathUtils::IsEqual(denominator, 0.f)) {
    denominator = MathUtils::kFloatMin;
  }
  float numerator;
  switch (position) {
    case Frustum::PlanePosition::kLeft:
      numerator = (coord1.w() + coord1.x());
      break;
    case Frustum::PlanePosition::kRight:
      numerator = (coord1.w() - coord1.x());
      break;
    case Frustum::PlanePosition::kBottom:
      numerator = (coord1.w() + coord1.y());
      break;
    case Frustum::PlanePosition::kTop:
      numerator = (coord1.w() - coord1.y());
      break;
    case Frustum::PlanePosition::kNear:
      numerator = (coord1.w() + coord1.z());
      break;
    case Frustum::PlanePosition::kFar:
      numerator = (coord1.w() - coord1.z());
      break;
    case Frustum::PlanePosition::kProjection:
      numerator = coord1.w();
      break;
  }
  return numerator / denominator;
}
TransformedVertex Clipper::AffineCombination(const TransformedVertex& v1,
                                             const TransformedVertex& v2,
                                             const float scalar) const {
  return (1.f - scalar) * v1 + scalar * v2;
}
}  // namespace ho_renderer
