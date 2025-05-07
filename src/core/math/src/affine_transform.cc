#include "core/math/include/affine_transform.h"

#include <string>
#include <vector>

#include "core/math/include/linear_transform.h"
#include "core/math/include/matrix4x4.h"
#include "core/math/include/vector3.h"
#include "core/math/include/vector4.h"

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

LinearTransform AffineTransform::GetLinearPart() const {
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

std::vector<std::string> AffineTransform::ToString() const {
  return matrix_.ToString();
}
}  // namespace ho_renderer