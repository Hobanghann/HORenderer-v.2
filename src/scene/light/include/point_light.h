#ifndef _HORENDERER_POINT_LIGHT_H_
#define _HORENDERER_POINT_LIGHT_H_

#include <string>

#include "core/math/include/vector4.h"
#include "graphics/color/include/linear_rgb.h"
#include "scene/light/include/light.h"

namespace ho_renderer {
class PointLight : public Light {
 public:
  PointLight() = delete;
  PointLight(const PointLight&) = delete;
  PointLight(const std::string& name, const LinearRGB& color, float intensity,
             const Vector4& coord, float constant_attenuation,
             float linear_attenuation, float quadratic_attenuation);
  PointLight& operator=(const PointLight&) = delete;
  ~PointLight();

  const Vector4& world_coord() const;
  const Vector3& transformed_coord() const;
  float constant_attenuation() const;
  float linear_attenuation() const;
  float quadratic_attenuation() const;

  PointLight& set_world_coord(const Vector4& coord);
  PointLight& set_transformed_coord(const Vector3& coord);
  PointLight& set_constant_attenuation(float attenuation);
  PointLight& set_linear_attenuation(float attenuation);
  PointLight& set_quadratic_attenuation(float attenuation);

  float GetIntensityAt(const Vector3& coord) const override;

 private:
  Vector4 world_coord_;
  Vector3 transformed_coord_;
  float constant_attenuation_;
  float linear_attenuation_;
  float quadratic_attenuation_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_POINT_LIGHT_H_