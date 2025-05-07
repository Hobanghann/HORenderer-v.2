#include "core/math/include/linear_transform.h"

#include "core/math/include/affine_transform.h"
#include "core/math/include/math_utils.h"
#include "core/math/include/matrix3x3.h"
#include "core/math/include/vector3.h"
#include "core/math/include/vector4.h"

namespace ho_renderer {
LinearTransform::LinearTransform() : matrix_(Matrix3x3::kIdentityMatrix) {}
LinearTransform::LinearTransform(const Matrix3x3& matrix) : matrix_(matrix) {}
LinearTransform::LinearTransform(const LinearTransform& transform) = default;
LinearTransform& LinearTransform::operator=(const LinearTransform& transform) =
    default;
LinearTransform::~LinearTransform() = default;

// factory function
LinearTransform LinearTransform::CreateScaleTransform(float scale) {
  return LinearTransform(scale * Matrix3x3::kIdentityMatrix);
}
LinearTransform LinearTransform::CreateRotationTransform(
    const Vector3& world_right, const Vector3& world_up,
    const Vector3& world_forward) {
  return LinearTransform(Matrix3x3(world_right, world_up, world_forward));
}
LinearTransform LinearTransform::CreateRotationTransform(
    const EulerAngle& euler_angle) {
  float cy = 0.f, sy = 0.f, cp = 0.f, sp = 0.f, cr = 0.f, sr = 0.f;
  MathUtils::SinCosf(sy, cy, euler_angle.yaw_angle());
  MathUtils::SinCosf(sp, cp, euler_angle.pitch_angle());
  MathUtils::SinCosf(sr, cr, euler_angle.roll_angle());

  return LinearTransform(Matrix3x3(
      Vector3(cy * cr + sy * sp * sr, cp * sr, -sy * cr + cy * sp * sr),
      Vector3(-cy * sr + sy * sp * cr, cp * cr, sy * sr + cy * sp * cr),
      Vector3(sy * cp, -sp, cy * cp)));
}
LinearTransform LinearTransform::CreateYawTransform(float angle) {
  float sin, cos;
  MathUtils::SinCosf(sin, cos, angle);
  return LinearTransform(Matrix3x3(Vector3(cos, 0.f, -sin), Vector3::kUnitY,
                                   Vector3(sin, 0.f, cos)));
}
LinearTransform LinearTransform::CreateRollTransform(float angle) {
  float sin, cos;
  MathUtils::SinCosf(sin, cos, angle);
  return LinearTransform(Matrix3x3(Vector3(cos, sin, 0.f),
                                   Vector3(-sin, cos, 0.f), Vector3::kUnitZ));
}

LinearTransform LinearTransform::CreatePitchTransform(float angle) {
  float sin, cos;
  MathUtils::SinCosf(sin, cos, angle);
  return LinearTransform(Matrix3x3(Vector3::kUnitX, Vector3(0.f, cos, sin),
                                   Vector3(0.f, -sin, cos)));
}

LinearTransform LinearTransform::CreateInverseScaleTransform(float scale) {
  return LinearTransform((1.f / scale) * Matrix3x3::kIdentityMatrix);
}
LinearTransform LinearTransform::CreateInverseRotationTransform(
    const Vector3& world_right, const Vector3& world_up,
    const Vector3& world_forward) {
  return LinearTransform(
      Matrix3x3(world_right, world_up, world_forward).Transpose());
}
LinearTransform LinearTransform::CreateInverseRotationTransform(
    const EulerAngle& euler_angle) {
  float cy = 0.f, sy = 0.f, cp = 0.f, sp = 0.f, cr = 0.f, sr = 0.f;
  MathUtils::SinCosf(sy, cy, euler_angle.yaw_angle());
  MathUtils::SinCosf(sp, cp, euler_angle.pitch_angle());
  MathUtils::SinCosf(sr, cr, euler_angle.roll_angle());

  return LinearTransform(
      Matrix3x3(
          Vector3(cy * cr + sy * sp * sr, cp * sr, -sy * cr + cy * sp * sr),
          Vector3(-cy * sr + sy * sp * cr, cp * cr, sy * sr + cy * sp * cr),
          Vector3(sy * cp, -sp, cy * cp))
          .Transpose());
}
LinearTransform LinearTransform::CreateInverseYawTransform(float angle) {
  float sin, cos;
  MathUtils::SinCosf(sin, cos, angle);
  return LinearTransform(Matrix3x3(Vector3(cos, 0.f, -sin), Vector3::kUnitY,
                                   Vector3(sin, 0.f, cos))
                             .Transpose());
}
LinearTransform LinearTransform::CreateInverseRollTransform(float angle) {
  float sin, cos;
  MathUtils::SinCosf(sin, cos, angle);
  return LinearTransform(Matrix3x3(Vector3(cos, sin, 0.f),
                                   Vector3(-sin, cos, 0.f), Vector3::kUnitZ)
                             .Transpose());
}
LinearTransform LinearTransform::CreateInversePitchTransform(float angle) {
  float sin, cos;
  MathUtils::SinCosf(sin, cos, angle);
  return LinearTransform(Matrix3x3(Vector3::kUnitX, Vector3(0.f, cos, sin),
                                   Vector3(0.f, -sin, cos))
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

std::vector<std::string> LinearTransform::ToString() const {
  return matrix_.ToString();
}
}  // namespace ho_renderer