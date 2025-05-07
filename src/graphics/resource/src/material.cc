#include "graphics/resource/include/material.h"

#include <cstdint>
#include <string>

#include "graphics/color/include/linear_rgb.h"
#include "graphics/resource/include/texture.h"

namespace ho_renderer {
Material::Material(
    Model* owner, const std::string& name, const LinearRGB& ambient_color,
    const LinearRGB& diffuse_color, const LinearRGB& specular_color,
    float specular_coefficient, float specular_exponent, float opaque,
    std::array<std::unique_ptr<Texture>, TextureType::Last> textures)
    : owner_(owner),
      name_(name),
      ambient_color_(ambient_color),
      diffuse_color_(diffuse_color),
      specular_color_(specular_color),
      specular_coefficient_(specular_coefficient),
      specular_exponent_(specular_exponent),
      opaque_(opaque),
      textures_(std::move(textures)) {}
Material::~Material() = default;

const std::string& Material::name() const { return name_; }
const LinearRGB& Material::ambient_color() const { return ambient_color_; }
const LinearRGB& Material::diffuse_color() const { return diffuse_color_; }
const LinearRGB& Material::specular_color() const { return specular_color_; }
float Material::specular_coefficient() const { return specular_coefficient_; }
float Material::specular_exponent() const { return specular_exponent_; }
float Material::opaque() const { return opaque_; }
const Texture* Material::GetTexture(TextureType type) const {
  return textures_[type].get();
}

}  // namespace ho_renderer