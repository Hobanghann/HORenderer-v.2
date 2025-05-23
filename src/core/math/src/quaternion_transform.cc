#include "core/math/include/quaternion_transform.h"

#include <string>

#include "core/math/include/euler_angle.h"
#include "core/math/include/math_utils.h"
#include "core/math/include/matrix3x3.h"
#include "core/math/include/quaternion.h"

namespace ho_renderer {
QuaternionTransform::QuaternionTransform(const QuaternionTransform& transform) =
    default;
QuaternionTransform::QuaternionTransform(const Quaternion& quaternion)
    : quaternion_(quaternion) {}
QuaternionTransform& QuaternionTransform::operator=(
    const QuaternionTransform& quaternion) = default;
QuaternionTransform::~QuaternionTransform() = default;

QuaternionTransform QuaternionTransform::CreateRotationTransform(
    const Vector3& axis, float angle) {
  return QuaternionTransform(
      Quaternion::CreateHalfRotationQuartation(angle, axis));
}
QuaternionTransform QuaternionTransform::CreateRotationTransform(
    const EulerAngle& euler_angle) {
  QuaternionTransform pitch_transform =
      CreatePitchRotateTransform(euler_angle.pitch_angle());
  QuaternionTransform yaw_transform =
      CreateYawRotateTransform(euler_angle.yaw_angle());
  QuaternionTransform roll_transform =
      CreateRollRotateTransform(euler_angle.roll_angle());
  return roll_transform.ComposeWith(yaw_transform).ComposeWith(pitch_transform);
}
QuaternionTransform QuaternionTransform::CreatePitchRotateTransform(
    float angle) {
  return QuaternionTransform(
      Quaternion::CreateHalfRotationQuartation(angle, Vector3::kUnitX));
}
QuaternionTransform QuaternionTransform::CreateYawRotateTransform(float angle) {
  return QuaternionTransform(
      Quaternion::CreateHalfRotationQuartation(angle, Vector3::kUnitY));
}
QuaternionTransform QuaternionTransform::CreateRollRotateTransform(
    float angle) {
  return QuaternionTransform(
      Quaternion::CreateHalfRotationQuartation(angle, Vector3::kUnitZ));
}
QuaternionTransform QuaternionTransform::CreateInverseRotationTransform(
    const Vector3& axis, float angle) {
  return QuaternionTransform(
      Quaternion::CreateHalfRotationQuartation(-angle, axis));
}
QuaternionTransform QuaternionTransform::CreateInverseRotationTransform(
    const EulerAngle& euler_angle) {
  QuaternionTransform pitch_transform =
      CreateInversePitchRotateTransform(euler_angle.pitch_angle());
  QuaternionTransform yaw_transform =
      CreateInverseYawRotateTransform(euler_angle.yaw_angle());
  QuaternionTransform roll_transform =
      CreateInverseRollRotateTransform(euler_angle.roll_angle());
  return pitch_transform.ComposeWith(roll_transform).ComposeWith(yaw_transform);
}
QuaternionTransform QuaternionTransform::CreateInversePitchRotateTransform(
    float angle) {
  return QuaternionTransform(
      Quaternion::CreateHalfRotationQuartation(-angle, Vector3::kUnitX));
}
QuaternionTransform QuaternionTransform::CreateInverseYawRotateTransform(
    float angle) {
  return QuaternionTransform(
      Quaternion::CreateHalfRotationQuartation(-angle, Vector3::kUnitY));
}
QuaternionTransform QuaternionTransform::CreateInverseRollRotateTransform(
    float angle) {
  return QuaternionTransform(
      Quaternion::CreateHalfRotationQuartation(-angle, Vector3::kUnitZ));
}

QuaternionTransform& QuaternionTransform::ComposeWith(
    const QuaternionTransform& transform) {
  quaternion_ = transform.quaternion_ * quaternion_;
  return *this;
}
QuaternionTransform QuaternionTransform::GetComposeWith(
    const QuaternionTransform& transform) const {
  return QuaternionTransform(transform.quaternion_ * quaternion_);
}
Vector3 QuaternionTransform::Transform(const Vector3& vector) const {
  Quaternion q_from_v = Quaternion(vector);
  Quaternion result_q = quaternion_ * q_from_v * quaternion_.GetConjugation();
  return result_q.vector_part();
}

const Quaternion& QuaternionTransform::GetQuaternion() const {
  return quaternion_;
}
Matrix3x3 QuaternionTransform::ToMatrix() const {
  Vector3 col1 = Transform(Vector3::kUnitX);
  Vector3 col2 = Transform(Vector3::kUnitY);
  Vector3 col3 = Transform(Vector3::kUnitZ);
  return Matrix3x3(col1, col2, col3);
}
}  // namespace ho_renderer