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
  Vector3 row1 = GetRow1();
  Vector3 row2 = GetRow2();
  Vector3 row3 = GetRow3();
  return Matrix3x3(Vector3(row1.Dot(matrix.col1_), row2.Dot(matrix.col1_),
                           row3.Dot(matrix.col1_)),
                   Vector3(row1.Dot(matrix.col2_), row2.Dot(matrix.col2_),
                           row3.Dot(matrix.col2_)),
                   Vector3(row1.Dot(matrix.col3_), row2.Dot(matrix.col3_),
                           row3.Dot(matrix.col3_)));
}
Matrix3x3& Matrix3x3::operator*=(const Matrix3x3& matrix) {
  Vector3 row1 = GetRow1();
  Vector3 row2 = GetRow2();
  Vector3 row3 = GetRow3();
  col1_ = Vector3(row1.Dot(matrix.col1_), row2.Dot(matrix.col1_),
                  row3.Dot(matrix.col1_));
  col2_ = Vector3(row1.Dot(matrix.col2_), row2.Dot(matrix.col2_),
                  row3.Dot(matrix.col2_));
  col3_ = Vector3(row1.Dot(matrix.col3_), row2.Dot(matrix.col3_),
                  row3.Dot(matrix.col3_));
  return *this;
}
Vector3 Matrix3x3::operator*(const Vector3& vector) const {
  return Vector3(GetRow1().Dot(vector), GetRow2().Dot(vector),
                 GetRow3().Dot(vector));
}
Matrix3x3 Matrix3x3::Transpose() const {
  return Matrix3x3(GetRow1(), GetRow2(), GetRow3());
}

std::vector<std::string> Matrix3x3::ToStrings() const {
  Vector3 row1 = GetRow1();
  Vector3 row2 = GetRow2();
  Vector3 row3 = GetRow3();
  std::vector<std::string> result;
  char row[64];
  std::snprintf(row, sizeof(row), "| %.3f , %.3f , %.3f |", row1.x(), row1.y(),
                row1.z());
  result.emplace_back(row);
  std::snprintf(row, sizeof(row), "| %.3f , %.3f , %.3f |", row2.x(), row2.y(),
                row2.z());
  result.emplace_back(row);
  std::snprintf(row, sizeof(row), "| %.3f , %.3f , %.3f |", row3.x(), row3.y(),
                row3.z());
  result.emplace_back(row);
  return result;
}

}  // namespace ho_renderer
