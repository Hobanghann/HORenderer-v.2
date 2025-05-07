#include "scene/camera/include/camera.h"

#include <string>

#include "core/math/include/linear_transform.h"
#include "core/math/include/math_utils.h"
#include "core/math/include/quaternion_transform.h"
#include "core/math/include/vector3.h"
#include "core/math/include/vector4.h"

namespace ho_renderer {
Camera::Camera(const Camera& camera_object) = default;
Camera::Camera(const std::string& name, const Transform& transform, float fov,
               float aspect_ratio, float near_distance, float far_distance,
               float rotate_velocity, float move_velocity)
    : name_(name),
      transform_(transform),
      fov_(fov),
      aspect_ratio_(aspect_ratio),
      focal_length_(1.f / MathUtils::Tanf(fov * 0.5f)),
      near_distance_(near_distance),
      far_distance_(far_distance),
      rotate_velocity_(rotate_velocity),
      move_velocity_(move_velocity) {}
Camera& Camera::operator=(const Camera& camera_object) = default;
Camera::~Camera() = default;

const std::string& Camera::name() const { return name_; }
const Transform& Camera::transform() const { return transform_; }
float Camera::fov() const { return fov_; }
float Camera::focal_length() const { return focal_length_; }
float Camera::aspect_ratio() const { return aspect_ratio_; }
float Camera::near_distance() const { return near_distance_; }
float Camera::far_distance() const { return far_distance_; }
bool Camera::is_property_changed() const { return is_property_changed_; }

Camera& Camera::set_name(const std::string& name) {
  name_ = name;
  return *this;
}
Camera& Camera::set_transform(const Transform& transform) {
  transform_ = transform;
  return *this;
}
Camera& Camera::set_fov(float fov) {
  fov_ = fov;
  focal_length_ = 1.f / MathUtils::Tanf(fov * 0.5f);
  return *this;
}
Camera& Camera::set_aspect_ratio(float viewport_width, float viewport_height) {
  aspect_ratio_ = viewport_width / viewport_height;
  return *this;
}
Camera& Camera::set_near_distance(float near_distance) {
  near_distance_ = near_distance;
  return *this;
}
Camera& Camera::set_far_distance(float far_distance) {
  far_distance_ = far_distance;
  return *this;
}
Camera& Camera::set_is_property_changed(bool is_property_changed) {
  is_property_changed_ = is_property_changed;
  return *this;
}

// problem : Inverse rotation transformation defined by local axis,
// must be transposed
AffineTransform Camera::GetViewTransform() const {
  AffineTransform inv_rotation_transform =
      LinearTransform::CreateInverseRotationTransform(
          transform_.world_right(), transform_.world_up(),
          transform_.world_forward())
          .ToAffineTransform();
  AffineTransform inv_translation_transform =
      AffineTransform::CreateInverseTranslationTransform(
          transform_.world_coord());
  AffineTransform yaw_180_transform =
      LinearTransform::CreateYawTransform(MathUtils::kPi).ToAffineTransform();
  return inv_translation_transform.ComposeWith(inv_rotation_transform)
      .ComposeWith(yaw_180_transform);
}
AffineTransform Camera::GetProjectionTransform() const {
  float near_minus_far = (near_distance_ - far_distance_);
  if (MathUtils::IsEqual(near_minus_far, 0.f)) {
    near_minus_far = MathUtils::kFloatMin;
  }
  float inv_near_minus_far = 1.f / near_minus_far;
  return AffineTransform(Matrix4x4(
      {focal_length_ / aspect_ratio_, 0.f, 0.f, 0.f},
      {0.f, focal_length_, 0.f, 0.f},
      {0.f, 0.f, (near_distance_ + far_distance_) * inv_near_minus_far, -1.f},
      {0.f, 0.f, (2.f * near_distance_ * far_distance_) * inv_near_minus_far,
       0.f}));
}
AffineTransform Camera::GetReversedProjectionTransform() const {
  float far_minus_near = (far_distance_ - near_distance_);
  if (MathUtils::IsEqual(far_minus_near, 0.f)) {
    far_minus_near = MathUtils::kFloatMin;
  }
  float inv_far_minus_near = 1.f / far_minus_near;
  return AffineTransform(Matrix4x4(
      {focal_length_ / aspect_ratio_, 0.f, 0.f, 0.f},
      {0.f, focal_length_, 0.f, 0.f},
      {0.f, 0.f, far_distance_ * inv_far_minus_near, -1.f},
      {0.f, 0.f, 2.f * far_distance_ * near_distance_ * inv_far_minus_near,
       0.f}));
}

void Camera::Update(InputReceiver& input_receiver, float delta_time) {
  /*Problem: Problem: Changing only the pitch and
yaw angles through mouse input assumes that the object's forward vector aligns
with the world space Z-axis and the object's right vector aligns with the world
space X-axis. However, when the object's position changes, its forward vector no
longer aligns with the world space Z-axis and X-axis, causing issues.

Solution: The mouse movement should modify the object's forward and right
vectors, meaning the rotation should be applied in the object's local axis.
Therefore, the rotated local axis should be computed and then reflected back
into the transform’s Euler angles.
*/
  if (input_receiver.IsPressed(kMOUSE_RBUTTON)) {
    EulerAngle e_angle;
    float mouse_delta_x =
        input_receiver.GetMouseDeltaX() * rotate_velocity_ * delta_time;
    float mouse_delta_y =
        input_receiver.GetMouseDeltaY() * rotate_velocity_ * delta_time;
    e_angle.set_yaw_angle(mouse_delta_x);
    e_angle.set_pitch_angle(mouse_delta_y);
    QuaternionTransform r_transform =
        QuaternionTransform::CreateRotationTransform(e_angle);
    Vector3 transformed_forward =
        r_transform.Transform(transform_.world_forward()).GetNormalized();
    // it's for keep orthogonality
    Vector3 up;
    if (MathUtils::IsEqual(transformed_forward.Dot(Vector3::kUnitY), 1.f)) {
      up = transformed_forward.Cross(Vector3::kUnitX).GetNormalized();
    } else {
      up = Vector3::kUnitY;
    }
    Vector3 transformed_right = up.Cross(transformed_forward).GetNormalized();
    Vector3 transformed_up =
        transformed_forward.Cross(transformed_right).GetNormalized();
    transform_.set_world_forward(transformed_forward);
    transform_.set_world_right(transformed_right);
    transform_.set_world_up(transformed_up);
  }
  Vector3 prev_coord = transform_.world_coord();
  if (input_receiver.IsPressed(kKEY_W)) {
    transform_.set_world_coord(
        prev_coord +
        (move_velocity_ * transform_.world_forward() * delta_time));
  }
  if (input_receiver.IsPressed(kKEY_S)) {
    transform_.set_world_coord(
        prev_coord -
        (move_velocity_ * transform_.world_forward() * delta_time));
  }
  if (input_receiver.IsPressed(kKEY_A)) {
    transform_.set_world_coord(
        prev_coord + (move_velocity_ * transform_.world_right() * delta_time));
  }
  if (input_receiver.IsPressed(kKEY_D)) {
    transform_.set_world_coord(
        prev_coord - (move_velocity_ * transform_.world_right() * delta_time));
  }
}
}  // namespace ho_renderer