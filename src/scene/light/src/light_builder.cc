#include "scene/light/include/light_builder.h"

#include <string>

#include "core/math/include/vector4.h"
#include "graphics/color/include/linear_rgb.h"
#include "scene/light/include/ambient_light.h"
#include "scene/light/include/directional_light.h"
#include "scene/light/include/point_light.h"
#include "tools/include/debug.h"

namespace ho_renderer {

LightBuilder::LightBuilder()
    : name_("Unnamed Light"),
      light_color_(LinearRGB::kWHITE),
      light_intensity_(0.f),
      light_vector_(Vector4::kZero),
      constant_attenuation_(0.f),
      linear_attenuation_(0.0f),
      quadratic_attenuation_(0.0f) {}

LightBuilder::~LightBuilder() = default;

LightBuilder& LightBuilder::set_name(const std::string& name) {
  name_ = name;
  return *this;
}

LightBuilder& LightBuilder::set_light_color(const LinearRGB& color) {
  light_color_ = color;
  return *this;
}

LightBuilder& LightBuilder::set_light_intensity(float intensity) {
  light_intensity_ = intensity;
  return *this;
}

LightBuilder& LightBuilder::set_light_direction(const Vector4& direction) {
  light_vector_ = direction;
  return *this;
}

LightBuilder& LightBuilder::set_world_coord(const Vector4& coord) {
  light_vector_ = coord;
  return *this;
}

LightBuilder& LightBuilder::set_constant_attenuation(float attenuation) {
  constant_attenuation_ = attenuation;
  return *this;
}

LightBuilder& LightBuilder::set_linear_attenuation(float attenuation) {
  linear_attenuation_ = attenuation;
  return *this;
}

LightBuilder& LightBuilder::set_quadratic_attenuation(float attenuation) {
  quadratic_attenuation_ = attenuation;
  return *this;
}

std::unique_ptr<AmbientLight> LightBuilder::BuildAmbientLight() const {
  return std::make_unique<AmbientLight>(name_, light_color_, light_intensity_);
}

std::unique_ptr<DirectionalLight> LightBuilder::BuildDirectionalLight() const {
  return std::make_unique<DirectionalLight>(name_, light_color_,
                                            light_intensity_, light_vector_);
}

std::unique_ptr<PointLight> LightBuilder::BuildPointLight() const {
  ASSERT_MSG(constant_attenuation_ != 0.f || linear_attenuation_ != 0.f ||
                 quadratic_attenuation_ != 0.f,
             "LightBuilder::BuildPointLight Error : at least one attenuation "
             "factor must be non-zero");
  return std::make_unique<PointLight>(
      name_, light_color_, light_intensity_, light_vector_,
      constant_attenuation_, linear_attenuation_, quadratic_attenuation_);
}

void LightBuilder::Reset() {
  name_ = "Unnamed Light";
  light_color_ = LinearRGB::kWHITE;
  light_intensity_ = 0.f;
  light_vector_ = Vector4::kZero;
  constant_attenuation_ = 0.f;
  linear_attenuation_ = 0.0f;
  quadratic_attenuation_ = 0.0f;
}

}  // namespace ho_renderer