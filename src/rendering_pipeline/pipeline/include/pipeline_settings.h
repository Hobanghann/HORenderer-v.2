#ifndef _HORENDERER_RENDERINGPIPELINE_PIPELINEOBJECTS_PIPELINESETTINGS_H_
#define _HORENDERER_RENDERINGPIPELINE_PIPELINEOBJECTS_PIPELINESETTINGS_H_

#include <cstdint>

#include "engine/color/include/linear_rgb.h"
#include "engine/input/include/input_listener.h"
#include "math/include/vector2.h"

namespace ho_renderer {
enum PrimitiveType { kPOINT, kLINE, kTRIANGLE };
enum BoundingVolumeMode { kSPHERE, kAABB };
enum InterpolationMode { kAFFINE, kPERSPECTIVE_CORRECT };
enum RenderingMode { kWIRE_FRAME, kFILL, kTEXTURE_MAPPING };
class PipelineSettings : public InputListener {
 public:
  PipelineSettings();
  PipelineSettings(const PipelineSettings& settings) = delete;
  PipelineSettings& operator=(const PipelineSettings& settings) = delete;
  ~PipelineSettings();

  const uint32_t screen_width() const;
  const uint32_t screen_height() const;
  const float depth_range_min() const;
  const float depth_range_max() const;
  const LinearRGB& background_color() const;
  const Vector2& viewport_position() const;
  const PrimitiveType primitive_type() const;
  const BoundingVolumeMode bounding_volume_mode() const;
  const InterpolationMode interpolation_mode() const;
  const RenderingMode rendering_mode() const;
  bool is_using_backface_culling() const;
  bool is_using_diffuse_lighting() const;
  bool is_using_specular_lighting() const;

  PipelineSettings& set_screen_width(const uint32_t& screen_width);
  PipelineSettings& set_screen_height(const uint32_t& screen_height);
  PipelineSettings& set_depth_range_min(float depth_range_min);
  PipelineSettings& set_depth_range_max(float depth_range_min);
  PipelineSettings& set_background_color(const LinearRGB& background_color);
  PipelineSettings& set_viewport_position(const Vector2& viewport_position);
  PipelineSettings& set_primitive_type(PrimitiveType type);
  PipelineSettings& set_bounding_volume_mode(BoundingVolumeMode mode);
  PipelineSettings& set_interpolation_mode(InterpolationMode mode);
  PipelineSettings& set_rendering_mode(RenderingMode mode);
  PipelineSettings& set_is_using_backface_culling(bool arg);
  PipelineSettings& set_is_using_diffuse_lighting(bool arg);
  PipelineSettings& set_is_using_specular_lighting(bool arg);

  void Update(InputReceiver& input_receiver, const float delta_time) override;

 private:
  uint32_t screen_width_;
  uint32_t screen_height_;
  float depth_range_min_;
  float depth_range_max_;
  LinearRGB background_color_;
  Vector2 viewport_position_;
  PrimitiveType primitive_type_;
  BoundingVolumeMode bounding_volume_mode_;
  bool is_sphere_mode_;
  InterpolationMode interpolation_mode_;
  bool is_affine_mode_;
  RenderingMode rendering_mode_;
  bool is_using_backface_culling_;
  bool is_using_diffuse_lighting_;
  bool is_using_specular_lighting_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_RENDERINGPIPELINE_PIPELINEOBJECTS_RENDERINGSTATE_H_