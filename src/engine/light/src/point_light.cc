#include "engine/light/include/point_light.h"

#include "math/include/math_utils.h"

namespace ho_renderer {
PointLight::PointLight(const std::string& name) : Light(name) {}
PointLight::~PointLight() = default;

const Vector4& PointLight::world_coordinate() const {
  return world_coordinate_;
}
const Vector3& PointLight::transformed_coordinate() const {
  return transformed_coordinate_;
}
const float PointLight::constant_attenuation() const {
  return constant_attenuation_;
}
const float PointLight::linear_attenuation() const {
  return linear_attenuation_;
}
const float PointLight::quadratic_attenuation() const {
  return quadratic_attenuation_;
}

PointLight& PointLight::set_world_coordinate(const Vector4& coordinate) {
  world_coordinate_ = coordinate;
  return *this;
}
PointLight& PointLight::set_transformed_coordinate(
    const Vector3& transformed_coordinate) {
  transformed_coordinate_ = transformed_coordinate;
  return *this;
}
PointLight& PointLight::set_constant_attenuation(const float attenuation) {
  constant_attenuation_ = attenuation;
  return *this;
}
PointLight& PointLight::set_linear_attenuation(const float attenuation) {
  linear_attenuation_ = attenuation;
  return *this;
}
PointLight& PointLight::set_quadratic_attenuation(const float attenuation) {
  quadratic_attenuation_ = attenuation;
  return *this;
}

float PointLight::GetIntensityAt(const Vector3& coordinate) const {
  float distance = (transformed_coordinate_ - coordinate).GetMagnitude();
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

void PointLight::Update(InputReceiver& input_receiver, const float delta_time) {
}
}  // namespace ho_renderer