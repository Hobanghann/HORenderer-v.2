#include "scene/light/include/point_light.h"

#include <string>

#include "core/math/include/vector4.h"
#include "graphics/color/include/linear_rgb.h"
#include "scene/light/include/light.h"

namespace ho_renderer {
PointLight::PointLight(const std::string& name, const LinearRGB& color,
                       float intensity, const Vector4& coord,
                       float constant_attenuation, float linear_attenuation,
                       float quadratic_attenuation)
    : Light(name, color, intensity),
      world_coord_(coord),
      constant_attenuation_(constant_attenuation),
      linear_attenuation_(linear_attenuation),
      quadratic_attenuation_(quadratic_attenuation) {}
PointLight::~PointLight() = default;

const Vector4& PointLight::world_coord() const { return world_coord_; }
const Vector3& PointLight::transformed_coord() const {
  return transformed_coord_;
}
float PointLight::constant_attenuation() const { return constant_attenuation_; }
float PointLight::linear_attenuation() const { return linear_attenuation_; }
float PointLight::quadratic_attenuation() const {
  return quadratic_attenuation_;
}

PointLight& PointLight::set_world_coord(const Vector4& coord) {
  world_coord_ = coord;
  return *this;
}
PointLight& PointLight::set_transformed_coord(
    const Vector3& transformed_coord) {
  transformed_coord_ = transformed_coord;
  return *this;
}
PointLight& PointLight::set_constant_attenuation(float attenuation) {
  constant_attenuation_ = attenuation;
  return *this;
}
PointLight& PointLight::set_linear_attenuation(float attenuation) {
  linear_attenuation_ = attenuation;
  return *this;
}
PointLight& PointLight::set_quadratic_attenuation(float attenuation) {
  quadratic_attenuation_ = attenuation;
  return *this;
}

float PointLight::GetIntensityAt(const Vector3& coord) const {
  float distance = (transformed_coord_ - coord).GetMagnitude();
  float attenuation = constant_attenuation_ + linear_attenuation_ * distance +
                      quadratic_attenuation_ * (distance * distance);
  // set minimum attenuation 0.0001f
  if (attenuation < 0.0001f) {
    attenuation = 0.0001f;
  }
  float attenuated_intensity = light_intensity_ / attenuation;
  // set minimum intensity 0.01
  if (attenuated_intensity < 0.01f) {
    attenuated_intensity = 0.01f;
  }
  return attenuated_intensity;
}

}  // namespace ho_renderer