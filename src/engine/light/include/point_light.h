#ifndef _HORENDERER_ENGINE_LIGHT_POINT_LIGHT_H_
#define _HORENDERER_ENGINE_LIGHT_POINT_LIGHT_H_

#include <string>

#include "engine/color/include/linear_rgb.h"
#include "engine/light/include/light.h"
#include "math/include/vector4.h"

namespace ho_renderer {
class PointLight : public Light {
 public:
  PointLight() = delete;
  PointLight(const PointLight&) = delete;
  explicit PointLight(const std::string& name);
  PointLight& operator=(const PointLight&) = delete;
  ~PointLight();

  const Vector4& world_coordinate() const;
  const Vector3& transformed_coordinate() const;
  const float constant_attenuation() const;
  const float linear_attenuation() const;
  const float quadratic_attenuation() const;

  PointLight& set_world_coordinate(const Vector4& coordinate);
  PointLight& set_transformed_coordinate(const Vector3& coordinate);
  PointLight& set_constant_attenuation(const float attenuation);
  PointLight& set_linear_attenuation(const float attenuation);
  PointLight& set_quadratic_attenuation(const float attenuation);

  float GetIntensityAt(const Vector3& coordinate) const override;

  void Update(InputReceiver& input_receiver, const float delta_time) override;

 private:
  Vector4 world_coordinate_;
  Vector3 transformed_coordinate_;
  float constant_attenuation_;
  float linear_attenuation_;
  float quadratic_attenuation_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_ENGINE_LIGHT_POINT_LIGHT_H_