#include "engine/light/include/directional_light.h"

namespace ho_renderer {
DirectionalLight::DirectionalLight(const std::string& name) : Light(name) {}
DirectionalLight::~DirectionalLight() = default;

const Vector4& DirectionalLight::light_direction() const {
  return light_direction_;
}
const Vector3& DirectionalLight::transformed_direction() const {
  return transformed_direction_;
}

DirectionalLight& DirectionalLight::set_light_direction(
    const Vector4& direction) {
  light_direction_ = direction;
  return *this;
}
DirectionalLight& DirectionalLight::set_transformed_direction(
    const Vector3& transformed_direction) {
  transformed_direction_ = transformed_direction;
  return *this;
}

float DirectionalLight::GetIntensityAt(const Vector3& coordinate) const {
  return light_intensity_;
}

void DirectionalLight::Update(InputReceiver& input_receiver,
                              const float delta_time) {}
}  // namespace ho_renderer