#include "graphics/rendering_pipeline/pipeline_components/include/viewport_transformer.h"

#include <cstdint>

#include "core/math/include/vector2.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/transformed_vertex.h"

namespace ho_renderer {
ViewportTransformer::ViewportTransformer() = default;
ViewportTransformer::~ViewportTransformer() = default;
TransformedVertex& ViewportTransformer::TransformNDC(
    TransformedVertex& vertex, const Vector2& viewport_position,
    int window_width, int window_height, float depth_range_min,
    float depth_range_max) const {
  // adjust window size
  window_width--;
  window_height--;
  float denormalized_x =
      DenormalizeX(vertex.ndc().x(), viewport_position.x(), window_width);
  float denormalized_y =
      DenormalizeY(vertex.ndc().y(), viewport_position.y(), window_height);
  float denormalized_z =
      DenormalizeZ(vertex.ndc().z(), depth_range_min, depth_range_max);
  vertex.set_viewport_ndc({denormalized_x, denormalized_y, denormalized_z});
  return vertex;
}
// problem : if x, y is 1.f or -1.f denormalized x, y can be window_width,
// window_height
int ViewportTransformer::DenormalizeX(float x, int viewport_position_x,
                                      int screen_width) const {
  int screen_width_half = screen_width * 0.5f;
  return (x * screen_width_half) + screen_width_half + viewport_position_x;
}
int ViewportTransformer::DenormalizeY(float y, int viewport_position_y,
                                      int screen_height) const {
  int screen_height_half = screen_height * 0.5f;
  return -(y * screen_height_half) + screen_height_half + viewport_position_y;
}
float ViewportTransformer::DenormalizeZ(float z, float depth_range_min,
                                        float depth_range_max) const {
  return (z * (depth_range_max - depth_range_min) +
          (depth_range_min + depth_range_max)) *
         0.5f;
}
}  // namespace ho_renderer