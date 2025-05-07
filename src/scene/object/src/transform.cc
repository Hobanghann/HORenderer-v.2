#include "scene/object/include/transform.h"

#include "core/math/include/vector3.h"

namespace ho_renderer {
Transform::Transform() = default;
Transform::Transform(const Vector3& position, const Vector3& forward,
                     const Vector3& right, const Vector3& up, float scale)
    : world_coord_(position),
      world_forward_(forward),
      world_right_(right),
      world_up_(up),
      world_scale_(scale) {}
Transform::Transform(const Transform& transform) = default;
Transform& Transform::operator=(const Transform& transform) = default;
Transform::~Transform() = default;

const Vector3& Transform::world_coord() const { return world_coord_; }
const Vector3& Transform::world_forward() const { return world_forward_; }
const Vector3& Transform::world_right() const { return world_right_; }
const Vector3& Transform::world_up() const { return world_up_; }
float Transform::world_scale() const { return world_scale_; }

Transform& Transform::set_world_coord(const Vector3& coord) {
  world_coord_ = coord;
  return *this;
}
Transform& Transform::set_world_forward(const Vector3& forward) {
  world_forward_ = forward;
  return *this;
}
Transform& Transform::set_world_right(const Vector3& right) {
  world_right_ = right;
  return *this;
}
Transform& Transform::set_world_up(const Vector3& up) {
  world_up_ = up;
  return *this;
}
Transform& Transform::set_world_scale(float scale) {
  world_scale_ = scale;
  return *this;
}

}  // namespace ho_renderer