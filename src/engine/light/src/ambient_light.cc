#include "engine/light/include/ambient_light.h"

namespace ho_renderer {
AmbientLight::AmbientLight(const std::string name) : Light(name) {}
AmbientLight::~AmbientLight() = default;

float AmbientLight::GetIntensityAt(const Vector3& coordinate) const {
  return light_intensity_;
}
void AmbientLight::Update(InputReceiver& input_receiver,
                          const float delta_time) {}
}  // namespace ho_renderer