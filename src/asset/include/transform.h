#ifndef _HORENDERER_ASSET_TRANSFORM_H_
#define _HORENDERER_ASSET_TRANSFORM_H_

#include "engine/input/include/input_sender.h"
#include "math/include/euler_angle.h"
#include "math/include/vector3.h"

namespace ho_renderer {
class Transform {
 public:
  Transform();
  Transform(const Vector3& position, const EulerAngle& rotation,
            const float& scale);
  Transform(const Transform& transform);
  Transform& operator=(const Transform& transform);
  ~Transform();

  const Vector3& world_coordinate() const;
  const EulerAngle& world_euler_angle() const;
  EulerAngle& get_world_euler_angle();
  const float world_scale() const;
  Transform& set_world_coordinate(const Vector3& position);
  Transform& set_world_euler_angle(const EulerAngle& rotation);
  Transform& set_world_scale(const float& scale);

 private:
  Vector3 world_coordinate_;
  EulerAngle world_euler_angle_;
  float world_scale_;
};
}  // namespace ho_renderer
#endif  // _HORENDERER_ASSET_TRANSFORM_H_