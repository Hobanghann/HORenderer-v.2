#include "scene/camera/include/camera_builder.h"

#include <memory>
#include <string>

#include "core/math/include/math_utils.h"
#include "core/math/include/vector3.h"
#include "scene/camera/include/camera.h"
#include "tools/include/debug.h"

namespace ho_renderer {
CameraBuilder::CameraBuilder()
    : name_("Unnamed Camera"),
      fov_(0.f),
      viewport_width_(0.f),
      viewport_height_(0.f),
      near_distance_(0.f),
      far_distance_(0.f),
      rotate_velocity_(0.f),
      move_velocity_(0.f),
      world_coord_(Vector3::kZero),
      world_forward_(-Vector3::kUnitZ),
      world_right_(-Vector3::kUnitX),
      world_up_(Vector3::kUnitY) {}
CameraBuilder::~CameraBuilder() = default;
CameraBuilder& CameraBuilder::set_name(const std::string& name) {
  name_ = name;
  return *this;
}

CameraBuilder& CameraBuilder::set_fov(float fov) {
  fov_ = fov;
  return *this;
}

CameraBuilder& CameraBuilder::set_viewport_width(float viewport_width) {
  viewport_width_ = viewport_width;
  return *this;
}

CameraBuilder& CameraBuilder::set_viewport_height(float viewport_height) {
  viewport_height_ = viewport_height;
  return *this;
}

CameraBuilder& CameraBuilder::set_near_distance(float near_distance) {
  near_distance_ = near_distance;
  return *this;
}

CameraBuilder& CameraBuilder::set_far_distance(float far_distance) {
  far_distance_ = far_distance;
  return *this;
}

CameraBuilder& CameraBuilder::set_rotate_velocity(float rotate_velocity) {
  rotate_velocity_ = rotate_velocity;
  return *this;
}
CameraBuilder& CameraBuilder::set_move_velocity(float move_velocity) {
  move_velocity_ = move_velocity;
  return *this;
}
CameraBuilder& CameraBuilder::set_world_coord(const Vector3& world_coord) {
  world_coord_ = world_coord;
  return *this;
}

CameraBuilder& CameraBuilder::set_world_forward(const Vector3& world_forward) {
  world_forward_ = world_forward;
  return *this;
}

CameraBuilder& CameraBuilder::set_world_right(const Vector3& world_right) {
  world_right_ = world_right;
  return *this;
}

CameraBuilder& CameraBuilder::set_world_up(const Vector3& world_up) {
  world_up_ = world_up;
  return *this;
}

std::unique_ptr<Camera> CameraBuilder::Build() const {
  ASSERT_MSG(MathUtils::IsNotEqual(fov_, 0.f),
             "CameraBuilder::Build Error : fov must not be zero");
  ASSERT_MSG(MathUtils::IsNotEqual(viewport_width_, 0.f),
             "CameraBuilder::Build Error : viewport_width must not be zero");
  ASSERT_MSG(MathUtils::IsNotEqual(viewport_height_, 0.f),
             "CameraBuilder::Build Error : viewport_height must not be zero");
  ASSERT_MSG(MathUtils::IsNotEqual(far_distance_, 0.f),
             "CameraBuilder::Build Error : far_distance must not be zero");
  if (MathUtils::IsEqual(fov_, 0.f) ||
      MathUtils::IsEqual(viewport_width_, 0.f) ||
      MathUtils::IsEqual(viewport_height_, 0.f) ||
      MathUtils::IsEqual(far_distance_, 0.f)) {
    return nullptr;
  }
  return std::make_unique<Camera>(
      name_,
      Transform(world_coord_, world_forward_, world_right_, world_up_, 0.f),
      fov_, viewport_width_ / viewport_height_, near_distance_, far_distance_,
      rotate_velocity_, move_velocity_);
}

void CameraBuilder::Reset() {
  name_ = "Unnamed Camera";
  fov_ = 0.f;
  viewport_width_ = 0.f;
  viewport_height_ = 0.f;
  near_distance_ = 0.f;
  far_distance_ = 0.f;
  rotate_velocity_ = 0.f;
  move_velocity_ = 0.f;
  world_coord_ = Vector3::kZero;
  world_forward_ = -Vector3::kUnitZ;
  world_right_ = -Vector3::kUnitX;
  world_up_ = Vector3::kUnitY;
}

}  // namespace ho_renderer