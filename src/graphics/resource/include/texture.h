#ifndef _HORENDERER_TEXTURE_H_
#define _HORENDERER_TEXTURE_H_

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "graphics/color/include/linear_rgb.h"
#include "core/math/include/vector3.h"

namespace ho_renderer {
class Texture {
 public:
  Texture() = delete;
  Texture(const Texture& texture) = delete;
  Texture(const std::string& path, const std::uint32_t* texels,
          int texture_width, int texture_height);
  Texture& operator=(const Texture& texture) = delete;
  ~Texture();

  const std::string& name() const;
  int texture_width() const;
  int texture_height() const;

  const LinearRGB& GetTexel(float u, float v) const;
  Vector3 GetVector(float u, float v) const;

 private:
  std::string path_;
  std::vector<LinearRGB> texels_;
  int texture_width_;
  int texture_height_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_TEXTURE_H_