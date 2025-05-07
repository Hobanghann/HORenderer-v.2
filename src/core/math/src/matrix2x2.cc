#include "core/math/include/matrix2x2.h"

#include <string>
#include <vector>

#include "core/math/include/vector2.h"

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
  return Matrix2x2(col1_ + matrix.col1_, col2_ + matrix.col2_);
}
Matrix2x2& Matrix2x2::operator+=(const Matrix2x2& matrix) {
  col1_ += matrix.col1_;
  col2_ += matrix.col2_;
  return *this;
}
// matrix multiplication
Matrix2x2 Matrix2x2::operator*(const Matrix2x2& matrix) const {
  Vector2 row1 = GetRow1();
  Vector2 row2 = GetRow2();
  return Matrix2x2(Vector2(row1.Dot(matrix.col1_), row2.Dot(matrix.col1_)),
                   Vector2(row1.Dot(matrix.col2_), row2.Dot(matrix.col2_)));
}

Matrix2x2& Matrix2x2::operator*=(const Matrix2x2& matrix) {
  Vector2 row1 = GetRow1();
  Vector2 row2 = GetRow2();
  col1_ = Vector2(row1.Dot(matrix.col1_), row2.Dot(matrix.col1_));
  col2_ = Vector2(row1.Dot(matrix.col2_), row2.Dot(matrix.col2_));
  return *this;
}

Vector2 Matrix2x2::operator*(const Vector2& vector) const {
  return Vector2(GetRow1().Dot(vector), GetRow2().Dot(vector));
}

Matrix2x2 Matrix2x2::Transpose() const {
  return Matrix2x2(GetRow1(), GetRow2());
}

std::vector<std::string> Matrix2x2::ToString() const {
  Vector2 row1 = GetRow1();
  Vector2 row2 = GetRow2();
  std::vector<std::string> result;
  char row[64];
  std::snprintf(row, sizeof(row), "| %.3f , %.3f |", row1.x(), row1.y());
  result.emplace_back(row);
  std::snprintf(row, sizeof(row), "| %.3f , %.3f|", row2.x(), row2.y());
  result.emplace_back(row);
  return result;
}
}  // namespace ho_renderer