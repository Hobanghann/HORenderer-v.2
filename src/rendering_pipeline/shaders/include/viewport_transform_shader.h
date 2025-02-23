#ifndef _HORENDERER_RENDERINGPIPELINE_SHADERS_VIEWPORT_TRANSFORM_SHADER_H_
#define _HORENDERER_RENDERINGPIPELINE_SHADERS_VIEWPORT_TRANSFORM_SHADER_H_

#include <cstdint>

#include "math/include/vector3.h"

namespace ho_renderer {
class ViewportTransformShader {
 public:
  ViewportTransformShader();
  ViewportTransformShader(const ViewportTransformShader&) = delete;
  ViewportTransformShader& operator=(const ViewportTransformShader&) = delete;
  ~ViewportTransformShader();

  Vector3 TransformNDC(const Vector3& ndc, const Vector2& viewport_position,
                       uint32_t window_width, uint32_t window_height,
                       float depth_range_min, float depth_range_max) const;

 private:
  uint32_t DenormalizeX(float x, uint32_t viewport_position_x,
                        uint32_t screen_width) const;
  uint32_t DenormalizeY(float y, uint32_t viewport_position_y,
                        uint32_t screen_height) const;
  float DenormalizeZ(float z, float depth_range_min,
                     float depth_range_max) const;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_RENDERINGPIPELINE_SHADERS_VIEWPORT_TRANSFORM_SHADER_H_