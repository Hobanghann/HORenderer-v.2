#include "asset/include/camera_object.h"

#include "app/include/debug.h"
#include "math/include/math_utils.h"

namespace ho_renderer {
CameraObject::CameraObject() : rotate_velocity_(MathUtils::kPI / 10.f) {}
CameraObject::CameraObject(const CameraObject& camera_object) = default;
CameraObject::CameraObject(const std::string& name)
    : name_(name), rotate_velocity_(MathUtils::kPI / 10.f) {}
CameraObject& CameraObject::operator=(const CameraObject& camera_object) =
    default;
CameraObject::~CameraObject() = default;

const std::string& CameraObject::name() const { return name_; }
const Transform& CameraObject::transform() const { return transform_; }
float CameraObject::fov() const { return fov_; }
float CameraObject::focal_length() const { return focal_length_; }
float CameraObject::aspect_ratio() const { return aspect_ratio_; }
float CameraObject::near_distance() const { return near_distance_; }
float CameraObject::far_distance() const { return far_distance_; }
bool CameraObject::is_property_changed() const { return is_property_changed_; }

CameraObject& CameraObject::set_name(const std::string& name) {
  name_ = name;
  return *this;
}
CameraObject& CameraObject::set_transform(const Transform& transform) {
  transform_ = transform;
  return *this;
}
CameraObject& CameraObject::set_fov(const float fov) {
  fov_ = fov;
  focal_length_ = 1.f / MathUtils::Tanf(fov * 0.5f);
  return *this;
}
CameraObject& CameraObject::set_aspect_ratio(const float screen_width,
                                             const float screen_height) {
  aspect_ratio_ = screen_width / screen_height;
  return *this;
}
CameraObject& CameraObject::set_near_distance(const float near_distance) {
  near_distance_ = near_distance;
  return *this;
}
CameraObject& CameraObject::set_far_distance(const float far_distance) {
  far_distance_ = far_distance;
  return *this;
}
CameraObject& CameraObject::set_is_property_changed(bool is_property_changed) {
  is_property_changed_ = is_property_changed;
  return *this;
}

void CameraObject::Update(InputReceiver& input_receiver,
                          const float delta_time) {
  if (input_receiver.IsPressed(kKEY_UP)) {
    transform_.get_world_euler_angle().set_pitch_angle(
        transform_.get_world_euler_angle().pitch_angle() +
        rotate_velocity_ * delta_time);
  }
  if (input_receiver.IsPressed(kKEY_DOWN)) {
    transform_.get_world_euler_angle().set_pitch_angle(
        transform_.get_world_euler_angle().pitch_angle() -
        rotate_velocity_ * delta_time);
  }
  if (input_receiver.IsPressed(kKEY_LEFT)) {
    transform_.get_world_euler_angle().set_yaw_angle(
        transform_.get_world_euler_angle().yaw_angle() +
        rotate_velocity_ * delta_time);
  }
  if (input_receiver.IsPressed(kKEY_RIGHT)) {
    transform_.get_world_euler_angle().set_yaw_angle(
        transform_.get_world_euler_angle().yaw_angle() -
        rotate_velocity_ * delta_time);
  }
}
}  // namespace ho_renderer