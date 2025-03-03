#ifndef _HORENDERER_ENGINE_LIGHT_AMBIENT_LIGHT_H_
#define _HORENDERER_ENGINE_LIGHT_AMBIENT_LIGHT_H_

#include <string>

#include "engine/color/include/linear_rgb.h"
#include "engine/light/include/light.h"

namespace ho_renderer {
class AmbientLight : public Light {
 public:
  AmbientLight() = delete;
  AmbientLight(const AmbientLight&) = delete;
  explicit AmbientLight(const std::string name);
  AmbientLight& operator=(const AmbientLight&) = delete;
  ~AmbientLight();

  float GetIntensityAt(const Vector3& coordinate) const override;

  void Update(InputReceiver& input_receiver, const float delta_time) override;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_ENGINE_LIGHT_AMBIENT_LIGHT_H_