#include "rendering_pipeline/shaders/include/rasterizing_shader.h"

#include <cassert>
#include <memory>
#include <string>

#include "app/include/debug.h"
#include "math/include/interpolation_utils.h"
#include "math/include/math_utils.h"
#include "rendering_pipeline/pipeline/include/resources_manager.h"
#include "rendering_pipeline/pipeline_objects/include/edge_function.h"

namespace ho_renderer {
RasterizingShader::RasterizingShader() = default;
RasterizingShader::~RasterizingShader() = default;
// splicit one primitive
std::vector<Fragment>* RasterizingShader::RasterizePoint(
    const std::vector<Vertex>& vertex_buffer,
    const std::vector<Vector3>& transformed_coordinate_buffer,
    const Point& primitive) const {
  std::vector<Fragment>* fragment_buffer =
      ResourcesManager::AllocateFragmentBuffer();
  Vector3 transformed_coordinate =
      transformed_coordinate_buffer[primitive.index0()];
  Vector2 screen_coordinate =
      Vector2(transformed_coordinate.x(), transformed_coordinate.y());
  float depth = transformed_coordinate.z();
  Fragment new_fragment =
      Fragment(PrimitiveType::kPOINT, &primitive, screen_coordinate, depth);
  fragment_buffer->push_back(new_fragment);
  return fragment_buffer;
}

std::vector<Fragment>* RasterizingShader::RasterizeLineAffine(
    const std::vector<Vertex>& vertex_buffer,
    const std::vector<Vector3>& transformed_coordinate_buffer,
    const Line& primitive) const {
  std::vector<Fragment>* fragment_buffer =
      ResourcesManager::AllocateFragmentBuffer();

  Vector3 transformed_coordinate1 =
      transformed_coordinate_buffer[primitive.index0()];
  Vector3 transformed_coordinate2 =
      transformed_coordinate_buffer[primitive.index1()];

  Vector2 screen_coordinate1 =
      Vector2(transformed_coordinate1.x(), transformed_coordinate1.y());
  Vector2 screen_coordinate2 =
      Vector2(transformed_coordinate2.x(), transformed_coordinate2.y());
  // attributes
  float depth1 = transformed_coordinate_buffer[primitive.index0()].z();
  float depth2 = transformed_coordinate_buffer[primitive.index1()].z();

  int start_x = screen_coordinate1.x();
  int start_y = screen_coordinate1.y();
  int end_x = screen_coordinate2.x();
  int end_y = screen_coordinate2.y();
  int dx = MathUtils::Abs(end_x - start_x);
  int dy = MathUtils::Abs(end_y - start_y);
  int sx = (start_x < end_x) ? 1 : -1;
  int sy = (start_y < end_y) ? 1 : -1;
  int err = dx - dy;

  while (true) {
    Vector2 target_coordiante = Vector2(start_x, start_y);
    Vector2 barycentric = InterpolationUtils::GetPixelBarycentric(
        target_coordiante, screen_coordinate1, screen_coordinate2);
    float interpolated_depth =
        InterpolationUtils::InterpolateAffineLine(depth1, depth2, barycentric);
    Fragment new_fragment = Fragment(PrimitiveType::kLINE, &primitive,
                                     target_coordiante, interpolated_depth);
    fragment_buffer->push_back(new_fragment);

    if (start_x == end_x && start_y == end_y) break;

    int e2 = 2 * err;
    if (e2 > -dy) {
      err -= dy;
      start_x += sx;
    }
    if (e2 < dx) {
      err += dx;
      start_y += sy;
    }
  }
  return fragment_buffer;
}

std::vector<Fragment>* RasterizingShader::RasterizeTriangleAffine(
    const std::vector<Vertex>& vertex_buffer,
    const std::vector<Vector3>& transformed_coordinate_buffer,
    const Triangle& primitive) const {
  std::vector<Fragment>* fragment_buffer =
      ResourcesManager::AllocateFragmentBuffer();

  Vector3 transformed_coordinate1 =
      transformed_coordinate_buffer[primitive.index0()];
  Vector3 transformed_coordinate2 =
      transformed_coordinate_buffer[primitive.index1()];
  Vector3 transformed_coordinate3 =
      transformed_coordinate_buffer[primitive.index2()];

  Vector2 screen_coordinate1 =
      Vector2(transformed_coordinate1.x(), transformed_coordinate1.y());
  Vector2 screen_coordinate2 =
      Vector2(transformed_coordinate2.x(), transformed_coordinate2.y());
  Vector2 screen_coordinate3 =
      Vector2(transformed_coordinate3.x(), transformed_coordinate3.y());

  // attributes
  float depth1 = transformed_coordinate1.z();
  float depth2 = transformed_coordinate2.z();
  float depth3 = transformed_coordinate3.z();

  int min_x = MathUtils::Minf(screen_coordinate1.x(), screen_coordinate2.x(),
                              screen_coordinate3.x());
  int max_x = MathUtils::Maxf(screen_coordinate1.x(), screen_coordinate2.x(),
                              screen_coordinate3.x());
  int min_y = MathUtils::Minf(screen_coordinate1.y(), screen_coordinate2.y(),
                              screen_coordinate3.y());
  int max_y = MathUtils::Maxf(screen_coordinate1.y(), screen_coordinate2.y(),
                              screen_coordinate3.y());

  for (int y = min_y; y < max_y; y++) {
    for (int x = min_x; x < max_x; x++) {
      Vector2 target_coordiante = Vector2(x, y);
      Vector3 barycentric = InterpolationUtils::GetPixelBarycentric(
          target_coordiante, screen_coordinate1, screen_coordinate2,
          screen_coordinate3);
      // degenerate case
      if (MathUtils::IsFloatNaN(barycentric.x()) &&
          MathUtils::IsFloatNaN(barycentric.y()) &&
          MathUtils::IsFloatNaN(barycentric.z())) {
        return nullptr;
      }
      // if target_coordinate is outof triangle, continue.
      if (barycentric.x() < 0.f || barycentric.x() > 1.f ||
          barycentric.y() < 0.f || barycentric.y() > 1.f ||
          barycentric.z() < 0.f || barycentric.z() > 1.f) {
        continue;
      }
      float interpolated_depth = InterpolationUtils::InterpolateAffineTriangle(
          depth1, depth2, depth3, barycentric);
      Fragment new_fragment = Fragment(PrimitiveType::kTRIANGLE, &primitive,
                                       target_coordiante, interpolated_depth);
      fragment_buffer->push_back(new_fragment);
    }
  }
  return fragment_buffer;
}
std::vector<Fragment>* RasterizingShader::EdgeFunctionRasterizeTriangleAffine(
    const std::vector<Vertex>& vertex_buffer,
    const std::vector<Vector3>& transformed_coordinate_buffer,
    const Triangle& primitive) const {
  std::vector<Fragment>* fragment_buffer =
      ResourcesManager::AllocateFragmentBuffer();

  Vector3 transformed_coordinate1 =
      transformed_coordinate_buffer[primitive.index0()];
  Vector3 transformed_coordinate2 =
      transformed_coordinate_buffer[primitive.index1()];
  Vector3 transformed_coordinate3 =
      transformed_coordinate_buffer[primitive.index2()];

  Vector2 screen_coordinate1 =
      Vector2(transformed_coordinate1.x(), transformed_coordinate1.y());
  Vector2 screen_coordinate2 =
      Vector2(transformed_coordinate2.x(), transformed_coordinate2.y());
  Vector2 screen_coordinate3 =
      Vector2(transformed_coordinate3.x(), transformed_coordinate3.y());

  // attributes
  float depth1 = transformed_coordinate1.z();
  float depth2 = transformed_coordinate2.z();
  float depth3 = transformed_coordinate3.z();

  int min_x = MathUtils::Minf(screen_coordinate1.x(), screen_coordinate2.x(),
                              screen_coordinate3.x());
  int max_x = MathUtils::Maxf(screen_coordinate1.x(), screen_coordinate2.x(),
                              screen_coordinate3.x());
  int min_y = MathUtils::Minf(screen_coordinate1.y(), screen_coordinate2.y(),
                              screen_coordinate3.y());
  int max_y = MathUtils::Maxf(screen_coordinate1.y(), screen_coordinate2.y(),
                              screen_coordinate3.y());
  // edge functions
  EdgeFunction f12(screen_coordinate1, screen_coordinate2,
                   Vector2(min_x, min_y));
  EdgeFunction f23(screen_coordinate2, screen_coordinate3,
                   Vector2(min_x, min_y));
  EdgeFunction f31(screen_coordinate3, screen_coordinate1,
                   Vector2(min_x, min_y));

  float area = f12.dx() * screen_coordinate3.x() +
               f12.dy() * screen_coordinate3.y() +
               (screen_coordinate2.x() * screen_coordinate1.y() -
                screen_coordinate1.x() * screen_coordinate2.y());
  // degenerate case
  if (MathUtils::IsEqual(area, 0.f)) {
    return nullptr;
  }
  float inv_area = 1.f / area;
  int f12_init = f12.initial_value();
  int f23_init = f23.initial_value();
  int f31_init = f31.initial_value();
  for (int y = min_y; y < max_y; y++) {
    int f12_ev = f12_init;
    int f23_ev = f23_init;
    int f31_ev = f31_init;
    for (int x = min_x; x < max_x; x++) {
      if (f12_ev >= 0 && f23_ev >= 0 && f31_ev >= 0) {
        Vector3 barycentric(f23_ev * inv_area, f31_ev * inv_area,
                            f12_ev * inv_area);
        float interpolated_depth =
            InterpolationUtils::InterpolateAffineTriangle(depth1, depth2,
                                                          depth3, barycentric);
        Fragment new_fragment = Fragment(PrimitiveType::kTRIANGLE, &primitive,
                                         Vector2(x, y), interpolated_depth);
        fragment_buffer->push_back(new_fragment);
      }
      f12_ev += f12.dx();
      f23_ev += f23.dx();
      f31_ev += f31.dx();
    }
    f12_init += f12.dy();
    f23_init += f23.dy();
    f31_init += f31.dy();
  }
  return fragment_buffer;
}
std::vector<Fragment>* RasterizingShader::RasterizeWireTriangleAffine(
    const std::vector<Vertex>& vertex_buffer,
    const std::vector<Vector3>& transformed_coordinate_buffer,
    const Triangle& primitive) const {
  std::vector<Fragment> fragment_buffer;
  Line wire1 =
      Line(primitive.index0(), primitive.index1(), primitive.color_bit());
  Line wire2 =
      Line(primitive.index1(), primitive.index2(), primitive.color_bit());
  Line wire3 =
      Line(primitive.index0(), primitive.index2(), primitive.color_bit());
  std::vector<Fragment>* wire_fragment_buffer;
  wire_fragment_buffer =
      RasterizeLineAffine(vertex_buffer, transformed_coordinate_buffer, wire1);
  if (wire_fragment_buffer != nullptr) {
    fragment_buffer.insert(fragment_buffer.end(), wire_fragment_buffer->begin(),
                           wire_fragment_buffer->end());
    ResourcesManager::DeallocateFragmentBuffer();
  }
  wire_fragment_buffer =
      RasterizeLineAffine(vertex_buffer, transformed_coordinate_buffer, wire2);
  if (wire_fragment_buffer != nullptr) {
    fragment_buffer.insert(fragment_buffer.end(), wire_fragment_buffer->begin(),
                           wire_fragment_buffer->end());
    ResourcesManager::DeallocateFragmentBuffer();
  }
  wire_fragment_buffer =
      RasterizeLineAffine(vertex_buffer, transformed_coordinate_buffer, wire3);
  if (wire_fragment_buffer != nullptr) {
    fragment_buffer.insert(fragment_buffer.end(), wire_fragment_buffer->begin(),
                           wire_fragment_buffer->end());
    ResourcesManager::DeallocateFragmentBuffer();
  }
  std::vector<Fragment>* output_fragment_buffer =
      ResourcesManager::AllocateFragmentBuffer();
  *output_fragment_buffer = fragment_buffer;
  return output_fragment_buffer;
}

std::vector<Fragment>* RasterizingShader::RasterizeLinePerspective(
    const std::vector<Vertex>& vertex_buffer,
    const std::vector<Vector3>& transformed_coordinate_buffer,
    const Line& primitive) const {
  std::vector<Fragment>* fragment_buffer =
      ResourcesManager::AllocateFragmentBuffer();
  Vector3 transformed_coordinate1 =
      transformed_coordinate_buffer[primitive.index0()];
  Vector3 transformed_coordinate2 =
      transformed_coordinate_buffer[primitive.index1()];

  Vector2 screen_coordinate1 =
      Vector2(transformed_coordinate1.x(), transformed_coordinate1.y());
  Vector2 screen_coordinate2 =
      Vector2(transformed_coordinate2.x(), transformed_coordinate2.y());

  // value for perspective correct interpolation
  float w1 = vertex_buffer[primitive.index0()].coordinate().w();
  if (MathUtils::IsEqual(w1, 0.f)) {
    w1 = MathUtils::kFLOAT_MIN;
  }
  float w2 = vertex_buffer[primitive.index1()].coordinate().w();
  if (MathUtils::IsEqual(w2, 0.f)) {
    w2 = MathUtils::kFLOAT_MIN;
  }
  float inv_w1 = 1.f / w1;
  float inv_w2 = 1.f / w2;
  Vector2 inv_w = Vector2(inv_w1, inv_w2);

  // attributes
  float depth1 = transformed_coordinate_buffer[primitive.index0()].z();
  float depth2 = transformed_coordinate_buffer[primitive.index1()].z();

  // set component for bresenham algorithm
  int start_x = screen_coordinate1.x();
  int start_y = screen_coordinate1.y();
  int end_x = screen_coordinate2.x();
  int end_y = screen_coordinate2.y();
  int dx = MathUtils::Abs(end_x - start_x);
  int dy = MathUtils::Abs(end_y - start_y);
  int sx = (start_x < end_x) ? 1 : -1;
  int sy = (start_y < end_y) ? 1 : -1;
  int err = dx - dy;

  while (true) {
    // create fragment
    Vector2 target_coordiante = Vector2(start_x, start_y);
    Vector2 barycentric = InterpolationUtils::GetPixelBarycentric(
        target_coordiante, screen_coordinate1, screen_coordinate2);
    float interpolated_w =
        InterpolationUtils::InterpolateWPerspectiveCorrectLine(inv_w,
                                                               barycentric);
    float interpolated_depth =
        1.f / InterpolationUtils::InterpolatePerspectiveCorrectLine(
                  depth1, depth2, barycentric, inv_w, interpolated_w);
    Fragment new_fragment = Fragment(PrimitiveType::kLINE, &primitive,
                                     target_coordiante, interpolated_depth);
    fragment_buffer->push_back(new_fragment);

    if (start_x == end_x && start_y == end_y) break;

    int e2 = 2 * err;
    if (e2 > -dy) {
      err -= dy;
      start_x += sx;
    }
    if (e2 < dx) {
      err += dx;
      start_y += sy;
    }
  }
  return fragment_buffer;
}
std::vector<Fragment>* RasterizingShader::RasterizeTrianglePerspective(
    const std::vector<Vertex>& vertex_buffer,
    const std::vector<Vector3>& transformed_coordinate_buffer,
    const Triangle& primitive) const {
  std::vector<Fragment>* fragment_buffer =
      ResourcesManager::AllocateFragmentBuffer();

  Vector3 transformed_coordinate1 =
      transformed_coordinate_buffer[primitive.index0()];
  Vector3 transformed_coordinate2 =
      transformed_coordinate_buffer[primitive.index1()];
  Vector3 transformed_coordinate3 =
      transformed_coordinate_buffer[primitive.index2()];

  Vector2 screen_coordinate1 =
      Vector2(transformed_coordinate1.x(), transformed_coordinate1.y());
  Vector2 screen_coordinate2 =
      Vector2(transformed_coordinate2.x(), transformed_coordinate2.y());
  Vector2 screen_coordinate3 =
      Vector2(transformed_coordinate3.x(), transformed_coordinate3.y());

  // value for perspective correct interpolation
  float w1 = vertex_buffer[primitive.index0()].coordinate().w();
  if (MathUtils::IsEqual(w1, 0.f)) {
    w1 = MathUtils::kFLOAT_MIN;
  }
  float w2 = vertex_buffer[primitive.index1()].coordinate().w();
  if (MathUtils::IsEqual(w2, 0.f)) {
    w2 = MathUtils::kFLOAT_MIN;
  }
  float w3 = vertex_buffer[primitive.index2()].coordinate().w();
  if (MathUtils::IsEqual(w3, 0.f)) {
    w3 = MathUtils::kFLOAT_MIN;
  }
  float inv_w1 = 1.f / w1;
  float inv_w2 = 1.f / w2;
  float inv_w3 = 1.f / w3;
  Vector3 inv_w = Vector3(inv_w1, inv_w2, inv_w3);

  // attributes
  float depth1 = transformed_coordinate1.z();
  float depth2 = transformed_coordinate2.z();
  float depth3 = transformed_coordinate3.z();

  int min_x = MathUtils::Minf(screen_coordinate1.x(), screen_coordinate2.x(),
                              screen_coordinate3.x());
  int max_x = MathUtils::Maxf(screen_coordinate1.x(), screen_coordinate2.x(),
                              screen_coordinate3.x());
  int min_y = MathUtils::Minf(screen_coordinate1.y(), screen_coordinate2.y(),
                              screen_coordinate3.y());
  int max_y = MathUtils::Maxf(screen_coordinate1.y(), screen_coordinate2.y(),
                              screen_coordinate3.y());

  for (int y = min_y; y < max_y; y++) {
    for (int x = min_x; x < max_x; x++) {
      Vector2 target_coordiante = Vector2(x, y);
      Vector3 barycentric = InterpolationUtils::GetPixelBarycentric(
          target_coordiante, screen_coordinate1, screen_coordinate2,
          screen_coordinate3);
      // degenerate case
      if (MathUtils::IsFloatNaN(barycentric.x()) &&
          MathUtils::IsFloatNaN(barycentric.y()) &&
          MathUtils::IsFloatNaN(barycentric.z())) {
        return nullptr;
      }
      // if target_coordinate is outof triangle, continue.
      if (barycentric.x() < 0.f || barycentric.x() > 1.f ||
          barycentric.y() < 0.f || barycentric.y() > 1.f ||
          barycentric.z() < 0.f || barycentric.z() > 1.f) {
        continue;
      }
      float interpolated_w =
          InterpolationUtils::InterpolateWPerspectiveCorrectTriangle(
              inv_w, barycentric);
      float interpolated_depth =
          1.f / InterpolationUtils::InterpolatePerspectiveCorrectTriangle(
                    depth1, depth2, depth3, barycentric, inv_w, interpolated_w);
      Fragment new_fragment = Fragment(PrimitiveType::kTRIANGLE, &primitive,
                                       target_coordiante, interpolated_depth);
      fragment_buffer->push_back(new_fragment);
    }
  }
  return fragment_buffer;
}
std::vector<Fragment>*
RasterizingShader::EdgeFunctionRasterizeTrianglePerspective(
    const std::vector<Vertex>& vertex_buffer,
    const std::vector<Vector3>& transformed_coordinate_buffer,
    const Triangle& primitive) const {
  std::vector<Fragment>* fragment_buffer =
      ResourcesManager::AllocateFragmentBuffer();

  Vector3 transformed_coordinate1 =
      transformed_coordinate_buffer[primitive.index0()];
  Vector3 transformed_coordinate2 =
      transformed_coordinate_buffer[primitive.index1()];
  Vector3 transformed_coordinate3 =
      transformed_coordinate_buffer[primitive.index2()];

  Vector2 screen_coordinate1 =
      Vector2(transformed_coordinate1.x(), transformed_coordinate1.y());
  Vector2 screen_coordinate2 =
      Vector2(transformed_coordinate2.x(), transformed_coordinate2.y());
  Vector2 screen_coordinate3 =
      Vector2(transformed_coordinate3.x(), transformed_coordinate3.y());
  // value for perspective correct interpolation
  float w1 = vertex_buffer[primitive.index0()].coordinate().w();
  if (MathUtils::IsEqual(w1, 0.f)) {
    w1 = MathUtils::kFLOAT_MIN;
  }
  float w2 = vertex_buffer[primitive.index1()].coordinate().w();
  if (MathUtils::IsEqual(w2, 0.f)) {
    w2 = MathUtils::kFLOAT_MIN;
  }
  float w3 = vertex_buffer[primitive.index2()].coordinate().w();
  if (MathUtils::IsEqual(w3, 0.f)) {
    w3 = MathUtils::kFLOAT_MIN;
  }
  float inv_w1 = 1.f / w1;
  float inv_w2 = 1.f / w2;
  float inv_w3 = 1.f / w3;
  Vector3 inv_w = Vector3(inv_w1, inv_w2, inv_w3);
  // attributes
  float depth1 = transformed_coordinate1.z();
  float depth2 = transformed_coordinate2.z();
  float depth3 = transformed_coordinate3.z();

  int min_x = MathUtils::Minf(screen_coordinate1.x(), screen_coordinate2.x(),
                              screen_coordinate3.x());
  int max_x = MathUtils::Maxf(screen_coordinate1.x(), screen_coordinate2.x(),
                              screen_coordinate3.x());
  int min_y = MathUtils::Minf(screen_coordinate1.y(), screen_coordinate2.y(),
                              screen_coordinate3.y());
  int max_y = MathUtils::Maxf(screen_coordinate1.y(), screen_coordinate2.y(),
                              screen_coordinate3.y());
  // edge functions
  EdgeFunction f12(screen_coordinate1, screen_coordinate2,
                   Vector2(min_x, min_y));
  EdgeFunction f23(screen_coordinate2, screen_coordinate3,
                   Vector2(min_x, min_y));
  EdgeFunction f31(screen_coordinate3, screen_coordinate1,
                   Vector2(min_x, min_y));

  float area = f12.dx() * screen_coordinate3.x() +
               f12.dy() * screen_coordinate3.y() +
               (screen_coordinate2.x() * screen_coordinate1.y() -
                screen_coordinate1.x() * screen_coordinate2.y());
  // degenerate case
  if (MathUtils::IsEqual(area, 0.f)) {
    return nullptr;
  }
  float inv_area = 1.f / area;
  int f12_init = f12.initial_value();
  int f23_init = f23.initial_value();
  int f31_init = f31.initial_value();
  for (int y = min_y; y < max_y; y++) {
    int f12_ev = f12_init;
    int f23_ev = f23_init;
    int f31_ev = f31_init;
    for (int x = min_x; x < max_x; x++) {
      if (f12_ev >= 0 && f23_ev >= 0 && f31_ev >= 0) {
        Vector3 barycentric(f23_ev * inv_area, f31_ev * inv_area,
                            f12_ev * inv_area);
        float interpolated_w =
            InterpolationUtils::InterpolateWPerspectiveCorrectTriangle(
                inv_w, barycentric);
        float interpolated_depth =
            1.f /
            InterpolationUtils::InterpolatePerspectiveCorrectTriangle(
                depth1, depth2, depth3, barycentric, inv_w, interpolated_w);
        Fragment new_fragment = Fragment(PrimitiveType::kTRIANGLE, &primitive,
                                         Vector2(x, y), interpolated_depth);
        fragment_buffer->push_back(new_fragment);
      }
      f12_ev += f12.dx();
      f23_ev += f23.dx();
      f31_ev += f31.dx();
    }
    f12_init += f12.dy();
    f23_init += f23.dy();
    f31_init += f31.dy();
  }
  return fragment_buffer;
}
std::vector<ho_renderer::Fragment>*

RasterizingShader::RasterizeWireTrianglePerspective(
    const std::vector<Vertex>& vertex_buffer,
    const std::vector<Vector3>& transformed_coordinate_buffer,
    const Triangle& primitive) const {
  std::vector<Fragment> fragment_buffer;
  Line wire1 =
      Line(primitive.index0(), primitive.index1(), primitive.color_bit());
  Line wire2 =
      Line(primitive.index1(), primitive.index2(), primitive.color_bit());
  Line wire3 =
      Line(primitive.index2(), primitive.index0(), primitive.color_bit());
  std::vector<Fragment>* wire_fragment_buffer;
  wire_fragment_buffer =
      RasterizeLineAffine(vertex_buffer, transformed_coordinate_buffer, wire1);
  if (wire_fragment_buffer != nullptr) {
    fragment_buffer.insert(fragment_buffer.end(), wire_fragment_buffer->begin(),
                           wire_fragment_buffer->end());
    ResourcesManager::DeallocateFragmentBuffer();
  }
  wire_fragment_buffer =
      RasterizeLineAffine(vertex_buffer, transformed_coordinate_buffer, wire2);
  if (wire_fragment_buffer != nullptr) {
    fragment_buffer.insert(fragment_buffer.end(), wire_fragment_buffer->begin(),
                           wire_fragment_buffer->end());
    ResourcesManager::DeallocateFragmentBuffer();
  }
  wire_fragment_buffer =
      RasterizeLineAffine(vertex_buffer, transformed_coordinate_buffer, wire3);
  if (wire_fragment_buffer != nullptr) {
    fragment_buffer.insert(fragment_buffer.end(), wire_fragment_buffer->begin(),
                           wire_fragment_buffer->end());
    ResourcesManager::DeallocateFragmentBuffer();
  }
  std::vector<Fragment>* output_fragment_buffer =
      ResourcesManager::AllocateFragmentBuffer();
  *output_fragment_buffer = fragment_buffer;
  return output_fragment_buffer;
}
}  // namespace ho_renderer