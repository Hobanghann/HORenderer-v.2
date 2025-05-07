#ifndef _HORENDERER_LIGHT_H_
#define _HORENDERER_LIGHT_H_

#include <string>

#include "core/math/include/vector3.h"
#include "graphics/color/include/linear_rgb.h"

namespace ho_renderer {
class Light {
 public:
  Light() = delete;
  Light(const Light& light) = delete;
  Light(const std::string& name, const LinearRGB& color, float intensity);
  Light& operator=(const Light& light) = delete;
  virtual ~Light();

  const std::string& name() const;
  const LinearRGB& light_color() const;
  float light_intensity() const;

  Light& set_name(const std::string& name);
  Light& set_light_color(const LinearRGB& color);
  Light& set_light_intensity(float intensity);

  virtual float GetIntensityAt(const Vector3& coord = Vector3::kZero) const = 0;

 protected:
  std::string name_;
  LinearRGB light_color_;
  float light_intensity_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER__LIGHT_H_