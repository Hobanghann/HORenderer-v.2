#ifndef _HORENDERER_MATH_MATRIX2X2_H_
#define _HORENDERER_MATH_MATRIX2X2_H_

#include "math/include/vector2.h"

namespace ho_renderer {
class Matrix3x3;
class Matrix2x2 {
 public:
  static const Matrix2x2 kIdentityMatrix;
  // constructor
  Matrix2x2();
  Matrix2x2(const Vector2& col1, const Vector2& col2);
  Matrix2x2(const Matrix2x2&);
  Matrix2x2& operator=(const Matrix2x2&);
  ~Matrix2x2();
  // getter and setter
  Vector2 col1() const;
  Vector2 col2() const;
  Matrix2x2& set_col1(const Vector2& vector);
  Matrix2x2& set_col2(const Vector2& vector);
  // row getter
  Vector2 GetRow1() const;
  Vector2 GetRow2() const;
  // addition
  Matrix2x2 operator+(const Matrix2x2& matrix) const;
  Matrix2x2& operator+=(const Matrix2x2& matrix);
  // matrix multiplication
  Matrix2x2 operator*(const Matrix2x2& matrix) const;
  Matrix2x2& operator*=(const Matrix2x2& matrix);
  Vector2 operator*(const Vector2& InVector) const;
  // Transpose
  Matrix2x2 Transpose() const;

 private:
  Vector2 col1_;
  Vector2 col2_;
};

// scalar multiplication
inline Matrix2x2 operator*(const float scalar, const Matrix2x2& matrix) {
  return Matrix2x2(scalar * matrix.col1(), scalar * matrix.col2());
}
}  // namespace ho_renderer

#endif  // _HORENDERER_MATH_MATRIX2X2_H_