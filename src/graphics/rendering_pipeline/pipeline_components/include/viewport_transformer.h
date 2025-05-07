#ifndef _HORENDERER_VIEWPORT_TRANSFORMER_H_
#define _HORENDERER_VIEWPORT_TRANSFORMER_H_

#include <cstdint>

#include "core/math/include/vector2.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/transformed_vertex.h"

namespace ho_renderer {
class ViewportTransformer {
 public:
  ViewportTransformer();
  ViewportTransformer(const ViewportTransformer&) = delete;
  ViewportTransformer& operator=(const ViewportTransformer&) = delete;
  ~ViewportTransformer();

  TransformedVertex& TransformNDC(TransformedVertex& vertex,
                                  const Vector2& viewport_position,
                                  int window_width, int window_height,
                                  float depth_range_min,
                                  float depth_range_max) const;

 private:
  int DenormalizeX(float x, int viewport_position_x, int screen_width) const;
  int DenormalizeY(float y, int viewport_position_y, int screen_height) const;
  float DenormalizeZ(float z, float depth_range_min,
                     float depth_range_max) const;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_VIEWPORT_TRANSFORMER_H_