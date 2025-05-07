#ifndef _HORENDERER_QUATERINON_ROTATION_TRANSFORM_H_
#define _HORENDERER_QUATERINON_ROTATION_TRANSFORM_H_

#include <string>

#include "core/math/include/euler_angle.h"
#include "core/math/include/matrix3x3.h"
#include "core/math/include/quaternion.h"

namespace ho_renderer {
class QuaternionTransform {
 public:
  QuaternionTransform() = delete;
  QuaternionTransform(const QuaternionTransform& transform);
  explicit QuaternionTransform(const Quaternion& quaternion);
  QuaternionTransform& operator=(const QuaternionTransform& quaternion);
  ~QuaternionTransform();

  static QuaternionTransform CreateRotationTransform(const Vector3& axis,
                                                     float angle);
  static QuaternionTransform CreateRotationTransform(
      const EulerAngle& euler_angle);
  static QuaternionTransform CreatePitchRotateTransform(float angle);
  static QuaternionTransform CreateYawRotateTransform(float angle);
  static QuaternionTransform CreateRollRotateTransform(float angle);
  static QuaternionTransform CreateInverseRotationTransform(const Vector3& axis,
                                                            float angle);
  static QuaternionTransform CreateInverseRotationTransform(
      const EulerAngle& euler_angle);
  static QuaternionTransform CreateInversePitchRotateTransform(float angle);
  static QuaternionTransform CreateInverseYawRotateTransform(float angle);
  static QuaternionTransform CreateInverseRollRotateTransform(float angle);

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

#endif  // _HORENDERER_QUATERINON_TRANSFORM_H_