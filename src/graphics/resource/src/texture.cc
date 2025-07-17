#include "graphics/resource/include/texture.h"

#include <cstdint>
#include <memory>
#include <string>

#include "core/math/include/math_utils.h"
#include "tools/include/debug.h"

namespace ho_renderer {
Texture::Texture(const std::string& path, const std::uint32_t* texels,
                 int texture_width, int texture_height)
    : path_(path),
      texture_width_(texture_width),
      texture_height_(texture_height) {
  ASSERT_MSG(texels != nullptr,
             "Texture::Texture Error: texels pointer must not be null");
  ASSERT_MSG(texture_width > 0 && texture_height > 0,
             "Texture::Texture Error: width and height must be positive");
  int tex_size = texture_width_ * texture_height_;
  for (int i = 0; i < tex_size; i++) {
    texels_.emplace_back(texels[i]);
  }
}
Texture::~Texture() = default;

const std::string& Texture::name() const {
  int found = path_.find_last_of('/');
  return path_.substr(found + 1);
}
int Texture::texture_width() const { return texture_width_; }
int Texture::texture_height() const { return texture_height_; }

const LinearRGB& Texture::GetTexel(float u, float v) const {
  // point filtering
  int x = static_cast<int>(MathUtils::Clamp(0.f, 1.f, u) *
                           static_cast<float>(texture_width_ - 1));
  int y = static_cast<int>(MathUtils::Clamp(0.f, 1.f, v) *
                           static_cast<float>(texture_width_ - 1));
  return texels_[texture_width_ * y + x];
}

Vector3 Texture::GetVector(float u, float v) const {
  // point filtering
  int x = static_cast<int>(MathUtils::Clamp(0.f, 1.f, u) *
                           static_cast<float>(texture_width_ - 1));
  int y = static_cast<int>(MathUtils::Clamp(0.f, 1.f, v) *
                           static_cast<float>(texture_width_ - 1));
  LinearRGB texel = texels_[texture_width_ * y + x];
  return Vector3(texel.red() * 2.f - 1.f, texel.green() * 2.f - 1.f,
                 texel.blue() * 2.f - 1.f);
}
}  // namespace ho_renderer