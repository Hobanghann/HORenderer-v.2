#ifndef _HORENDERER_LIGHT_BUILDER_H_
#define _HORENDERER_LIGHT_BUILDER_H_

#include <memory>
#include <string>

#include "core/math/include/vector4.h"
#include "graphics/color/include/linear_rgb.h"
#include "scene/light/include/ambient_light.h"
#include "scene/light/include/directional_light.h"
#include "scene/light/include/point_light.h"

namespace ho_renderer {
class LightBuilder {
 public:
  LightBuilder();
  LightBuilder(const LightBuilder&) = delete;
  LightBuilder& operator=(const LightBuilder&) = delete;
  ~LightBuilder();

  LightBuilder& set_name(const std::string& name);
  LightBuilder& set_light_color(const LinearRGB& color);
  LightBuilder& set_light_intensity(float intensity);
  LightBuilder& set_light_direction(const Vector4& direction);
  LightBuilder& set_world_coord(const Vector4& coord);
  LightBuilder& set_constant_attenuation(float attenuation);
  LightBuilder& set_linear_attenuation(float attenuation);
  LightBuilder& set_quadratic_attenuation(float attenuation);

  std::unique_ptr<AmbientLight> BuildAmbientLight() const;
  std::unique_ptr<DirectionalLight> BuildDirectionalLight() const;
  std::unique_ptr<PointLight> BuildPointLight() const;
  void Reset();

 private:
  std::string name_;
  LinearRGB light_color_;
  float light_intensity_;
  Vector4 light_vector_;
  float constant_attenuation_;
  float linear_attenuation_;
  float quadratic_attenuation_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_LIGHT_BUILDER_H_