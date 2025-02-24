#ifndef _HORENDERER_MATH_QUATERINON_ROTATION_TRANSFORM_H_
#define _HORENDERER_MATH_QUATERINON_ROTATION_TRANSFORM_H_

#include "math/include/euler_angle.h"
#include "math/include/matrix3x3.h"
#include "math/include/quaternion.h"

namespace ho_renderer {
class QuaternionTransform {
 public:
  QuaternionTransform() = delete;
  QuaternionTransform(const QuaternionTransform& transform);
  explicit QuaternionTransform(const Quaternion& quaternion);
  QuaternionTransform& operator=(const QuaternionTransform& quaternion);
  ~QuaternionTransform();

  static QuaternionTransform CreateRotateTransform(const Vector3& axis,
                                                   const float angle);
  static QuaternionTransform CreateRotateTransform(
      const EulerAngle& euler_angle);
  static QuaternionTransform CreatePitchRotateTransform(const float angle);
  static QuaternionTransform CreateYawRotateTransform(const float angle);
  static QuaternionTransform CreateRollRotateTransform(const float angle);
  static QuaternionTransform CreateInverseRotateTransform(const Vector3& axis,
                                                          const float angle);
  static QuaternionTransform CreateInverseRotateTransform(
      const EulerAngle& euler_angle);
  static QuaternionTransform CreateInversePitchRotateTransform(
      const float angle);
  static QuaternionTransform CreateInverseYawRotateTransform(const float angle);
  static QuaternionTransform CreateInverseRollRotateTransform(
      const float angle);

  QuaternionTransform& ComposeWith(const QuaternionTransform& transform);
  QuaternionTransform GetComposeWith(
      const QuaternionTransform& transform) const;
  Vector3 Transform(const Vector3& vector) const;

  const Quaternion& GetQuaternion() const;
  Matrix3x3 ToMatrix() const;

 private:
  Quaternion quaternion_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_MATH_QUATERINON_TRANSFORM_H_