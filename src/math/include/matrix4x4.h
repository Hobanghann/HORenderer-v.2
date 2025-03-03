#ifndef _HORENDERER_MATH_MATRIX4X4_H_
#define _HORENDERER_MATH_MATRIX4X4_H_

#include <string>
#include <vector>

#include "math/include/vector4.h"

namespace ho_renderer {
class Matrix4x4 {
 public:
  static const Matrix4x4 kIdentityMatrix;

  // constructor
  Matrix4x4();
  Matrix4x4(const Vector4& col1, const Vector4& col2, const Vector4& col3,
            const Vector4& col4);
  Matrix4x4(const Matrix4x4& matrix);
  Matrix4x4& operator=(const Matrix4x4& matrix);
  ~Matrix4x4();
  // getter and setter
  Vector4 col1() const;
  Vector4 col2() const;
  Vector4 col3() const;
  Vector4 col4() const;
  Matrix4x4& set_col1(const Vector4& vector);
  Matrix4x4& set_col2(const Vector4& vector);
  Matrix4x4& set_col3(const Vector4& vector);
  Matrix4x4& set_col4(const Vector4& vector);
  // row getter
  Vector4 GetRow1() const;
  Vector4 GetRow2() const;
  Vector4 GetRow3() const;
  Vector4 GetRow4() const;
  // addition
  Matrix4x4 operator+(const Matrix4x4& matrix) const;
  Matrix4x4& operator+=(const Matrix4x4& matrix);
  // matrix multiplication
  Matrix4x4 operator*(const Matrix4x4& matrix) const;
  Matrix4x4& operator*=(const Matrix4x4& matrix);
  Vector4 operator*(const Vector4& InVector) const;
  // transpose
  Matrix4x4 Transpose() const;

  std::vector<std::string> ToStrings() const;

 private:
  Vector4 col1_;
  Vector4 col2_;
  Vector4 col3_;
  Vector4 col4_;
};
// Scalar multiplication
inline Matrix4x4 operator*(const float& scalar, const Matrix4x4& matrix) {
  return Matrix4x4(scalar * matrix.col1(), scalar * matrix.col2(),
                   scalar * matrix.col3(), scalar * matrix.col4());
}
}  // namespace ho_renderer

#endif  // _HORENDERER_MATH_MATRIX4X4_H_