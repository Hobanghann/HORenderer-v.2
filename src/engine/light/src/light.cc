#include "engine/light/include/light.h"

namespace ho_renderer {
Light::Light(const std::string& name) : name_(name) {}
Light::~Light() = default;

const std::string& Light::name() const { return name_; }
const LinearRGB& Light::light_color() const { return light_color_; }
const float Light::light_intensity() const { return light_intensity_; }

Light& Light::set_name(const std::string& name) {
  name_ = name;
  return *this;
}
Light& Light::set_light_color(const LinearRGB& color) {
  light_color_ = color;
  return *this;
}
Light& Light::set_light_intensity(const float intensity) {
  light_intensity_ = intensity;
  return *this;
}

}  // namespace ho_renderer