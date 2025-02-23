#include "math/include/linear_transform.h"

#include "app/include/debug.h"
#include "math/include/affine_transform.h"
#include "math/include/math_utils.h"
#include "math/include/vector3.h"
#include "math/include/vector4.h"

namespace ho_renderer {
LinearTransform::LinearTransform() : matrix_(Matrix3x3::kIdentityMatrix) {}
LinearTransform::LinearTransform(const Matrix3x3& matrix) : matrix_(matrix) {}
LinearTransform::LinearTransform(const LinearTransform& transform) = default;
LinearTransform& LinearTransform::operator=(const LinearTransform& transform) =
    default;
LinearTransform::~LinearTransform() = default;

// factory function
LinearTransform LinearTransform::CreateScaleTransform(const float scale) {
  return LinearTransform(scale * Matrix3x3::kIdentityMatrix);
}
LinearTransform LinearTransform::CreateRotateTransform(
    const EulerAngle& euler_angle) {
  return LinearTransform::CreateRollTransform(euler_angle.roll_angle())
      .ComposeWith(LinearTransform::CreateYawTransform(euler_angle.yaw_angle()))
      .ComposeWith(
          LinearTransform::CreatePitchTransform(euler_angle.pitch_angle()));
}
LinearTransform LinearTransform::CreateYawTransform(const float angle) {
  return LinearTransform(
      Matrix3x3(Vector3(MathUtils::Cosf(angle), 0.f, -MathUtils::Sinf(angle)),
                Vector3::kUnitY,
                Vector3(MathUtils::Sinf(angle), 0.f, MathUtils::Cosf(angle))));
}
LinearTransform LinearTransform::CreateRollTransform(const float angle) {
  return LinearTransform(
      Matrix3x3(Vector3(MathUtils::Cosf(angle), MathUtils::Sinf(angle), 0.f),
                Vector3(-MathUtils::Sinf(angle), MathUtils::Cosf(angle), 0.f),
                Vector3::kUnitZ));
}

LinearTransform LinearTransform::CreatePitchTransform(const float angle) {
  return LinearTransform(
      Matrix3x3(Vector3::kUnitX,
                Vector3(0.f, MathUtils::Cosf(angle), MathUtils::Sinf(angle)),
                Vector3(0.f, -MathUtils::Sinf(angle), MathUtils::Cosf(angle))));
}

LinearTransform LinearTransform::CreateInverseScaleTransform(
    const float scale) {
  return LinearTransform((1.f / scale) * Matrix3x3::kIdentityMatrix);
}
LinearTransform LinearTransform::CreateInverseRotateTransform(
    const EulerAngle& euler_angle) {
  return CreateInversePitchTransform(euler_angle.pitch_angle())
      .ComposeWith(CreateInverseYawTransform(euler_angle.yaw_angle())
                       .ComposeWith(CreateInverseRollTransform(
                           euler_angle.roll_angle())));
}
LinearTransform LinearTransform::CreateInverseYawTransform(const float angle) {
  return LinearTransform(
      Matrix3x3(Vector3(MathUtils::Cosf(angle), 0.f, -MathUtils::Sinf(angle)),
                Vector3::kUnitY,
                Vector3(MathUtils::Sinf(angle), 0.f, MathUtils::Cosf(angle)))
          .Transpose());
}
LinearTransform LinearTransform::CreateInverseRollTransform(const float angle) {
  return LinearTransform(
      Matrix3x3(Vector3(MathUtils::Cosf(angle), MathUtils::Sinf(angle), 0.f),
                Vector3(-MathUtils::Sinf(angle), MathUtils::Cosf(angle), 0.f),
                Vector3::kUnitZ)
          .Transpose());
}
LinearTransform LinearTransform::CreateInversePitchTransform(
    const float angle) {
  return LinearTransform(
      Matrix3x3(Vector3::kUnitX,
                Vector3(0.f, MathUtils::Cosf(angle), MathUtils::Sinf(angle)),
                Vector3(0.f, -MathUtils::Sinf(angle), MathUtils::Cosf(angle)))
          .Transpose());
}

LinearTransform& LinearTransform::ComposeWith(
    const LinearTransform& linear_transform) {
  matrix_ = linear_transform.matrix_ * matrix_;
  return *this;
}

LinearTransform LinearTransform::GetComposeWith(
    const LinearTransform& linear_transform) {
  return LinearTransform(linear_transform.matrix_ * matrix_);
}

Vector3 LinearTransform::Transform(const Vector3& vector) const {
  return matrix_ * vector;
}

const Matrix3x3& LinearTransform::GetMatrix() const { return matrix_; }

AffineTransform LinearTransform::ToAffineTransform() const {
  return AffineTransform(Matrix4x4(Vector4(matrix_.col1()),
                                   Vector4(matrix_.col2()),
                                   Vector4(matrix_.col3()), Vector4::kUnitW));
}
}  // namespace ho_renderer