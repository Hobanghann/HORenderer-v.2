#include "rendering_pipeline/shaders/include/viewport_transform_shader.h"

#include <cstdint>

#include "app/include/debug.h"
#include "math/include/vector3.h"

namespace ho_renderer {
ViewportTransformShader::ViewportTransformShader() = default;
ViewportTransformShader::~ViewportTransformShader() = default;
Vector3 ViewportTransformShader::TransformNDC(const Vector3& ndc,
                                              const Vector2& viewport_position,
                                              std::uint32_t window_width,
                                              std::uint32_t window_height,
                                              float depth_range_min,
                                              float depth_range_max) const {
  float denormalized_x =
      DenormalizeX(ndc.x(), viewport_position.x(), window_width);
  float denormalized_y =
      DenormalizeY(ndc.y(), viewport_position.y(), window_height);
  float denormalized_z =
      DenormalizeZ(ndc.z(), depth_range_min, depth_range_max);
  return {denormalized_x, denormalized_y, denormalized_z};
}

std::uint32_t ViewportTransformShader::DenormalizeX(
    float x, std::uint32_t viewport_position_x,
    std::uint32_t screen_width) const {
  uint32_t screen_width_half = screen_width * 0.5f;
  return (x * screen_width_half) + screen_width_half + viewport_position_x;
}
std::uint32_t ViewportTransformShader::DenormalizeY(
    float y, std::uint32_t viewport_position_y,
    std::uint32_t screen_height) const {
  std::uint32_t screen_height_half = screen_height * 0.5f;
  return -(y * screen_height_half) + screen_height_half + viewport_position_y;
}
float ViewportTransformShader::DenormalizeZ(float z, float depth_range_min,
                                            float depth_range_max) const {
  return (z * (depth_range_max - depth_range_min) +
          (depth_range_min + depth_range_max)) *
         0.5f;
}
}  // namespace ho_renderer