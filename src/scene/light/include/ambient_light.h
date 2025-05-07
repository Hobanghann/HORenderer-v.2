#ifndef _HORENDERER_AMBIENT_LIGHT_H_
#define _HORENDERER_AMBIENT_LIGHT_H_

#include <string>

#include "graphics/color/include/linear_rgb.h"
#include "scene/light/include/light.h"

namespace ho_renderer {
class AmbientLight : public Light {
 public:
  AmbientLight() = delete;
  AmbientLight(const AmbientLight&) = delete;
  AmbientLight(const std::string& name, const LinearRGB& color,
               float intensity);
  AmbientLight& operator=(const AmbientLight&) = delete;
  ~AmbientLight();

  float GetIntensityAt(const Vector3& coord) const override;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_AMBIENT_LIGHT_H_