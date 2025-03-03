#include "rendering_pipeline/shaders/include/rasterizing_shader.h"

#include <cassert>
#include <memory>
#include <string>

#include "app/include/debug.h"
#include "math/include/interpolation_utils.h"
#include "math/include/math_utils.h"
#include "rendering_pipeline/pipeline/include/resources_manager.h"
#include "rendering_pipeline/pipeline_objects/include/edge_function.h"
#include "rendering_pipeline/pipeline_objects/include/frame_buffer.h"

namespace ho_renderer {
RasterizingShader::RasterizingShader() = default;
RasterizingShader::~RasterizingShader() = default;
// splicit one primitive
std::vector<Fragment>* RasterizingShader::RasterizePoint(
    const FrameBuffer& frame_buffer, const std::vector<Vertex>& vertex_buffer,
    const std::vector<Vector3>& view_coordinate_buffer,
    const std::vector<Vector3>& viewport_ndc_buffer,
    const Point& primitive) const {
  std::vector<Fragment>* fragment_buffer =
      ResourcesManager::GetClearFragmentBuffer();
  const Vector3& view_coordinate = view_coordinate_buffer[primitive.index0()];
  const Vector3& viewport_ndc = viewport_ndc_buffer[primitive.index0()];
  const Vector2& screen_coordinate =
      Vector2(viewport_ndc.x(), viewport_ndc.y());
  float depth = viewport_ndc.z();
  const Fragment& new_fragment =
      Fragment(PrimitiveType::kPOINT, &primitive, view_coordinate,
               screen_coordinate, depth);
  fragment_buffer->push_back(new_fragment);
  return fragment_buffer;
}

std::vector<Fragment>* RasterizingShader::RasterizeLineAffine(
    const FrameBuffer& frame_buffer, const std::vector<Vertex>& vertex_buffer,
    const std::vector<Vector3>& view_coordinate_buffer,
    const std::vector<Vector3>& viewport_ndc_buffer,
    const Line& primitive) const {
  std::vector<Fragment>* fragment_buffer =
      ResourcesManager::GetClearFragmentBuffer();

  const Vector3& view_coordinate1 = view_coordinate_buffer[primitive.index0()];
  const Vector3& view_coordinate2 = view_coordinate_buffer[primitive.index1()];
  const Vector3& viewport_ndc1 = viewport_ndc_buffer[primitive.index0()];
  const Vector3& viewport_ndc2 = viewport_ndc_buffer[primitive.index1()];

  const Vector2& screen_coordinate1 =
      Vector2(viewport_ndc1.x(), viewport_ndc1.y());
  const Vector2& screen_coordinate2 =
      Vector2(viewport_ndc2.x(), viewport_ndc2.y());
  // attributes
  float depth1 = viewport_ndc1.z();
  float depth2 = viewport_ndc2.z();

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
    const Vector2& target_coordiante = Vector2(start_x, start_y);
    const Vector2& barycentric = InterpolationUtils::GetPixelBarycentric(
        target_coordiante, screen_coordinate1, screen_coordinate2);
    // degenerate case
    if (MathUtils::IsFloatNaN(barycentric.x()) &&
        MathUtils::IsFloatNaN(barycentric.y())) {
      return nullptr;
    }
    const Vector3& view_coordinate = InterpolationUtils::InterpolateAffineLine(
        view_coordinate1, view_coordinate2, barycentric);
    float interpolated_depth =
        InterpolationUtils::InterpolateAffineLine(depth1, depth2, barycentric);
    if (frame_buffer.GetDepthBuffer().GetDepth(target_coordiante.x(),
                                               target_coordiante.y()) >
        interpolated_depth) {
      const Fragment& new_fragment =
          Fragment(PrimitiveType::kLINE, &primitive, view_coordinate,
                   target_coordiante, interpolated_depth);
      fragment_buffer->push_back(new_fragment);
    }
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
    const FrameBuffer& frame_buffer, const std::vector<Vertex>& vertex_buffer,
    const std::vector<Vector3>& view_coordinate_buffer,
    const std::vector<Vector3>& viewport_ndc_buffer,
    const Triangle& primitive) const {
  std::vector<Fragment>* fragment_buffer =
      ResourcesManager::GetClearFragmentBuffer();

  const Vector3& view_coordinate1 = view_coordinate_buffer[primitive.index0()];
  const Vector3& view_coordinate2 = view_coordinate_buffer[primitive.index1()];
  const Vector3& view_coordinate3 = view_coordinate_buffer[primitive.index2()];
  const Vector3& viewport_ndc1 = viewport_ndc_buffer[primitive.index0()];
  const Vector3& viewport_ndc2 = viewport_ndc_buffer[primitive.index1()];
  const Vector3& viewport_ndc3 = viewport_ndc_buffer[primitive.index2()];

  const Vector2& screen_coordinate1 =
      Vector2(viewport_ndc1.x(), viewport_ndc1.y());
  const Vector2& screen_coordinate2 =
      Vector2(viewport_ndc2.x(), viewport_ndc2.y());
  const Vector2& screen_coordinate3 =
      Vector2(viewport_ndc3.x(), viewport_ndc3.y());
  // attributes
  float depth1 = viewport_ndc1.z();
  float depth2 = viewport_ndc2.z();
  float depth3 = viewport_ndc3.z();

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
      const Vector2& target_coordiante = Vector2(x, y);
      const Vector3& barycentric = InterpolationUtils::GetPixelBarycentric(
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
      const Vector3& view_coordinate =
          InterpolationUtils::InterpolateAffineTriangle(
              view_coordinate1, view_coordinate2, view_coordinate3,
              barycentric);
      float interpolated_depth = InterpolationUtils::InterpolateAffineTriangle(
          depth1, depth2, depth3, barycentric);
      if (frame_buffer.GetDepthBuffer().GetDepth(target_coordiante.x(),
                                                 target_coordiante.y()) >
          interpolated_depth) {
        const Fragment& new_fragment =
            Fragment(PrimitiveType::kTRIANGLE, &primitive, view_coordinate,
                     target_coordiante, interpolated_depth);
        fragment_buffer->push_back(new_fragment);
      }
    }
  }
  return fragment_buffer;
}
std::vector<Fragment>* RasterizingShader::EdgeFunctionRasterizeTriangleAffine(
    const FrameBuffer& frame_buffer, const std::vector<Vertex>& vertex_buffer,
    const std::vector<Vector3>& view_coordinate_buffer,
    const std::vector<Vector3>& viewport_ndc_buffer,
    const Triangle& primitive) const {
  std::vector<Fragment>* fragment_buffer =
      ResourcesManager::GetClearFragmentBuffer();

  const Vector3& view_coordinate1 = view_coordinate_buffer[primitive.index0()];
  const Vector3& view_coordinate2 = view_coordinate_buffer[primitive.index1()];
  const Vector3& view_coordinate3 = view_coordinate_buffer[primitive.index2()];
  const Vector3& viewport_ndc1 = viewport_ndc_buffer[primitive.index0()];
  const Vector3& viewport_ndc2 = viewport_ndc_buffer[primitive.index1()];
  const Vector3& viewport_ndc3 = viewport_ndc_buffer[primitive.index2()];

  const Vector2& screen_coordinate1 =
      Vector2(viewport_ndc1.x(), viewport_ndc1.y());
  const Vector2& screen_coordinate2 =
      Vector2(viewport_ndc2.x(), viewport_ndc2.y());
  const Vector2& screen_coordinate3 =
      Vector2(viewport_ndc3.x(), viewport_ndc3.y());
  // attributes
  float depth1 = viewport_ndc1.z();
  float depth2 = viewport_ndc2.z();
  float depth3 = viewport_ndc3.z();

  int min_x = MathUtils::Minf(screen_coordinate1.x(), screen_coordinate2.x(),
                              screen_coordinate3.x());
  int max_x = MathUtils::Maxf(screen_coordinate1.x(), screen_coordinate2.x(),
                              screen_coordinate3.x());
  int min_y = MathUtils::Minf(screen_coordinate1.y(), screen_coordinate2.y(),
                              screen_coordinate3.y());
  int max_y = MathUtils::Maxf(screen_coordinate1.y(), screen_coordinate2.y(),
                              screen_coordinate3.y());
  // edge functions
  const EdgeFunction f12(screen_coordinate1, screen_coordinate2,
                         Vector2(min_x, min_y));
  const EdgeFunction f23(screen_coordinate2, screen_coordinate3,
                         Vector2(min_x, min_y));
  const EdgeFunction f31(screen_coordinate3, screen_coordinate1,
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
        const Vector3& view_coordinate =
            InterpolationUtils::InterpolateAffineTriangle(
                view_coordinate1, view_coordinate2, view_coordinate3,
                barycentric);
        float interpolated_depth =
            InterpolationUtils::InterpolateAffineTriangle(depth1, depth2,
                                                          depth3, barycentric);
        if (frame_buffer.GetDepthBuffer().GetDepth(x, y) > interpolated_depth) {
          const Fragment& new_fragment =
              Fragment(PrimitiveType::kTRIANGLE, &primitive, view_coordinate,
                       Vector2(x, y), interpolated_depth);
          fragment_buffer->push_back(new_fragment);
        }
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
    const FrameBuffer& frame_buffer, const std::vector<Vertex>& vertex_buffer,
    const std::vector<Vector3>& view_coordinate_buffer,
    const std::vector<Vector3>& viewport_ndc_buffer,
    const Triangle& primitive) const {
  std::vector<Fragment> fragment_buffer;
  const Line& wire1 =
      Line(primitive.index0(), primitive.index1(), primitive.color());
  const Line& wire2 =
      Line(primitive.index1(), primitive.index2(), primitive.color());
  const Line& wire3 =
      Line(primitive.index0(), primitive.index2(), primitive.color());
  std::vector<Fragment>* wire_fragment_buffer;
  wire_fragment_buffer =
      RasterizeLineAffine(frame_buffer, vertex_buffer, view_coordinate_buffer,
                          viewport_ndc_buffer, wire1);
  if (wire_fragment_buffer != nullptr) {
    fragment_buffer.insert(fragment_buffer.end(), wire_fragment_buffer->begin(),
                           wire_fragment_buffer->end());
  }
  wire_fragment_buffer =
      RasterizeLineAffine(frame_buffer, vertex_buffer, view_coordinate_buffer,
                          viewport_ndc_buffer, wire2);
  if (wire_fragment_buffer != nullptr) {
    fragment_buffer.insert(fragment_buffer.end(), wire_fragment_buffer->begin(),
                           wire_fragment_buffer->end());
  }
  wire_fragment_buffer =
      RasterizeLineAffine(frame_buffer, vertex_buffer, view_coordinate_buffer,
                          viewport_ndc_buffer, wire3);
  if (wire_fragment_buffer != nullptr) {
    fragment_buffer.insert(fragment_buffer.end(), wire_fragment_buffer->begin(),
                           wire_fragment_buffer->end());
  }
  std::vector<Fragment>* output_fragment_buffer =
      ResourcesManager::GetClearFragmentBuffer();
  *output_fragment_buffer = fragment_buffer;
  return output_fragment_buffer;
}

std::vector<Fragment>* RasterizingShader::RasterizeLinePerspective(
    const FrameBuffer& frame_buffer, const std::vector<Vertex>& vertex_buffer,
    const std::vector<Vector3>& view_coordinate_buffer,
    const std::vector<Vector3>& viewport_ndc_buffer,
    const Line& primitive) const {
  std::vector<Fragment>* fragment_buffer =
      ResourcesManager::GetClearFragmentBuffer();

  const Vector3& view_coordinate1 = view_coordinate_buffer[primitive.index0()];
  const Vector3& view_coordinate2 = view_coordinate_buffer[primitive.index1()];
  const Vector3& viewport_ndc1 = viewport_ndc_buffer[primitive.index0()];
  const Vector3& viewport_ndc2 = viewport_ndc_buffer[primitive.index1()];

  const Vector2& screen_coordinate1 =
      Vector2(viewport_ndc1.x(), viewport_ndc1.y());
  const Vector2& screen_coordinate2 =
      Vector2(viewport_ndc2.x(), viewport_ndc2.y());

  // value for perspective correct interpolation
  float w1 = vertex_buffer[primitive.index0()].coordinate().w();
  if (MathUtils::IsEqual(w1, 0.f)) {
    w1 = MathUtils::kEPSILON;
  }
  float w2 = vertex_buffer[primitive.index1()].coordinate().w();
  if (MathUtils::IsEqual(w2, 0.f)) {
    w2 = MathUtils::kEPSILON;
  }
  float inv_w1 = 1.f / w1;
  float inv_w2 = 1.f / w2;
  const Vector2& inv_w = Vector2(inv_w1, inv_w2);

  // attributes
  float depth1 = viewport_ndc1.z();
  float depth2 = viewport_ndc2.z();

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
    const Vector2& target_coordiante = Vector2(start_x, start_y);
    const Vector2& barycentric = InterpolationUtils::GetPixelBarycentric(
        target_coordiante, screen_coordinate1, screen_coordinate2);
    float interpolated_depth =
        InterpolationUtils::InterpolateAffineLine(depth1, depth2, barycentric);
    if (frame_buffer.GetDepthBuffer().GetDepth(target_coordiante.x(),
                                               target_coordiante.y()) >
        interpolated_depth) {
      float interpolated_w =
          InterpolationUtils::InterpolateWPerspectiveCorrectLine(inv_w,
                                                                 barycentric);
      Vector3 view_coordinate =
          InterpolationUtils::InterpolatePerspectiveCorrectLine(
              view_coordinate1, view_coordinate2, barycentric, inv_w,
              interpolated_w);

      const Fragment& new_fragment =
          Fragment(PrimitiveType::kLINE, &primitive, view_coordinate,
                   target_coordiante, interpolated_depth);
      fragment_buffer->push_back(new_fragment);
    }

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
    const FrameBuffer& frame_buffer, const std::vector<Vertex>& vertex_buffer,
    const std::vector<Vector3>& view_coordinate_buffer,
    const std::vector<Vector3>& viewport_ndc_buffer,
    const Triangle& primitive) const {
  std::vector<Fragment>* fragment_buffer =
      ResourcesManager::GetClearFragmentBuffer();

  const Vector3& view_coordinate1 = view_coordinate_buffer[primitive.index0()];
  const Vector3& view_coordinate2 = view_coordinate_buffer[primitive.index1()];
  const Vector3& view_coordinate3 = view_coordinate_buffer[primitive.index2()];
  const Vector3& viewport_ndc1 = viewport_ndc_buffer[primitive.index0()];
  const Vector3& viewport_ndc2 = viewport_ndc_buffer[primitive.index1()];
  const Vector3& viewport_ndc3 = viewport_ndc_buffer[primitive.index2()];

  const Vector2& screen_coordinate1 =
      Vector2(viewport_ndc1.x(), viewport_ndc1.y());
  const Vector2& screen_coordinate2 =
      Vector2(viewport_ndc2.x(), viewport_ndc2.y());
  const Vector2& screen_coordinate3 =
      Vector2(viewport_ndc3.x(), viewport_ndc3.y());

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
  const Vector3& inv_w = Vector3(inv_w1, inv_w2, inv_w3);

  // attributes
  float depth1 = viewport_ndc1.z();
  float depth2 = viewport_ndc2.z();
  float depth3 = viewport_ndc3.z();

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
      const Vector2& target_coordiante = Vector2(x, y);
      const Vector3& barycentric = InterpolationUtils::GetPixelBarycentric(
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
      if (frame_buffer.GetDepthBuffer().GetDepth(target_coordiante.x(),
                                                 target_coordiante.y()) >
          interpolated_depth) {
        float interpolated_w =
            InterpolationUtils::InterpolateWPerspectiveCorrectTriangle(
                inv_w, barycentric);
        const Vector3& view_coordinate =
            InterpolationUtils::InterpolatePerspectiveCorrectTriangle(
                view_coordinate1, view_coordinate2, view_coordinate3,
                barycentric, inv_w, interpolated_w);

        const Fragment& new_fragment =
            Fragment(PrimitiveType::kTRIANGLE, &primitive, view_coordinate,
                     target_coordiante, interpolated_depth);
        fragment_buffer->push_back(new_fragment);
      }
    }
  }
  return fragment_buffer;
}
std::vector<Fragment>*
RasterizingShader::EdgeFunctionRasterizeTrianglePerspective(
    const FrameBuffer& frame_buffer, const std::vector<Vertex>& vertex_buffer,
    const std::vector<Vector3>& view_coordinate_buffer,
    const std::vector<Vector3>& viewport_ndc_buffer,
    const Triangle& primitive) const {
  std::vector<Fragment>* fragment_buffer =
      ResourcesManager::GetClearFragmentBuffer();

  const Vector3& view_coordinate1 = view_coordinate_buffer[primitive.index0()];
  const Vector3& view_coordinate2 = view_coordinate_buffer[primitive.index1()];
  const Vector3& view_coordinate3 = view_coordinate_buffer[primitive.index2()];
  const Vector3& viewport_ndc1 = viewport_ndc_buffer[primitive.index0()];
  const Vector3& viewport_ndc2 = viewport_ndc_buffer[primitive.index1()];
  const Vector3& viewport_ndc3 = viewport_ndc_buffer[primitive.index2()];

  const Vector2& screen_coordinate1 =
      Vector2(viewport_ndc1.x(), viewport_ndc1.y());
  const Vector2& screen_coordinate2 =
      Vector2(viewport_ndc2.x(), viewport_ndc2.y());
  const Vector2& screen_coordinate3 =
      Vector2(viewport_ndc3.x(), viewport_ndc3.y());
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
  float depth1 = viewport_ndc1.z();
  float depth2 = viewport_ndc2.z();
  float depth3 = viewport_ndc3.z();

  int min_x = MathUtils::Minf(screen_coordinate1.x(), screen_coordinate2.x(),
                              screen_coordinate3.x());
  int max_x = MathUtils::Maxf(screen_coordinate1.x(), screen_coordinate2.x(),
                              screen_coordinate3.x());
  int min_y = MathUtils::Minf(screen_coordinate1.y(), screen_coordinate2.y(),
                              screen_coordinate3.y());
  int max_y = MathUtils::Maxf(screen_coordinate1.y(), screen_coordinate2.y(),
                              screen_coordinate3.y());
  // reserve buffer
  fragment_buffer->reserve((max_x - min_x) * (max_y - min_y));
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
        if (frame_buffer.GetDepthBuffer().GetDepth(x, y) > interpolated_depth) {
          float interpolated_w =
              InterpolationUtils::InterpolateWPerspectiveCorrectTriangle(
                  inv_w, barycentric);
          const Vector3& view_coordinate =
              InterpolationUtils::InterpolatePerspectiveCorrectTriangle(
                  view_coordinate1, view_coordinate2, view_coordinate3,
                  barycentric, inv_w, interpolated_w);

          const Fragment& new_fragment =
              Fragment(PrimitiveType::kTRIANGLE, &primitive, view_coordinate,
                       Vector2(x, y), interpolated_depth);
          fragment_buffer->push_back(new_fragment);
        }
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
    const FrameBuffer& frame_buffer, const std::vector<Vertex>& vertex_buffer,
    const std::vector<Vector3>& view_coordinate_buffer,
    const std::vector<Vector3>& viewport_ndc_buffer,
    const Triangle& primitive) const {
  std::vector<Fragment> fragment_buffer;
  const Line& wire1 =
      Line(primitive.index0(), primitive.index1(), primitive.color());
  const Line& wire2 =
      Line(primitive.index1(), primitive.index2(), primitive.color());
  const Line& wire3 =
      Line(primitive.index2(), primitive.index0(), primitive.color());
  std::vector<Fragment>* wire_fragment_buffer;
  wire_fragment_buffer =
      RasterizeLineAffine(frame_buffer, vertex_buffer, view_coordinate_buffer,
                          viewport_ndc_buffer, wire1);
  if (wire_fragment_buffer != nullptr) {
    fragment_buffer.insert(fragment_buffer.end(), wire_fragment_buffer->begin(),
                           wire_fragment_buffer->end());
  }
  wire_fragment_buffer =
      RasterizeLineAffine(frame_buffer, vertex_buffer, view_coordinate_buffer,
                          viewport_ndc_buffer, wire2);
  if (wire_fragment_buffer != nullptr) {
    fragment_buffer.insert(fragment_buffer.end(), wire_fragment_buffer->begin(),
                           wire_fragment_buffer->end());
  }
  wire_fragment_buffer =
      RasterizeLineAffine(frame_buffer, vertex_buffer, view_coordinate_buffer,
                          viewport_ndc_buffer, wire3);
  if (wire_fragment_buffer != nullptr) {
    fragment_buffer.insert(fragment_buffer.end(), wire_fragment_buffer->begin(),
                           wire_fragment_buffer->end());
  }
  std::vector<Fragment>* output_fragment_buffer =
      ResourcesManager::GetClearFragmentBuffer();
  *output_fragment_buffer = fragment_buffer;
  return output_fragment_buffer;
}
}  // namespace ho_renderer