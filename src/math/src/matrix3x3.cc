#include "math/include/matrix3x3.h"

#include "app/include/debug.h"
#include "math/include/matrix4x4.h"
#include "math/include/vector3.h"
#include "math/include/vector4.h"

namespace ho_renderer {
Matrix3x3 Matrix3x3::kIdentityMatrix =
    Matrix3x3(ho_renderer::Vector3::kUnitX, ho_renderer::Vector3::kUnitY,
              ho_renderer::Vector3::kUnitZ);
// constructor
Matrix3x3::Matrix3x3() = default;
Matrix3x3::Matrix3x3(const Vector3& col1, const Vector3& col2,
                     const Vector3& col3)
    : col1_(col1), col2_(col2), col3_(col3) {}
Matrix3x3::Matrix3x3(const Matrix3x3& matrix) = default;
Matrix3x3& Matrix3x3::operator=(const Matrix3x3& matrix) = default;
Matrix3x3::~Matrix3x3() = default;
// getter and setter
Vector3 Matrix3x3::col1() const { return col1_; }
Vector3 Matrix3x3::col2() const { return col2_; }
Vector3 Matrix3x3::col3() const { return col3_; }
Matrix3x3& Matrix3x3::set_col1(const Vector3& vector) {
  col1_ = vector;
  return *this;
}
Matrix3x3& Matrix3x3::set_col2(const Vector3& vector) {
  col2_ = vector;
  return *this;
}
Matrix3x3& Matrix3x3::set_col3(const Vector3& vector) {
  col3_ = vector;
  return *this;
}
// row getter
Vector3 Matrix3x3::GetRow1() const {
  return Vector3(col1_.x(), col2_.x(), col3_.x());
}
Vector3 Matrix3x3::GetRow2() const {
  return Vector3(col1_.y(), col2_.y(), col3_.y());
}
Vector3 Matrix3x3::GetRow3() const {
  return Vector3(col1_.z(), col2_.z(), col3_.z());
}
// addition
Matrix3x3 ho_renderer::Matrix3x3::operator+(const Matrix3x3& matrix) const {
  return Matrix3x3(col1_ + matrix.col1_, col2_ + matrix.col2_,
                   col3_ + matrix.col3_);
}
Matrix3x3& ho_renderer::Matrix3x3::operator+=(const Matrix3x3& matrix) {
  col1_ += matrix.col1_;
  col2_ += matrix.col2_;
  col3_ += matrix.col3_;
  return *this;
}
// matrix multiplication
Matrix3x3 ho_renderer::Matrix3x3::operator*(const Matrix3x3& matrix) const {
  return Matrix3x3(
      Vector3(GetRow1().Dot(matrix.col1_), GetRow2().Dot(matrix.col1_),
              GetRow3().Dot(matrix.col1_)),
      Vector3(GetRow1().Dot(matrix.col2_), GetRow2().Dot(matrix.col2_),
              GetRow3().Dot(matrix.col2_)),
      Vector3(GetRow1().Dot(matrix.col3_), GetRow2().Dot(matrix.col3_),
              GetRow3().Dot(matrix.col3_)));
}
Matrix3x3& Matrix3x3::operator*=(const Matrix3x3& matrix) {
  col1_ = Vector3(GetRow1().Dot(matrix.col1_), GetRow2().Dot(matrix.col1_),
                  GetRow3().Dot(matrix.col1_));
  col2_ = Vector3(GetRow1().Dot(matrix.col2_), GetRow2().Dot(matrix.col2_),
                  GetRow3().Dot(matrix.col2_));
  col3_ = Vector3(GetRow1().Dot(matrix.col3_), GetRow2().Dot(matrix.col3_),
                  GetRow3().Dot(matrix.col3_));
  return *this;
}
Vector3 Matrix3x3::operator*(const Vector3& vector) const {
  return Vector3(GetRow1().Dot(vector), GetRow2().Dot(vector),
                 GetRow3().Dot(vector));
}
Matrix3x3 Matrix3x3::Transpose() const {
  return Matrix3x3(GetRow1(), GetRow2(), GetRow3());
}
}  // namespace ho_renderer
