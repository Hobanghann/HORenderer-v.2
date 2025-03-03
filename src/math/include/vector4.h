#ifndef _HORENDERER_MATH_VECTOR4_H_
#define _HORENDERER_MATH_VECTOR4_H_

#include <string>

#include "math/include/vector3.h"

namespace ho_renderer {
class Quaternion;

class Vector4 {
 public:
  static const Vector4 kUnitX;
  static const Vector4 kUnitY;
  static const Vector4 kUnitZ;
  static const Vector4 kUnitW;
  static const Vector4 kZero;

  Vector4();
  Vector4(float x, float y, float z, float w);
  Vector4(const Vector4&);
  Vector4& operator=(const Vector4&);
  explicit Vector4(const Vector3& vector);  // make vector3 to vector4
  explicit Vector4(const Quaternion& quaternion);
  ~Vector4();
  // getter add setter
  float x() const;
  float y() const;
  float z() const;
  float w() const;
  Vector4& set_x(float x);
  Vector4& set_y(float y);
  Vector4& set_z(float z);
  Vector4& set_w(float w);
  // addition
  Vector4 operator+(const Vector4& vector) const;
  Vector4& operator+=(const Vector4& vector);
  // sumation
  Vector4 operator-(const Vector4& vector) const;
  Vector4& operator-=(const Vector4& vector);
  // equality test
  bool operator==(const Vector4& vector) const;
  bool operator!=(const Vector4& vector) const;
  // scalar multiplication with -1
  Vector4 operator-() const;
  // dot product
  float Dot(const Vector4& vector) const;
  // magnitude
  float GetMagnitude() const;
  float GetSqrdMagnitude() const;
  // normaliz_ation
  void Normalize();
  Vector4 GetNormalized() const;
  // transformation homogeneous coordinate to cartesian coordinate
  Vector3 ToCartesianCoordinate() const;
  // transformation to Vector3 by eliminating last component
  Vector3 ToVector3() const;

  std::string ToString() const;

 private:
  float x_;
  float y_;
  float z_;
  float w_;
};
// scalar multiplication
inline Vector4 operator*(const float scalar, const Vector4& vector) {
  return Vector4(scalar * vector.x(), scalar * vector.y(), scalar * vector.z(),
                 scalar * vector.w());
}
inline Vector4 operator/(const Vector4& vector, const float scalar) {
  float inv_scalar = 1.f / scalar;
  return inv_scalar * vector;
}
}  // namespace ho_renderer

#endif  // _HORENDERER_MATH_VECTOR4_H_