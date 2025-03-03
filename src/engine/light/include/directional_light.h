#ifndef _HORENDERER_ENGINE_LIGHT_DIRECTIONAL_LIGHT_H_
#define _HORENDERER_ENGINE_LIGHT_DIRECTIONAL_LIGHT_H_

#include <string>

#include "engine/color/include/linear_rgb.h"
#include "engine/light/include/light.h"
#include "math/include/vector4.h"

namespace ho_renderer {
class DirectionalLight : public Light {
 public:
  DirectionalLight() = delete;
  DirectionalLight(const DirectionalLight&) = delete;
  DirectionalLight& operator=(const DirectionalLight&) = delete;
  explicit DirectionalLight(const std::string& name);
  ~DirectionalLight();

  const Vector4& light_direction() const;
  const Vector3& transformed_direction() const;

  DirectionalLight& set_light_direction(const Vector4& direction);
  DirectionalLight& set_transformed_direction(
      const Vector3& transformed_direction);

  float GetIntensityAt(const Vector3& coordinate) const override;

  void Update(InputReceiver& input_receiver, const float delta_time) override;

 private:
  Vector4 light_direction_;
  Vector3 transformed_direction_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_ENGINE_LIGHT_DIRECTIONAL_LIGHT_H_