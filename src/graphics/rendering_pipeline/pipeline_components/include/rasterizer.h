#ifndef _HORENDERER_RASTERIZER_H_
#define _HORENDERER_RASTERIZER_H_

#include <memory>
#include <optional>
#include <vector>

#include "graphics/rendering_pipeline/pipeline_objects/include/depth_buffer.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/fragment.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/line.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/point.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/transformed_vertex.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/triangle.h"
#include "graphics/rendering_pipeline/system/include/pipeline_settings.h"

namespace ho_renderer {
class Rasterizer {
 public:
  struct Attributes {
    const TransformedVertex& v1;
    const TransformedVertex& v2;
    const TransformedVertex& v3;
    Vector2 screen_coord1;
    Vector2 screen_coord2;
    Vector2 screen_coord3;
    float depth1;
    float depth2;
    float depth3;
    Vector3 inv_w;
  };
  struct BoundingVolume {
    Vector2 min;
    Vector2 max;
  };
  Rasterizer();
  Rasterizer(const Rasterizer&) = delete;
  Rasterizer& operator=(const Rasterizer&) = delete;
  ~Rasterizer();

  std::vector<Fragment>* RasterizePoint(
      std::vector<Fragment>* output_f_buffer,
      const std::vector<TransformedVertex>* v_buffer, const Point* p,
      DepthBuffer* d_buffer);
  std::vector<Fragment>* RasterizeLineAffine(
      std::vector<Fragment>* output_f_buffer,
      const std::vector<TransformedVertex>* v_buffer, const Line* l,
      DepthBuffer* d_buffer, const Triangle* t = nullptr);
  std::vector<Fragment>* RasterizeLinePerspective(
      std::vector<Fragment>* output_f_buffer,
      const std::vector<TransformedVertex>* v_buffer, const Line* l,
      DepthBuffer* d_buffer, const Triangle* t = nullptr);
  std::vector<Fragment>* RasterizeTriangleAffine(
      std::vector<Fragment>* output_f_buffer,
      const std::vector<TransformedVertex>* v_buffer, const Triangle* t,
      DepthBuffer* d_buffer);
  std::vector<Fragment>* EdgeFunctionRasterizeTriangleAffine(
      std::vector<Fragment>* output_f_buffer,
      const std::vector<TransformedVertex>* v_buffer, const Triangle* t,
      DepthBuffer* d_buffer);
  std::vector<Fragment>* RasterizeWireTriangleAffine(
      std::vector<Fragment>* output_f_buffer,
      const std::vector<TransformedVertex>* v_buffer, const Triangle* t,
      DepthBuffer* d_buffer);
  std::vector<Fragment>* RasterizeTrianglePerspective(
      std::vector<Fragment>* output_f_buffer,
      const std::vector<TransformedVertex>* v_buffer, const Triangle* t,
      DepthBuffer* d_buffer);
  std::vector<Fragment>* EdgeFunctionRasterizeTrianglePerspective(
      std::vector<Fragment>* output_f_buffer,
      const std::vector<TransformedVertex>* v_buffer, const Triangle* t,
      DepthBuffer* d_buffer);
  std::vector<Fragment>* RasterizeWireTrianglePerspective(
      std::vector<Fragment>* output_f_buffer,
      const std::vector<TransformedVertex>* v_buffer, const Triangle* t,
      DepthBuffer* d_buffer);

  TransformedVertex InterpolateAffineLine(const TransformedVertex& v1,
                                          const TransformedVertex& v2,
                                          const Vector2& barycentric);
  TransformedVertex InterpolateAffineTriangle(const TransformedVertex& v1,
                                              const TransformedVertex& v2,
                                              const TransformedVertex& v3,
                                              const Vector3& barycentric);
  TransformedVertex InterpolatePerspectiveCorrectLine(
      const TransformedVertex& v1, const TransformedVertex& v2,
      const Vector2& ndc_barycentric, const Vector2& inv_w,
      float interpolated_w);
  TransformedVertex InterpolatePerspectiveCorrectTriangle(
      const TransformedVertex& v1, const TransformedVertex& v2,
      const TransformedVertex& v3, const Vector3& ndc_barycentric,
      const Vector3& inv_w, float interpolated_w);

  Attributes LoadAttributes(const TransformedVertex& v1,
                            const TransformedVertex& v2);
  Attributes LoadAttributes(const TransformedVertex& v1,
                            const TransformedVertex& v2,
                            const TransformedVertex& v3);

  BoundingVolume LoadBoundingVolume(const Vector2& screen_coord1,
                                    const Vector2& screen_coord2,
                                    const Vector2& screen_coord3);

  std::optional<Fragment> LoadFragmentAffine(const Vector2& target_coord,
                                             const Vector2& barycentric,
                                             const Attributes& atr,
                                             DepthBuffer* d_buffer,
                                             const Primitive* p);
  std::optional<Fragment> LoadFragmentAffine(const Vector2& target_coord,
                                             const Vector3& barycentric,
                                             const Attributes& atr,
                                             DepthBuffer* d_buffer,
                                             const Primitive* p);
  std::optional<Fragment> LoadFragmentPerspective(const Vector2& target_coord,
                                                  const Vector2& barycentric,
                                                  const Attributes& atr,
                                                  DepthBuffer* d_buffer,
                                                  const Primitive* p);
  std::optional<Fragment> LoadFragmentPerspective(const Vector2& target_coord,
                                                  const Vector3& barycentric,
                                                  const Attributes& atr,
                                                  DepthBuffer* d_buffer,
                                                  const Primitive* p);
};
}  // namespace ho_renderer
#endif  // _HORENDERER_RASTERIZER_H_