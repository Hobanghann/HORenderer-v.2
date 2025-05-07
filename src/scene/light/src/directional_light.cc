#include "scene/light/include/directional_light.h"

#include <string>

#include "core/math/include/vector3.h"
#include "core/math/include/vector4.h"
#include "graphics/color/include/linear_rgb.h"
#include "scene/light/include/light.h"

namespace ho_renderer {
DirectionalLight::DirectionalLight(const std::string& name,
                                   const LinearRGB& color, float intensity,
                                   const Vector4& direction)
    : Light(name, color, intensity), light_direction_(direction) {}
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

DirectionalLight& DirectionalLight::ResetTransformedDirection() {
  transformed_direction_ = Vector3::kZero;
  return *this;
}

float DirectionalLight::GetIntensityAt(const Vector3& coord) const {
  return light_intensity_;
}

}  // namespace ho_renderer