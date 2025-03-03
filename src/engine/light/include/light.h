#ifndef _HORENDERER_ENGINE_LIGHT_LIGHT_H_
#define _HORENDERER_ENGINE_LIGHT_LIGHT_H_

#include <string>

#include "engine/color/include/linear_rgb.h"
#include "engine/input/include/input_listener.h"
#include "math/include/vector3.h"

namespace ho_renderer {
class Light : public InputListener {
 public:
  Light() = delete;
  Light(const Light& light) = delete;
  Light(const std::string& name);
  Light& operator=(const Light& light) = delete;
  virtual ~Light();

  const std::string& name() const;
  const LinearRGB& light_color() const;
  const float light_intensity() const;

  Light& set_name(const std::string& name);
  Light& set_light_color(const LinearRGB& color);
  Light& set_light_intensity(const float intensity);

  virtual float GetIntensityAt(
      const Vector3& coordinate = Vector3::kZero) const = 0;

 protected:
  std::string name_;
  LinearRGB light_color_;
  float light_intensity_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_ENGINE_LIGHT_LIGHT_H_