#include "core/math/include/matrix4x4.h"

#include <string>
#include <vector>

#include "core/math/include/vector4.h"

namespace ho_renderer {

const Matrix4x4 Matrix4x4::kIdentityMatrix = Matrix4x4(
    Vector4::kUnitX, Vector4::kUnitY, Vector4::kUnitZ, Vector4::kUnitW);

Matrix4x4::Matrix4x4() = default;
Matrix4x4::Matrix4x4(const Vector4& col1, const Vector4& col2,
                     const Vector4& col3, const Vector4& col4)
    : col1_(col1), col2_(col2), col3_(col3), col4_(col4) {}
Matrix4x4::Matrix4x4(const Matrix4x4& matrix) = default;
Matrix4x4& Matrix4x4::operator=(const Matrix4x4& matrix) = default;
Matrix4x4::~Matrix4x4() = default;

// getter and setter
Vector4 Matrix4x4::col1() const { return col1_; }
Vector4 Matrix4x4::col2() const { return col2_; }
Vector4 Matrix4x4::col3() const { return col3_; }
Vector4 Matrix4x4::col4() const { return col4_; }
Matrix4x4& Matrix4x4::set_col1(const Vector4& vector) {
  col1_ = vector;
  return *this;
}
Matrix4x4& Matrix4x4::set_col2(const Vector4& vector) {
  col2_ = vector;
  return *this;
}
Matrix4x4& Matrix4x4::set_col3(const Vector4& vector) {
  col3_ = vector;
  return *this;
}
Matrix4x4& Matrix4x4::set_col4(const Vector4& vector) {
  col4_ = vector;
  return *this;
}
// row getter
Vector4 Matrix4x4::GetRow1() const {
  return Vector4(col1_.x(), col2_.x(), col3_.x(), col4_.x());
}
Vector4 Matrix4x4::GetRow2() const {
  return Vector4(col1_.y(), col2_.y(), col3_.y(), col4_.y());
}
Vector4 Matrix4x4::GetRow3() const {
  return Vector4(col1_.z(), col2_.z(), col3_.z(), col4_.z());
}
Vector4 Matrix4x4::GetRow4() const {
  return Vector4(col1_.w(), col2_.w(), col3_.w(), col4_.w());
}
// addition
Matrix4x4 Matrix4x4::operator+(const Matrix4x4& matrix) const {
  return Matrix4x4(col1_ + matrix.col1_, col2_ + matrix.col2_,
                   col3_ + matrix.col3_, col4_ + matrix.col4_);
}
Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& matrix) {
  col1_ += matrix.col1_;
  col2_ += matrix.col2_;
  col3_ += matrix.col3_;
  col4_ += matrix.col4_;
  return *this;
}
// matrix multiplication
Matrix4x4 Matrix4x4::operator*(const Matrix4x4& matrix) const {
  Vector4 row1 = GetRow1();
  Vector4 row2 = GetRow2();
  Vector4 row3 = GetRow3();
  Vector4 row4 = GetRow4();
  return Matrix4x4(Vector4(row1.Dot(matrix.col1_), row2.Dot(matrix.col1_),
                           row3.Dot(matrix.col1_), row4.Dot(matrix.col1_)),
                   Vector4(row1.Dot(matrix.col2_), row2.Dot(matrix.col2_),
                           row3.Dot(matrix.col2_), row4.Dot(matrix.col2_)),
                   Vector4(row1.Dot(matrix.col3_), row2.Dot(matrix.col3_),
                           row3.Dot(matrix.col3_), row4.Dot(matrix.col3_)),
                   Vector4(row1.Dot(matrix.col4_), row2.Dot(matrix.col4_),
                           row3.Dot(matrix.col4_), row4.Dot(matrix.col4_)));
}
Matrix4x4& ho_renderer::Matrix4x4::operator*=(const Matrix4x4& matrix) {
  Vector4 row1 = GetRow1();
  Vector4 row2 = GetRow2();
  Vector4 row3 = GetRow3();
  Vector4 row4 = GetRow4();
  col1_ = Vector4(row1.Dot(matrix.col1_), row2.Dot(matrix.col1_),
                  row3.Dot(matrix.col1_), row4.Dot(matrix.col1_));
  col2_ = Vector4(row1.Dot(matrix.col2_), row2.Dot(matrix.col2_),
                  row3.Dot(matrix.col2_), row4.Dot(matrix.col2_));
  col3_ = Vector4(row1.Dot(matrix.col3_), row2.Dot(matrix.col3_),
                  row3.Dot(matrix.col3_), row4.Dot(matrix.col3_));
  col4_ = Vector4(row1.Dot(matrix.col4_), row2.Dot(matrix.col4_),
                  row3.Dot(matrix.col4_), row4.Dot(matrix.col4_));
  return *this;
}
Vector4 ho_renderer::Matrix4x4::operator*(const Vector4& vector) const {
  return Vector4(GetRow1().Dot(vector), GetRow2().Dot(vector),
                 GetRow3().Dot(vector), GetRow4().Dot(vector));
}
// transposition
ho_renderer::Matrix4x4 ho_renderer::Matrix4x4::Transpose() const {
  return Matrix4x4(GetRow1(), GetRow2(), GetRow3(), GetRow4());
}

std::vector<std::string> Matrix4x4::ToString() const {
  Vector4 row1 = GetRow1();
  Vector4 row2 = GetRow2();
  Vector4 row3 = GetRow3();
  Vector4 row4 = GetRow4();
  std::vector<std::string> result;
  char row[64];
  std::snprintf(row, sizeof(row), "| %.3f , %.3f , %.3f, %.3f |", row1.x(),
                row1.y(), row1.z(), row1.w());
  result.emplace_back(row);
  std::snprintf(row, sizeof(row), "| %.3f , %.3f , %.3f, %.3f |", row2.x(),
                row2.y(), row2.z(), row2.w());
  result.emplace_back(row);
  std::snprintf(row, sizeof(row), "| %.3f , %.3f , %.3f, %.3f |", row3.x(),
                row3.y(), row3.z(), row3.w());
  result.emplace_back(row);
  std::snprintf(row, sizeof(row), "| %.3f , %.3f , %.3f, %.3f |", row4.x(),
                row4.y(), row4.z(), row4.w());
  result.emplace_back(row);
  return result;
}

}  // namespace ho_renderer