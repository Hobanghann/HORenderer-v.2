#ifndef _HORENDERER_DIRECTIONAL_LIGHT_H_
#define _HORENDERER_DIRECTIONAL_LIGHT_H_

#include <string>

#include "core/math/include/vector3.h"
#include "core/math/include/vector4.h"
#include "graphics/color/include/linear_rgb.h"
#include "scene/light/include/light.h"

namespace ho_renderer {
class DirectionalLight : public Light {
 public:
  DirectionalLight() = delete;
  DirectionalLight(const DirectionalLight&) = delete;
  DirectionalLight& operator=(const DirectionalLight&) = delete;
  DirectionalLight(const std::string& name, const LinearRGB& color,
                   float intensity, const Vector4& direction);
  ~DirectionalLight();

  const Vector4& light_direction() const;
  const Vector3& transformed_direction() const;

  DirectionalLight& set_light_direction(const Vector4& direction);
  DirectionalLight& set_transformed_direction(
      const Vector3& transformed_direction);

  DirectionalLight& ResetTransformedDirection();

  float GetIntensityAt(const Vector3& coord) const override;

 private:
  Vector4 light_direction_;
  Vector3 transformed_direction_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_DIRECTIONAL_LIGHT_H_