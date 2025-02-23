#include "asset/include/transform.h"

#include "app/include/debug.h"
#include "engine/include/input_manager.h"

namespace ho_renderer {
Transform::Transform() = default;
Transform::Transform(const Vector3& coordinate, const EulerAngle& angle,
                     const float& scale)
    : world_coordinate_(coordinate),
      world_euler_angle_(angle),
      world_scale_(scale) {}
Transform::Transform(const Transform& transform) = default;
Transform& Transform::operator=(const Transform& transform) = default;
Transform::~Transform() = default;

const Vector3& Transform::world_coordinate() const { return world_coordinate_; }
const EulerAngle& Transform::world_euler_angle() const {
  return world_euler_angle_;
}
EulerAngle& Transform::get_world_euler_angle() { return world_euler_angle_; }
const float Transform::world_scale() const { return world_scale_; }

Transform& Transform::set_world_coordinate(const Vector3& coordinate) {
  world_coordinate_ = coordinate;
  return *this;
}
Transform& Transform::set_world_euler_angle(const EulerAngle& angle) {
  world_euler_angle_ = angle;
  return *this;
}
Transform& Transform::set_world_scale(const float& scale) {
  world_scale_ = scale;
  return *this;
}

}  // namespace ho_renderer