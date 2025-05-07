#ifndef _HORENDERER_PIPELINE_SETTINGS_H_
#define _HORENDERER_PIPELINE_SETTINGS_H_

#include <cstdint>

#include "core/input/include/input_listener.h"
#include "core/math/include/vector2.h"
#include "graphics/color/include/linear_rgb.h"
#include "graphics/rendering_pipeline/system/include/pipeline_enum.h"

namespace ho_renderer {
class PipelineSettings : public InputListener {
 public:
  PipelineSettings(int viewport_width, int viewport_height);
  PipelineSettings(const PipelineSettings& settings) = delete;
  PipelineSettings& operator=(const PipelineSettings& settings) = delete;
  ~PipelineSettings();

  IndexOrder index_order() const;
  int viewport_width() const;
  int viewport_height() const;
  float depth_range_min() const;
  float depth_range_max() const;
  const LinearRGB& background_color() const;
  const Vector2& viewport_position() const;
  PrimitiveType primitive_type() const;
  BoundingVolumeMode bounding_volume_mode() const;
  InterpolationMode interpolation_mode() const;
  RenderingMode rendering_mode() const;
  ShadingMode shading_mode() const;
  bool is_using_backface_culling() const;
  bool is_using_ambient_lighting() const;
  bool is_using_diffuse_lighting() const;
  bool is_using_specular_lighting() const;
  const LinearRGB& default_ambient_color() const;
  const LinearRGB& default_diffuse_color() const;
  const LinearRGB& default_specular_color() const;
  float default_specular_coefficient() const;
  float default_specular_exponent() const;
  float default_opacity() const;

  PipelineSettings& set_index_order(IndexOrder index_order);
  PipelineSettings& set_viewport_width(int viewport_width);
  PipelineSettings& set_viewport_height(int viewport_height);
  PipelineSettings& set_depth_range_min(float depth_range_min);
  PipelineSettings& set_depth_range_max(float depth_range_min);
  PipelineSettings& set_background_color(const LinearRGB& background_color);
  PipelineSettings& set_viewport_position(const Vector2& viewport_position);
  PipelineSettings& set_primitive_type(PrimitiveType type);
  PipelineSettings& set_bounding_volume_mode(BoundingVolumeMode mode);
  PipelineSettings& set_interpolation_mode(InterpolationMode mode);
  PipelineSettings& set_rendering_mode(RenderingMode mode);
  PipelineSettings& set_shading_mode(ShadingMode mode);
  PipelineSettings& set_is_using_backface_culling(bool arg);
  PipelineSettings& set_is_using_ambient_lighting(bool arg);
  PipelineSettings& set_is_using_diffuse_lighting(bool arg);
  PipelineSettings& set_is_using_specular_lighting(bool arg);
  PipelineSettings& set_default_ambient_color(const LinearRGB& color);
  PipelineSettings& set_default_diffuse_color(const LinearRGB& color);
  PipelineSettings& set_default_specular_color(const LinearRGB& color);
  PipelineSettings& set_default_specular_coefficient(float coefficient);
  PipelineSettings& set_default_specular_exponent(float exp);
  PipelineSettings& set_default_opacity(float opacity);

  void Update(InputReceiver& input_receiver, float delta_time) override;

 private:
  IndexOrder index_order_;
  int viewport_width_;
  int viewport_height_;
  float depth_range_min_;
  float depth_range_max_;
  LinearRGB background_color_;
  Vector2 viewport_position_;
  PrimitiveType primitive_type_;
  BoundingVolumeMode bounding_volume_mode_;
  InterpolationMode interpolation_mode_;
  RenderingMode rendering_mode_;
  ShadingMode shading_mode_;
  bool is_using_backface_culling_;
  bool is_using_ambient_lighting_;
  bool is_using_diffuse_lighting_;
  bool is_using_specular_lighting_;
  LinearRGB default_ambient_color_;
  LinearRGB default_diffuse_color_;
  LinearRGB default_specular_color_;
  float default_specular_coefficient_;
  float default_specular_exponent_;
  float default_opacity_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_PIPELINE_SETTINGS_H_