#ifndef _HORENDERER_MATH_MATRIX3X3_H_
#define _HORENDERER_MATH_MATRIX3X3_H_

#include "math/include/vector3.h"

namespace ho_renderer {
class Matrix3x3 {
 public:
  static Matrix3x3 kIdentityMatrix;
  // constructor
  Matrix3x3();
  Matrix3x3(const Vector3& col1, const Vector3& col2, const Vector3& col3);
  Matrix3x3(const Matrix3x3& matrix);
  Matrix3x3& operator=(const Matrix3x3& matrix);
  ~Matrix3x3();
  // getter and setter
  Vector3 col1() const;
  Vector3 col2() const;
  Vector3 col3() const;
  Matrix3x3& set_col1(const Vector3& vector);
  Matrix3x3& set_col2(const Vector3& vector);
  Matrix3x3& set_col3(const Vector3& vector);
  // row getter
  Vector3 GetRow1() const;
  Vector3 GetRow2() const;
  Vector3 GetRow3() const;
  // addition
  Matrix3x3 operator+(const Matrix3x3& matrix) const;
  Matrix3x3& operator+=(const Matrix3x3& matrix);
  // matrix multiplication
  Matrix3x3 operator*(const Matrix3x3& matrix) const;
  Matrix3x3& operator*=(const Matrix3x3& matrix);
  Vector3 operator*(const Vector3& vector) const;
  // transposition
  Matrix3x3 Transpose() const;

 private:
  Vector3 col1_;
  Vector3 col2_;
  Vector3 col3_;
};

// Scalar multiplication
inline Matrix3x3 operator*(const float scalar, const Matrix3x3 matrix) {
  return Matrix3x3(scalar * matrix.col1(), scalar * matrix.col2(),
                   scalar * matrix.col3());
}
}  // namespace ho_renderer
#endif  // _HORENDERER_MATH_MATRIX3X3_H_