#ifndef _HORENDERER_LINEAR_TRANSFORM_H_
#define _HORENDERER_LINEAR_TRANSFORM_H_

#include <string>
#include <vector>

#include "core/math/include/euler_angle.h"
#include "core/math/include/matrix3x3.h"
#include "core/math/include/vector3.h"

namespace ho_renderer {
class AffineTransform;
class LinearTransform {
 public:
  // constructor
  LinearTransform();
  explicit LinearTransform(const Matrix3x3& matrix);
  LinearTransform(const LinearTransform& transform);
  LinearTransform& operator=(const LinearTransform& transform);
  ~LinearTransform();
  // factory function
  static LinearTransform CreateScaleTransform(float scale);
  static LinearTransform CreateRotationTransform(const Vector3& world_right,
                                                 const Vector3& world_up,
                                                 const Vector3& world_forward);
  static LinearTransform CreateRotationTransform(const EulerAngle& angle);
  static LinearTransform CreateYawTransform(float angle);
  static LinearTransform CreateRollTransform(float angle);
  static LinearTransform CreatePitchTransform(float angle);
  static LinearTransform CreateInverseScaleTransform(float scale);
  static LinearTransform CreateInverseRotationTransform(
      const Vector3& world_right, const Vector3& world_up,
      const Vector3& world_forward);
  static LinearTransform CreateInverseRotationTransform(
      const EulerAngle& angle);
  static LinearTransform CreateInverseYawTransform(float angle);
  static LinearTransform CreateInverseRollTransform(float angle);
  static LinearTransform CreateInversePitchTransform(float angle);
  // compose linear transformation by multiplying arg * this
  LinearTransform& ComposeWith(const LinearTransform& linear_transform);
  LinearTransform GetComposeWith(const LinearTransform& linear_transform);
  Vector3 Transform(const Vector3& vector) const;
  const Matrix3x3& GetMatrix() const;
  // transformation linear transform to affine transforn
  AffineTransform ToAffineTransform() const;

  std::vector<std::string> ToString() const;

 private:
  Matrix3x3 matrix_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_LINEAR_TRANSFORM_H_