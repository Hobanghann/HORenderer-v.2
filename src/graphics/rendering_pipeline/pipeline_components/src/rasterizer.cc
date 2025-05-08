#include "graphics/rendering_pipeline/pipeline_components/include/rasterizer.h"

#include <cassert>
#include <memory>
#include <string>

#include "core/math/include/interpolation_utils.h"
#include "core/math/include/math_utils.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/edge_function.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/frame_buffer.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/transformed_vertex.h"
#include "tools/include/debug.h"

namespace ho_renderer {
Rasterizer::Rasterizer() = default;
Rasterizer::~Rasterizer() = default;
// splicit one primitive
std::vector<Fragment>* Rasterizer::RasterizePoint(
    std::vector<Fragment>* output_f_buffer,
    const std::vector<TransformedVertex>* v_buffer, const Point* p,
    DepthBuffer* d_buffer) {
  ASSERT_MSG(
      output_f_buffer != nullptr,
      "Rasterizer::RasterizePoint Error : output fragment buffer is null");
  ASSERT_MSG(v_buffer != nullptr,
             "Rasterizer::RasterizePoint Error : vertex buffer is null");
  ASSERT_MSG(p != nullptr, "Rasterizer::RasterizePoint Error : point is null");
  ASSERT_MSG(d_buffer != nullptr,
             "Rasterizer::RasterizePoint Error : depth buffer is null");

  if (output_f_buffer == nullptr) {
    return nullptr;
  }
  if (v_buffer == nullptr || p == nullptr || d_buffer == nullptr) {
    return output_f_buffer;
  }

  const TransformedVertex& v = (*v_buffer)[p->index0()];
  const Vector3& view_ndc = v.viewport_ndc();
  const Vector2 screen_coord = Vector2(view_ndc.x(), view_ndc.y());
  float depth = view_ndc.z();
  output_f_buffer->emplace_back(
      p, screen_coord, v.view_coord(), v.texture_coord(), v.normal_vector(),
      v.tangent_vector(), v.source_vertex()->handedness(), depth);
  return output_f_buffer;
}

std::vector<Fragment>* Rasterizer::RasterizeLineAffine(
    std::vector<Fragment>* output_f_buffer,
    const std::vector<TransformedVertex>* v_buffer, const Line* l,
    DepthBuffer* d_buffer, const Triangle* t) {
  ASSERT_MSG(
      output_f_buffer != nullptr,
      "Rasterizer::RasterizeLineAffine Error : output fragment buffer is null");
  ASSERT_MSG(v_buffer != nullptr,
             "Rasterizer::RasterizeLineAffine Error : vertex buffer is null");
  ASSERT_MSG(l != nullptr,
             "Rasterizer::RasterizeLineAffine Error : line is null");
  ASSERT_MSG(d_buffer != nullptr,
             "Rasterizer::RasterizeLineAffine Error : depth buffer is null");

  if (output_f_buffer == nullptr) {
    return nullptr;
  }
  if (v_buffer == nullptr || l == nullptr || d_buffer == nullptr) {
    return output_f_buffer;
  }

  // load attributes
  const TransformedVertex& v1 = (*v_buffer)[l->index0()];
  const TransformedVertex& v2 = (*v_buffer)[l->index1()];
  Attributes atr = LoadAttributes(v1, v2);

  // set component for bresenham algorithm
  int start_x = atr.screen_coord1.x();
  int start_y = atr.screen_coord1.y();
  int end_x = atr.screen_coord2.x();
  int end_y = atr.screen_coord2.y();
  int dx = MathUtils::Abs(end_x - start_x);
  int dy = MathUtils::Abs(end_y - start_y);
  int sx = (start_x < end_x) ? 1 : -1;
  int sy = (start_y < end_y) ? 1 : -1;
  int err = dx - dy;

  while (true) {
    const Vector2 target_coord = Vector2(start_x, start_y);
    const Vector2 barycentric = InterpolationUtils::GetPixelBarycentric(
        target_coord, atr.screen_coord1, atr.screen_coord2);
    // degenerate case
    if (MathUtils::IsFloatNaN(barycentric.x()) &&
        MathUtils::IsFloatNaN(barycentric.y())) {
      return output_f_buffer;
    }
    std::optional<Fragment> frag = LoadFragmentAffine(
        Vector2(start_x, start_y), barycentric, atr, d_buffer,
        (t == nullptr ? static_cast<const Primitive*>(l)
                      : static_cast<const Primitive*>(t)));
    if (frag.has_value()) {
      output_f_buffer->push_back(frag.value());
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
  return output_f_buffer;
}
std::vector<Fragment>* Rasterizer::RasterizeLinePerspective(
    std::vector<Fragment>* output_f_buffer,
    const std::vector<TransformedVertex>* v_buffer, const Line* l,
    DepthBuffer* d_buffer, const Triangle* t) {
  ASSERT_MSG(output_f_buffer != nullptr,
             "Rasterizer::RasterizeLinePerspective Error : output fragment "
             "buffer is null");
  ASSERT_MSG(
      v_buffer != nullptr,
      "Rasterizer::RasterizeLinePerspective Error : vertex buffer is null");
  ASSERT_MSG(l != nullptr,
             "Rasterizer::RasterizeLinePerspective Error : line is null");
  ASSERT_MSG(
      d_buffer != nullptr,
      "Rasterizer::RasterizeLinePerspective Error : depth buffer is null");

  if (output_f_buffer == nullptr) {
    return nullptr;
  }
  if (v_buffer == nullptr || l == nullptr || d_buffer == nullptr) {
    return output_f_buffer;
  }
  // load attrivutes
  const TransformedVertex& v1 = (*v_buffer)[l->index0()];
  const TransformedVertex& v2 = (*v_buffer)[l->index1()];
  Attributes atr = LoadAttributes(v1, v2);

  // set component for bresenham algorithm
  int start_x = atr.screen_coord1.x();
  int start_y = atr.screen_coord1.y();
  int end_x = atr.screen_coord2.x();
  int end_y = atr.screen_coord2.y();
  int dx = MathUtils::Abs(end_x - start_x);
  int dy = MathUtils::Abs(end_y - start_y);
  int sx = (start_x < end_x) ? 1 : -1;
  int sy = (start_y < end_y) ? 1 : -1;
  int err = dx - dy;

  while (true) {
    // create fragment
    const Vector2& target_coord = Vector2(start_x, start_y);
    const Vector2& barycentric = InterpolationUtils::GetPixelBarycentric(
        target_coord, atr.screen_coord1, atr.screen_coord2);
    // degenerate case
    if (MathUtils::IsFloatNaN(barycentric.x()) &&
        MathUtils::IsFloatNaN(barycentric.y())) {
      return output_f_buffer;
    }
    std::optional<Fragment> frag = LoadFragmentAffine(
        Vector2(start_x, start_y), barycentric, atr, d_buffer,
        (t == nullptr ? static_cast<const Primitive*>(l)
                      : static_cast<const Primitive*>(t)));
    if (frag.has_value()) {
      output_f_buffer->push_back(frag.value());
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
  return output_f_buffer;
}

std::vector<Fragment>* Rasterizer::RasterizeTriangleAffine(
    std::vector<Fragment>* output_f_buffer,
    const std::vector<TransformedVertex>* v_buffer, const Triangle* t,
    DepthBuffer* d_buffer) {
  ASSERT_MSG(output_f_buffer != nullptr,
             "Rasterizer::RasterizeTriangleAffine Error : output fragment "
             "buffer is null");
  ASSERT_MSG(
      v_buffer != nullptr,
      "Rasterizer::RasterizeTriangleAffine Error : vertex buffer is null");
  ASSERT_MSG(t != nullptr,
             "Rasterizer::RasterizeTriangleAffine Error : triangle is null");
  ASSERT_MSG(
      d_buffer != nullptr,
      "Rasterizer::RasterizeTriangleAffine Error : depth buffer is null");

  if (output_f_buffer == nullptr) {
    return nullptr;
  }
  if (v_buffer == nullptr || t == nullptr || d_buffer == nullptr) {
    return output_f_buffer;
  }
  // attributes
  const TransformedVertex& v1 = (*v_buffer)[t->index0()];
  const TransformedVertex& v2 = (*v_buffer)[t->index1()];
  const TransformedVertex& v3 = (*v_buffer)[t->index2()];
  Attributes atr = LoadAttributes(v1, v2, v3);

  BoundingVolume b = LoadBoundingVolume(atr.screen_coord1, atr.screen_coord2,
                                        atr.screen_coord3);

  for (int y = b.min.y(); y < b.max.y(); y++) {
    for (int x = b.min.x(); x < b.max.x(); x++) {
      const Vector2& target_coord = Vector2(x, y);
      const Vector3& barycentric = InterpolationUtils::GetPixelBarycentric(
          target_coord, atr.screen_coord1, atr.screen_coord2,
          atr.screen_coord3);
      // degenerate case
      if (MathUtils::IsFloatNaN(barycentric.x()) &&
          MathUtils::IsFloatNaN(barycentric.y()) &&
          MathUtils::IsFloatNaN(barycentric.z())) {
        return output_f_buffer;
      }
      // if target_coord is outof triangle, continue.
      if (barycentric.x() < 0.f || barycentric.x() > 1.f ||
          barycentric.y() < 0.f || barycentric.y() > 1.f ||
          barycentric.z() < 0.f || barycentric.z() > 1.f) {
        continue;
      }
      std::optional<Fragment> frag =
          LoadFragmentAffine(Vector2(x, y), barycentric, atr, d_buffer, t);
      if (frag.has_value()) {
        output_f_buffer->push_back(frag.value());
      }
    }
  }
  return output_f_buffer;
}
std::vector<Fragment>* Rasterizer::EdgeFunctionRasterizeTriangleAffine(
    std::vector<Fragment>* output_f_buffer,
    const std::vector<TransformedVertex>* v_buffer, const Triangle* t,
    DepthBuffer* d_buffer) {
  ASSERT_MSG(
      output_f_buffer != nullptr,
      "Rasterizer::EdgeFunctionRasterizeTriangleAffine Error : output fragment "
      "buffer is null");
  ASSERT_MSG(v_buffer != nullptr,
             "Rasterizer::EdgeFunctionRasterizeTriangleAffine Error : vertex "
             "buffer is null");
  ASSERT_MSG(t != nullptr,
             "Rasterizer::EdgeFunctionRasterizeTriangleAffine Error : triangle "
             "is null");
  ASSERT_MSG(d_buffer != nullptr,
             "Rasterizer::EdgeFunctionRasterizeTriangleAffine Error : depth "
             "buffer is null");

  if (output_f_buffer == nullptr) {
    return nullptr;
  }
  if (v_buffer == nullptr || t == nullptr || d_buffer == nullptr) {
    return output_f_buffer;
  }
  // attributes
  const TransformedVertex& v1 = (*v_buffer)[t->index0()];
  const TransformedVertex& v2 = (*v_buffer)[t->index1()];
  const TransformedVertex& v3 = (*v_buffer)[t->index2()];
  Attributes atr = LoadAttributes(v1, v2, v3);

  BoundingVolume b = LoadBoundingVolume(atr.screen_coord1, atr.screen_coord2,
                                        atr.screen_coord3);
  // edge functions
  const EdgeFunction f12(atr.screen_coord1, atr.screen_coord2,
                         Vector2(b.min.x(), b.min.y()));
  const EdgeFunction f23(atr.screen_coord2, atr.screen_coord3,
                         Vector2(b.min.x(), b.min.y()));
  const EdgeFunction f31(atr.screen_coord3, atr.screen_coord1,
                         Vector2(b.min.x(), b.min.y()));

  float area = f12.dx() * atr.screen_coord3.x() +
               f12.dy() * atr.screen_coord3.y() +
               (atr.screen_coord2.x() * atr.screen_coord1.y() -
                atr.screen_coord1.x() * atr.screen_coord2.y());
  // degenerate case
  if (MathUtils::IsEqual(area, 0.f)) {
    return output_f_buffer;
  }
  float inv_area = 1.f / area;
  int f12_init = f12.initial_value();
  int f23_init = f23.initial_value();
  int f31_init = f31.initial_value();
  for (int y = b.min.y(); y < b.max.y(); y++) {
    int f12_ev = f12_init;
    int f23_ev = f23_init;
    int f31_ev = f31_init;
    for (int x = b.min.x(); x < b.max.x(); x++) {
      if (f12_ev >= 0 && f23_ev >= 0 && f31_ev >= 0) {
        Vector3 barycentric(f23_ev * inv_area, f31_ev * inv_area,
                            f12_ev * inv_area);
        std::optional<Fragment> frag =
            LoadFragmentAffine(Vector2(x, y), barycentric, atr, d_buffer, t);
        if (frag.has_value()) {
          output_f_buffer->push_back(frag.value());
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
  return output_f_buffer;
}
std::vector<Fragment>* Rasterizer::RasterizeWireTriangleAffine(
    std::vector<Fragment>* output_f_buffer,
    const std::vector<TransformedVertex>* v_buffer, const Triangle* t,
    DepthBuffer* d_buffer) {
  ASSERT_MSG(output_f_buffer != nullptr,
             "Rasterizer::RasterizeWireTriangleAffine Error : output fragment "
             "buffer is null");
  ASSERT_MSG(
      v_buffer != nullptr,
      "Rasterizer::RasterizeWireTriangleAffine Error : vertex buffer is null");
  ASSERT_MSG(
      t != nullptr,
      "Rasterizer::RasterizeWireTriangleAffine Error : triangle is null");
  ASSERT_MSG(
      d_buffer != nullptr,
      "Rasterizer::RasterizeWireTriangleAffine Error : depth buffer is null");

  if (output_f_buffer == nullptr) {
    return nullptr;
  }
  if (v_buffer == nullptr || t == nullptr || d_buffer == nullptr) {
    return output_f_buffer;
  }
  Line wire1 = Line(t->material(), t->index0(), t->index1());
  Line wire2 = Line(t->material(), t->index1(), t->index2());
  Line wire3 = Line(t->material(), t->index2(), t->index0());
  output_f_buffer =
      RasterizeLineAffine(output_f_buffer, v_buffer, &wire1, d_buffer, t);
  output_f_buffer =
      RasterizeLineAffine(output_f_buffer, v_buffer, &wire2, d_buffer, t);
  output_f_buffer =
      RasterizeLineAffine(output_f_buffer, v_buffer, &wire3, d_buffer, t);
  return output_f_buffer;
}

std::vector<Fragment>* Rasterizer::RasterizeTrianglePerspective(
    std::vector<Fragment>* output_f_buffer,
    const std::vector<TransformedVertex>* v_buffer, const Triangle* t,
    DepthBuffer* d_buffer) {
  ASSERT_MSG(output_f_buffer != nullptr,
             "Rasterizer::RasterizeTrianglePerspective Error : output fragment "
             "buffer is null");
  ASSERT_MSG(
      v_buffer != nullptr,
      "Rasterizer::RasterizeTrianglePerspective Error : vertex buffer is null");
  ASSERT_MSG(
      t != nullptr,
      "Rasterizer::RasterizeTrianglePerspective Error : triangle is null");
  ASSERT_MSG(
      d_buffer != nullptr,
      "Rasterizer::RasterizeTrianglePerspective Error : depth buffer is null");

  if (output_f_buffer == nullptr) {
    return nullptr;
  }
  if (v_buffer == nullptr || t == nullptr || d_buffer == nullptr) {
    return output_f_buffer;
  }
  const TransformedVertex& v1 = (*v_buffer)[t->index0()];
  const TransformedVertex& v2 = (*v_buffer)[t->index1()];
  const TransformedVertex& v3 = (*v_buffer)[t->index2()];
  Attributes atr = LoadAttributes(v1, v2, v3);

  BoundingVolume b = LoadBoundingVolume(atr.screen_coord1, atr.screen_coord2,
                                        atr.screen_coord3);

  for (int y = b.min.y(); y < b.max.y(); y++) {
    for (int x = b.min.x(); x < b.max.x(); x++) {
      const Vector2& target_coord = Vector2(x, y);
      const Vector3& barycentric = InterpolationUtils::GetPixelBarycentric(
          target_coord, atr.screen_coord1, atr.screen_coord2,
          atr.screen_coord3);
      // degenerate case
      if (MathUtils::IsFloatNaN(barycentric.x()) &&
          MathUtils::IsFloatNaN(barycentric.y()) &&
          MathUtils::IsFloatNaN(barycentric.z())) {
        return output_f_buffer;
      }
      // if target_coord is outof triangle, continue.
      if (barycentric.x() < 0.f || barycentric.x() > 1.f ||
          barycentric.y() < 0.f || barycentric.y() > 1.f ||
          barycentric.z() < 0.f || barycentric.z() > 1.f) {
        continue;
      }
      std::optional<Fragment> frag =
          LoadFragmentPerspective(Vector2(x, y), barycentric, atr, d_buffer, t);
      if (frag.has_value()) {
        output_f_buffer->push_back(frag.value());
      }
    }
  }
  return output_f_buffer;
}
std::vector<Fragment>* Rasterizer::EdgeFunctionRasterizeTrianglePerspective(
    std::vector<Fragment>* output_f_buffer,
    const std::vector<TransformedVertex>* v_buffer, const Triangle* t,
    DepthBuffer* d_buffer) {
  ASSERT_MSG(output_f_buffer != nullptr,
             "Rasterizer::EdgeFunctionRasterizeTrianglePerspective Error : "
             "output fragment "
             "buffer is null");
  ASSERT_MSG(v_buffer != nullptr,
             "Rasterizer::EdgeFunctionRasterizeTrianglePerspective Error : "
             "vertex buffer is null");
  ASSERT_MSG(t != nullptr,
             "Rasterizer::EdgeFunctionRasterizeTrianglePerspective Error : "
             "triangle is null");
  ASSERT_MSG(d_buffer != nullptr,
             "Rasterizer::EdgeFunctionRasterizeTrianglePerspective Error : "
             "depth buffer is null");

  if (output_f_buffer == nullptr) {
    return nullptr;
  }
  if (v_buffer == nullptr || t == nullptr || d_buffer == nullptr) {
    return output_f_buffer;
  }
  // attributes
  const TransformedVertex& v1 = (*v_buffer)[t->index0()];
  const TransformedVertex& v2 = (*v_buffer)[t->index1()];
  const TransformedVertex& v3 = (*v_buffer)[t->index2()];
  Attributes atr = LoadAttributes(v1, v2, v3);

  BoundingVolume b = LoadBoundingVolume(atr.screen_coord1, atr.screen_coord2,
                                        atr.screen_coord3);
  // edge functions
  EdgeFunction f12(atr.screen_coord1, atr.screen_coord2,
                   Vector2(b.min.x(), b.min.y()));
  EdgeFunction f23(atr.screen_coord2, atr.screen_coord3,
                   Vector2(b.min.x(), b.min.y()));
  EdgeFunction f31(atr.screen_coord3, atr.screen_coord1,
                   Vector2(b.min.x(), b.min.y()));

  float area = f12.dx() * atr.screen_coord3.x() +
               f12.dy() * atr.screen_coord3.y() +
               (atr.screen_coord2.x() * atr.screen_coord1.y() -
                atr.screen_coord1.x() * atr.screen_coord2.y());
  // degenerate case
  if (MathUtils::IsEqual(area, 0.f)) {
    return nullptr;
  }
  float inv_area = 1.f / area;
  int f12_init = f12.initial_value();
  int f23_init = f23.initial_value();
  int f31_init = f31.initial_value();
  for (int y = b.min.y(); y < b.max.y(); y++) {
    int f12_ev = f12_init;
    int f23_ev = f23_init;
    int f31_ev = f31_init;
    for (int x = b.min.x(); x < b.max.x(); x++) {
      if (f12_ev >= 0 && f23_ev >= 0 && f31_ev >= 0) {
        Vector3 barycentric(f23_ev * inv_area, f31_ev * inv_area,
                            f12_ev * inv_area);
        std::optional<Fragment> frag = LoadFragmentPerspective(
            Vector2(x, y), barycentric, atr, d_buffer, t);
        if (frag.has_value()) {
          output_f_buffer->push_back(frag.value());
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
  return output_f_buffer;
}
std::vector<ho_renderer::Fragment>*
Rasterizer::RasterizeWireTrianglePerspective(
    std::vector<Fragment>* output_f_buffer,
    const std::vector<TransformedVertex>* v_buffer, const Triangle* t,
    DepthBuffer* d_buffer) {
  ASSERT_MSG(
      output_f_buffer != nullptr,
      "Rasterizer::RasterizeWireTrianglePerspective Error : output fragment "
      "buffer is null");
  ASSERT_MSG(v_buffer != nullptr,
             "Rasterizer::RasterizeWireTrianglePerspective Error : vertex "
             "buffer is null");
  ASSERT_MSG(
      t != nullptr,
      "Rasterizer::RasterizeWireTrianglePerspective Error : triangle is null");
  ASSERT_MSG(d_buffer != nullptr,
             "Rasterizer::RasterizeWireTrianglePerspective Error : depth "
             "buffer is null");

  if (output_f_buffer == nullptr) {
    return nullptr;
  }
  if (v_buffer == nullptr || t == nullptr || d_buffer == nullptr) {
    return output_f_buffer;
  }
  Line wire1 = Line(t->material(), t->index0(), t->index1());
  Line wire2 = Line(t->material(), t->index1(), t->index2());
  Line wire3 = Line(t->material(), t->index2(), t->index0());
  output_f_buffer =
      RasterizeLinePerspective(output_f_buffer, v_buffer, &wire1, d_buffer, t);
  output_f_buffer =
      RasterizeLinePerspective(output_f_buffer, v_buffer, &wire2, d_buffer, t);
  output_f_buffer =
      RasterizeLinePerspective(output_f_buffer, v_buffer, &wire3, d_buffer, t);
  return output_f_buffer;
}

TransformedVertex Rasterizer::InterpolateAffineLine(
    const TransformedVertex& v1, const TransformedVertex& v2,
    const Vector2& barycentric) {
  return barycentric.x() * v1 + barycentric.y() * v2;
}
TransformedVertex Rasterizer::InterpolateAffineTriangle(
    const TransformedVertex& v1, const TransformedVertex& v2,
    const TransformedVertex& v3, const Vector3& barycentric) {
  return barycentric.x() * v1 + barycentric.y() * v2 + barycentric.z() * v3;
}
TransformedVertex Rasterizer::InterpolatePerspectiveCorrectLine(
    const TransformedVertex& v1, const TransformedVertex& v2,
    const Vector2& ndc_barycentric, const Vector2& inv_w,
    float interpolated_w) {
  return interpolated_w * (inv_w.x() * ndc_barycentric.x() * v1 +
                           inv_w.y() * ndc_barycentric.y() * v2);
}
TransformedVertex Rasterizer::InterpolatePerspectiveCorrectTriangle(
    const TransformedVertex& v1, const TransformedVertex& v2,
    const TransformedVertex& v3, const Vector3& ndc_barycentric,
    const Vector3& inv_w, float interpolated_w) {
  return interpolated_w * (inv_w.x() * ndc_barycentric.x() * v1 +
                           inv_w.y() * ndc_barycentric.y() * v2 +
                           inv_w.z() * ndc_barycentric.z() * v3);
}

Rasterizer::Attributes Rasterizer::LoadAttributes(const TransformedVertex& v1,
                                                  const TransformedVertex& v2) {
  float w1 = v1.clip_coord().w();
  if (MathUtils::IsEqual(w1, 0.f)) {
    w1 = MathUtils::kFloatMin;
  }
  float w2 = v2.clip_coord().w();
  if (MathUtils::IsEqual(w2, 0.f)) {
    w2 = MathUtils::kFloatMin;
  }
  float inv_w1 = 1.f / w1;
  float inv_w2 = 1.f / w2;
  return {v1,
          v2,
          v2,
          Vector2(v1.viewport_ndc().x(), v1.viewport_ndc().y()),
          Vector2(v2.viewport_ndc().x(), v2.viewport_ndc().y()),
          Vector2::kZero,
          v1.viewport_ndc().z(),
          v2.viewport_ndc().z(),
          0.f,
          {inv_w1, inv_w2, 0.f}};
}
Rasterizer::Attributes Rasterizer::LoadAttributes(const TransformedVertex& v1,
                                                  const TransformedVertex& v2,
                                                  const TransformedVertex& v3) {
  float w1 = v1.clip_coord().w();
  if (MathUtils::IsEqual(w1, 0.f)) {
    w1 = MathUtils::kFloatMin;
  }
  float w2 = v2.clip_coord().w();
  if (MathUtils::IsEqual(w2, 0.f)) {
    w2 = MathUtils::kFloatMin;
  }
  float w3 = v3.clip_coord().w();
  if (MathUtils::IsEqual(w3, 0.f)) {
    w3 = MathUtils::kFloatMin;
  }
  float inv_w1 = 1.f / w1;
  float inv_w2 = 1.f / w2;
  float inv_w3 = 1.f / w3;
  return {v1,
          v2,
          v3,
          Vector2(v1.viewport_ndc().x(), v1.viewport_ndc().y()),
          Vector2(v2.viewport_ndc().x(), v2.viewport_ndc().y()),
          Vector2(v3.viewport_ndc().x(), v3.viewport_ndc().y()),
          v1.viewport_ndc().z(),
          v2.viewport_ndc().z(),
          v3.viewport_ndc().z(),
          {inv_w1, inv_w2, inv_w3}};
}

Rasterizer::BoundingVolume Rasterizer::LoadBoundingVolume(
    const Vector2& screen_coord1, const Vector2& screen_coord2,
    const Vector2& screen_coord3) {
  int min_x =
      MathUtils::Minf(screen_coord1.x(), screen_coord2.x(), screen_coord3.x());
  int max_x =
      MathUtils::Maxf(screen_coord1.x(), screen_coord2.x(), screen_coord3.x());
  int min_y =
      MathUtils::Minf(screen_coord1.y(), screen_coord2.y(), screen_coord3.y());
  int max_y =
      MathUtils::Maxf(screen_coord1.y(), screen_coord2.y(), screen_coord3.y());
  return {Vector2(min_x, min_y), Vector2(max_x, max_y)};
}

std::optional<Fragment> Rasterizer::LoadFragmentAffine(
    const Vector2& target_coord, const Vector2& barycentric,
    const Attributes& atr, DepthBuffer* d_buffer, const Primitive* p) {
  ASSERT_MSG(d_buffer != nullptr,
             "Rasterizer::LoadFragmentAffine Error : depth buffer is null");
  ASSERT_MSG(p != nullptr,
             "Rasterizer::LoadFragmentAffine Error : primitive is null");
  if (d_buffer == nullptr || p == nullptr) {
    return std::nullopt;
  }
  float depth = InterpolationUtils::InterpolateAffineLine(
      atr.depth1, atr.depth2, barycentric);
  if (d_buffer->GetDepth(target_coord.x(), target_coord.y()) > depth) {
    d_buffer->SetDepth(target_coord.x(), target_coord.y(), depth);
    TransformedVertex frag_vertex =
        InterpolateAffineLine(atr.v1, atr.v2, barycentric);
    return std::make_optional<Fragment>(
        p, target_coord, frag_vertex.view_coord(), frag_vertex.texture_coord(),
        frag_vertex.normal_vector(), frag_vertex.tangent_vector(),
        frag_vertex.source_vertex()->handedness(), depth);
  } else {
    return std::nullopt;
  }
}
std::optional<Fragment> Rasterizer::LoadFragmentAffine(
    const Vector2& target_coord, const Vector3& barycentric,
    const Attributes& atr, DepthBuffer* d_buffer, const Primitive* p) {
  ASSERT_MSG(d_buffer != nullptr,
             "Rasterizer::LoadFragmentAffine Error : depth buffer is null");
  ASSERT_MSG(p != nullptr,
             "Rasterizer::LoadFragmentAffine Error : primitive is null");
  if (d_buffer == nullptr || p == nullptr) {
    return std::nullopt;
  }
  float depth = InterpolationUtils::InterpolateAffineTriangle(
      atr.depth1, atr.depth2, atr.depth3, barycentric);
  if (d_buffer->GetDepth(target_coord.x(), target_coord.y()) > depth) {
    d_buffer->SetDepth(target_coord.x(), target_coord.y(), depth);
    TransformedVertex frag_vertex =
        InterpolateAffineTriangle(atr.v1, atr.v2, atr.v3, barycentric);
    return std::make_optional<Fragment>(
        p, target_coord, frag_vertex.view_coord(), frag_vertex.texture_coord(),
        frag_vertex.normal_vector(), frag_vertex.tangent_vector(),
        frag_vertex.source_vertex()->handedness(), depth);
  } else {
    return std::nullopt;
  }
}
std::optional<Fragment> Rasterizer::LoadFragmentPerspective(
    const Vector2& target_coord, const Vector2& barycentric,
    const Attributes& atr, DepthBuffer* d_buffer, const Primitive* p) {
  ASSERT_MSG(
      d_buffer != nullptr,
      "Rasterizer::LoadFragmentPerspective Error : depth buffer is null");
  ASSERT_MSG(p != nullptr,
             "Rasterizer::LoadFragmentPerspective Error : primitive is null");
  if (d_buffer == nullptr || p == nullptr) {
    return std::nullopt;
  }
  float depth = InterpolationUtils::InterpolateAffineLine(
      atr.depth1, atr.depth2, barycentric);
  if (d_buffer->GetDepth(target_coord.x(), target_coord.y()) > depth) {
    d_buffer->SetDepth(target_coord.x(), target_coord.y(), depth);
    float interpolated_w =
        InterpolationUtils::InterpolateWPerspectiveCorrectLine(
            atr.inv_w.ToVector2(), barycentric);
    TransformedVertex frag_vertex = InterpolatePerspectiveCorrectLine(
        atr.v1, atr.v2, barycentric, atr.inv_w.ToVector2(), interpolated_w);
    return std::make_optional<Fragment>(
        p, target_coord, frag_vertex.view_coord(), frag_vertex.texture_coord(),
        frag_vertex.normal_vector(), frag_vertex.tangent_vector(),
        frag_vertex.handedness(), depth);
  } else {
    return std::nullopt;
  }
}
std::optional<Fragment> Rasterizer::LoadFragmentPerspective(
    const Vector2& target_coord, const Vector3& barycentric,
    const Attributes& atr, DepthBuffer* d_buffer, const Primitive* p) {
  ASSERT_MSG(
      d_buffer != nullptr,
      "Rasterizer::LoadFragmentPerspective Error : depth buffer is null");
  ASSERT_MSG(p != nullptr,
             "Rasterizer::LoadFragmentPerspective Error : primitive is null");
  if (d_buffer == nullptr || p == nullptr) {
    return std::nullopt;
  }
  float depth = InterpolationUtils::InterpolateAffineTriangle(
      atr.depth1, atr.depth2, atr.depth3, barycentric);
  if (d_buffer->GetDepth(target_coord.x(), target_coord.y()) > depth) {
    d_buffer->SetDepth(target_coord.x(), target_coord.y(), depth);
    float interpolated_w =
        InterpolationUtils::InterpolateWPerspectiveCorrectTriangle(atr.inv_w,
                                                                   barycentric);
    TransformedVertex frag_vertex = InterpolatePerspectiveCorrectTriangle(
        atr.v1, atr.v2, atr.v3, barycentric, atr.inv_w, interpolated_w);
    return std::make_optional<Fragment>(
        p, target_coord, frag_vertex.view_coord(), frag_vertex.texture_coord(),
        frag_vertex.normal_vector(), frag_vertex.tangent_vector(),
        frag_vertex.handedness(), depth);
  } else {
    return std::nullopt;
  }
}
}  // namespace ho_renderer