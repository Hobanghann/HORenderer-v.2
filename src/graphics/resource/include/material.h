#ifndef _HORENDERER_MATERIAL_H_
#define _HORENDERER_MATERIAL_H_

#include <array>
#include <cstdint>
#include <string>

#include "graphics/color/include/linear_rgb.h"
#include "graphics/resource/include/texture.h"
#include "graphics/resource/include/texture_type.h"

namespace ho_renderer {
class Model;
class Material {
 public:
  Material() = delete;
  Material(const Material& material) = delete;
  Material(Model* owner, const std::string& name,
           const LinearRGB& ambient_color, const LinearRGB& diffuse_color,
           const LinearRGB& specular_color, float specular_coefficient,
           float specular_exponent, float opaque,
           std::array<std::unique_ptr<Texture>, TextureType::Last> textures);
  Material& operator=(const Material& material) = delete;
  ~Material();

  const std::string& name() const;
  const LinearRGB& ambient_color() const;
  const LinearRGB& diffuse_color() const;
  const LinearRGB& specular_color() const;
  float specular_coefficient() const;
  float specular_exponent() const;
  float opaque() const;
  const Texture* GetTexture(TextureType type) const;

 private:
  std::string name_;
  LinearRGB ambient_color_;
  LinearRGB diffuse_color_;
  LinearRGB specular_color_;
  float specular_coefficient_;
  float specular_exponent_;
  float opaque_;  // used as alpha value in ARGB format.
  std::array<std::unique_ptr<Texture>, TextureType::Last> textures_;

  Model* owner_;
};
}  // namespace ho_renderer
#endif  // _HORENDERER_MATERIAL_H_