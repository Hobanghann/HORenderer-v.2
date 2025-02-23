#ifndef _HORENDERER_MATH_LINEARTRANSFORM_H_
#define _HORENDERER_MATH_LINEARTRANSFORM_H_

#include "math/include/euler_angle.h"
#include "math/include/matrix3x3.h"

namespace ho_renderer {
	class AffineTransform;
class LinearTransform {
 public:
  // constructor
  LinearTransform();
  LinearTransform(const Matrix3x3& matrix);
  LinearTransform(const LinearTransform& transform);
  LinearTransform& operator=(const LinearTransform& transform);
  ~LinearTransform();
  // factory function
  static LinearTransform CreateScaleTransform(const float scale);
  static LinearTransform CreateRotateTransform(const EulerAngle& angle);
  static LinearTransform CreateYawTransform(const float angle);
  static LinearTransform CreateRollTransform(const float angle);
  static LinearTransform CreatePitchTransform(const float angle);
  static LinearTransform CreateInverseScaleTransform(const float scale);
  static LinearTransform CreateInverseRotateTransform(const EulerAngle& angle);
  static LinearTransform CreateInverseYawTransform(const float angle);
  static LinearTransform CreateInverseRollTransform(const float angle);
  static LinearTransform CreateInversePitchTransform(const float angle);
  // compose linear transformation by multiplying arg * this
  LinearTransform& ComposeWith(const LinearTransform& linear_transform);
  LinearTransform GetComposeWith(const LinearTransform& linear_transform);
  Vector3 Transform(const Vector3& vector) const;
  const Matrix3x3& GetMatrix() const;
  // transformation linear transform to affine transforn
  AffineTransform ToAffineTransform() const;

 private:
  Matrix3x3 matrix_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_MATH_LINEARTRANSFORM_H_