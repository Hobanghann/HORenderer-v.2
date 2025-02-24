#include "math/include/affine_transform.h"

#include "app/include/debug.h"
#include "asset/include/camera_object.h"
#include "asset/include/game_object.h"
#include "math/include/linear_transform.h"
#include "math/include/math_utils.h"
#include "math/include/matrix3x3.h"
#include "math/include/matrix4x4.h"
#include "math/include/quaternion_transform.h"
#include "math/include/vector3.h"
#include "math/include/vector4.h"

namespace ho_renderer {
AffineTransform::AffineTransform() : matrix_(Matrix4x4::kIdentityMatrix) {}
AffineTransform::AffineTransform(const AffineTransform& transform) = default;
AffineTransform::AffineTransform(const Matrix4x4& affine_matrix)
    : matrix_(affine_matrix) {}
AffineTransform& AffineTransform::operator=(const AffineTransform& transform) =
    default;
AffineTransform::~AffineTransform() = default;

AffineTransform AffineTransform::CreateTranslationTransform(
    const Vector3& translation_vector) {
  Matrix4x4 affine_matrix = Matrix4x4::kIdentityMatrix;
  affine_matrix.set_col4(translation_vector.ToHomogeneousCoordinate());
  return AffineTransform(affine_matrix);
}
AffineTransform AffineTransform::CreateInverseTranslationTransform(
    const Vector3& translation_vector) {
  Matrix4x4 affine_matrix = Matrix4x4::kIdentityMatrix;
  affine_matrix.set_col4((-1.f * translation_vector).ToHomogeneousCoordinate());
  return AffineTransform(affine_matrix);
}
AffineTransform AffineTransform::CreateModelingTransform(
    const GameObject& game_object) {
  AffineTransform scale_transform = LinearTransform::CreateScaleTransform(
                                        game_object.transform().world_scale())
                                        .ToAffineTransform();
  AffineTransform rotation_transform =
      LinearTransform(QuaternionTransform::CreateRotateTransform(
                          game_object.transform().world_euler_angle())
                          .ToMatrix())
          .ToAffineTransform();
  AffineTransform translation_transform =
      AffineTransform::CreateTranslationTransform(
          game_object.transform().world_coordinate());
  return scale_transform.ComposeWith(rotation_transform)
      .ComposeWith(translation_transform);
}
AffineTransform AffineTransform::CreateViewTransform(
    const CameraObject& camera_object) {
  AffineTransform inv_rotation_transform =
      LinearTransform(QuaternionTransform::CreateInverseRotateTransform(
                          camera_object.transform().world_euler_angle())
                          .ToMatrix())
          .ToAffineTransform();
  AffineTransform inv_translation_transform =
      AffineTransform::CreateInverseTranslationTransform(
          camera_object.transform().world_coordinate());
  AffineTransform yaw_180_transform =
      LinearTransform::CreateYawTransform(MathUtils::kPI).ToAffineTransform();
  return inv_translation_transform.ComposeWith(inv_rotation_transform)
      .ComposeWith(yaw_180_transform);
}
AffineTransform AffineTransform::CreateProjectionTransform(
    const CameraObject& camera_object) {
  float near_minus_far =
      (camera_object.near_distance() - camera_object.far_distance());
  if (MathUtils::IsEqual(near_minus_far, 0.f)) {
    near_minus_far = MathUtils::kFLOAT_MIN;
  }
  float inv_near_minus_far = 1.f / near_minus_far;
  return AffineTransform(Matrix4x4(
      {camera_object.focal_length() / camera_object.aspect_ratio(), 0.f, 0.f,
       0.f},
      {0.f, camera_object.focal_length(), 0.f, 0.f},
      {0.f, 0.f,
       (camera_object.near_distance() + camera_object.far_distance()) *
           inv_near_minus_far,
       -1.f},
      {0.f, 0.f,
       (2.f * camera_object.near_distance() * camera_object.far_distance()) *
           inv_near_minus_far,
       0.f}));
}
AffineTransform AffineTransform::CreateReversedProjectionTransform(
    const CameraObject& camera_object) {
  float far_minus_near =
      (camera_object.far_distance() - camera_object.near_distance());
  if (MathUtils::IsEqual(far_minus_near, 0.f)) {
    far_minus_near = MathUtils::kFLOAT_MIN;
  }
  float inv_far_minus_near = 1.f / far_minus_near;
  return AffineTransform(Matrix4x4(
      {camera_object.focal_length() / camera_object.aspect_ratio(), 0.f, 0.f,
       0.f},
      {0.f, camera_object.focal_length(), 0.f, 0.f},
      {0.f, 0.f, camera_object.far_distance() * inv_far_minus_near, -1.f},
      {0.f, 0.f,
       2.f * camera_object.far_distance() * camera_object.near_distance() *
           inv_far_minus_near,
       0.f}));
}

LinearTransform AffineTransform::ExtractLinearTransform() const {
  return LinearTransform(Matrix3x3(matrix_.col1().ToVector3(),
                                   matrix_.col2().ToVector3(),
                                   matrix_.col3().ToVector3()));
}

AffineTransform& AffineTransform::ComposeWith(
    const AffineTransform& affine_transform) {
  matrix_ = affine_transform.matrix_ * matrix_;
  return *this;
}

AffineTransform AffineTransform::GetComposeWith(
    const AffineTransform& affine_transform) const {
  return AffineTransform(affine_transform.matrix_ * matrix_);
}

Vector4 AffineTransform::Transform(const Vector4& vector) const {
  return matrix_ * vector;
}

const Matrix4x4& AffineTransform::matrix() const { return matrix_; }
}  // namespace ho_renderer