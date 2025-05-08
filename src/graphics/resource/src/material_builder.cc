#include "graphics/resource/include/material_builder.h"

#include <array>
#include <memory>
#include <string>

#include "graphics/color/include/linear_rgb.h"
#include "graphics/resource/include/material.h"
#include "graphics/resource/include/model.h"
#include "graphics/resource/include/texture.h"
#include "graphics/resource/include/texture_type.h"

namespace ho_renderer {

MaterialBuilder::MaterialBuilder()
    : name_("Unnamed Material"),
      ambient_color_(LinearRGB::kDARK_GRAY),
      diffuse_color_(LinearRGB::kGRAY),
      specular_color_(LinearRGB::kWHITE),
      specular_coefficient_(1.f),
      specular_exponent_(2.f),
      opaque_(1.f),
      textures_() {}

MaterialBuilder::~MaterialBuilder() = default;

MaterialBuilder& MaterialBuilder::set_name(const std::string& name) {
  name_ = name;
  return *this;
}

MaterialBuilder& MaterialBuilder::set_ambient_color(const LinearRGB& color) {
  ambient_color_ = color;
  return *this;
}

MaterialBuilder& MaterialBuilder::set_diffuse_color(const LinearRGB& color) {
  diffuse_color_ = color;
  return *this;
}

MaterialBuilder& MaterialBuilder::set_specular_color(const LinearRGB& color) {
  specular_color_ = color;
  return *this;
}
MaterialBuilder& MaterialBuilder::set_specular_coefficient(float coefficient) {
  specular_coefficient_ = coefficient;
  return *this;
}
MaterialBuilder& MaterialBuilder::set_specular_exponent(float exponent) {
  specular_exponent_ = exponent;
  return *this;
}

MaterialBuilder& MaterialBuilder::set_opaque(float opaque) {
  opaque_ = opaque;
  return *this;
}

MaterialBuilder& MaterialBuilder::set_Texture(
    TextureType type, std::unique_ptr<Texture> texture) {
  textures_[type] = std::move(texture);
  return *this;
}

std::unique_ptr<Material> MaterialBuilder::Build(Model* owner) {
  std::unique_ptr<Material> new_mat = std::make_unique<Material>(
      owner, name_, ambient_color_, diffuse_color_, specular_color_,
      specular_coefficient_, specular_exponent_, opaque_, std::move(textures_));
  Reset();
  return new_mat;
}

void MaterialBuilder::Reset() {
  name_ = "Unnamed Material";
  ambient_color_ = LinearRGB::kDARK_GRAY;
  diffuse_color_ = LinearRGB::kGRAY;
  specular_color_ = LinearRGB::kWHITE;
  specular_coefficient_ = 1.f;
  specular_exponent_ = 2.f;
  opaque_ = 1.f;
  for (auto& t : textures_) t = nullptr;
}

}  // namespace ho_renderer
