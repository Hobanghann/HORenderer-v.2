#ifndef _HORENDERER_MATERIAL_BUILDER_H_
#define _HORENDERER_MATERIAL_BUILDER_H_

#include <array>
#include <memory>
#include <string>

#include "graphics/color/include/linear_rgb.h"
#include "graphics/resource/include/material.h"
#include "graphics/resource/include/texture.h"
#include "graphics/resource/include/texture_type.h"

namespace ho_renderer {
class Model;
class MaterialBuilder {
 public:
  MaterialBuilder();
  MaterialBuilder(const MaterialBuilder& builder) = delete;
  MaterialBuilder& operator=(const MaterialBuilder& builder) = delete;
  ~MaterialBuilder();

  MaterialBuilder& set_name(const std::string& name);
  MaterialBuilder& set_ambient_color(const LinearRGB& color);
  MaterialBuilder& set_diffuse_color(const LinearRGB& color);
  MaterialBuilder& set_specular_color(const LinearRGB& color);
  MaterialBuilder& set_specular_coefficient(float coefficient);
  MaterialBuilder& set_specular_exponent(float exponent);
  MaterialBuilder& set_opaque(float opaque);
  MaterialBuilder& set_Texture(TextureType type,
                               std::unique_ptr<Texture> texture);

  std::unique_ptr<Material> Build(Model* owner);
  void Reset();

 private:
  std::string name_;
  LinearRGB ambient_color_;
  LinearRGB diffuse_color_;
  LinearRGB specular_color_;
  float specular_coefficient_;
  float specular_exponent_;
  float opaque_;
  std::array<std::unique_ptr<Texture>, TextureType::Last> textures_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_MATERIAL_BUILDER_H_