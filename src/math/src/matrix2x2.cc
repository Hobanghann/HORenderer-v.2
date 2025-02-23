#include "math/include/matrix2x2.h"

#include "app/include/debug.h"
#include "math/include/matrix3x3.h"
#include "math/include/vector2.h"
#include "math/include/vector3.h"

namespace ho_renderer {
const Matrix2x2 Matrix2x2::kIdentityMatrix =
    Matrix2x2(Vector2::kUnitX, Vector2::kUnitY);

Matrix2x2::Matrix2x2() = default;
Matrix2x2::Matrix2x2(const Vector2& col1, const Vector2& col2)
    : col1_(col1), col2_(col2) {}
Matrix2x2::Matrix2x2(const Matrix2x2&) = default;
Matrix2x2& Matrix2x2::operator=(const Matrix2x2&) = default;
Matrix2x2::~Matrix2x2() = default;
// getter and setter
Vector2 Matrix2x2::col1() const { return col1_; }
Vector2 Matrix2x2::col2() const { return col2_; }
Matrix2x2& Matrix2x2::set_col1(const Vector2& vector) {
  col1_ = vector;
  return *this;
}
Matrix2x2& Matrix2x2::set_col2(const Vector2& vector) {
  col2_ = vector;
  return *this;
}
// row getter
Vector2 Matrix2x2::GetRow1() const { return Vector2(col1_.x(), col2_.x()); }
Vector2 Matrix2x2::GetRow2() const { return Vector2(col1_.y(), col2_.y()); }
// addition
Matrix2x2 Matrix2x2::operator+(const Matrix2x2& matrix) const {
  return Matrix2x2(col1_ + matrix.col1(), col2_ + matrix.col2());
}
Matrix2x2& Matrix2x2::operator+=(const Matrix2x2& matrix) {
  col1_ += matrix.col1();
  col2_ += matrix.col2();
  return *this;
}
// matrix multiplication
Matrix2x2 Matrix2x2::operator*(const Matrix2x2& matrix) const {
  return Matrix2x2(
      Vector2(GetRow1().Dot(matrix.col1_), GetRow2().Dot(matrix.col1_)),
      Vector2(GetRow1().Dot(matrix.col2_), GetRow2().Dot(matrix.col2_)));
}

Matrix2x2& Matrix2x2::operator*=(const Matrix2x2& matrix) {
  col1_.set_x(GetRow1().Dot(matrix.col1_));
  col1_.set_y(GetRow2().Dot(matrix.col1_));
  col2_.set_x(GetRow1().Dot(matrix.col2_));
  col2_.set_y(GetRow2().Dot(matrix.col2_));
  return *this;
}

Vector2 Matrix2x2::operator*(const Vector2& vector) const {
  return Vector2(GetRow1().Dot(vector), GetRow2().Dot(vector));
}

ho_renderer::Matrix2x2 ho_renderer::Matrix2x2::Transpose() const {
  return Matrix2x2(GetRow1(), GetRow2());
}
}  // namespace ho_renderer