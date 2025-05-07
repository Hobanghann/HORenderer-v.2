#include "scene/light/include/ambient_light.h"

namespace ho_renderer {
AmbientLight::AmbientLight(const std::string& name, const LinearRGB& color,
                           float intensity)
    : Light(name, color, intensity) {}
AmbientLight::~AmbientLight() = default;

float AmbientLight::GetIntensityAt(const Vector3& coord) const {
  return light_intensity_;
}
}  // namespace ho_renderer