#ifndef _HORENDERER_VECTOR3_H_
#define _HORENDERER_VECTOR3_H_

#include <string>

#include "core/math/include/vector2.h"

namespace ho_renderer {

class Vector4;
class Quaternion;

class alignas(16) Vector3 {
 public:
  static const Vector3 kUnitX;
  static const Vector3 kUnitY;
  static const Vector3 kUnitZ;
  static const Vector3 kZero;
  // constructor
  Vector3();
  Vector3(float x, float y, float z);
  Vector3(const Vector3 &);
  // make vector2 to vector4
  explicit Vector3(const Vector2 &vector);
  explicit Vector3(const Quaternion &quaternion);
  Vector3 &operator=(const Vector3 &);
  ~Vector3();
  // getter and setter
  float x() const;
  float y() const;
  float z() const;
  Vector3 &set_x(float x);
  Vector3 &set_y(float y);
  Vector3 &set_z(float z);
  // vector addition
  Vector3 operator+(const Vector3 &vector) const;
  Vector3 &operator+=(const Vector3 &vector);
  // vector subtraction
  Vector3 operator-(const Vector3 &vector) const;
  Vector3 &operator-=(const Vector3 &vector);
  // scalar multiplication
  Vector3 operator*(float scalar) const;
  Vector3 &operator*=(float scalar);
  // scalar multiplication with -1
  Vector3 operator-() const;
  // equality test
  bool operator==(const Vector3 &vector) const;
  bool operator!=(const Vector3 &vector) const;
  // dot product
  float Dot(const Vector3 &vector) const;
  // cross product
  Vector3 Cross(const Vector3 &vector) const;
  // calculating magnitude
  float GetMagnitude() const;
  float GetSqrdMagnitude() const;
  // normalization
  void Normalize();
  Vector3 GetNormalized() const;
  // transformation homogeneous coord to cartesian coord
  Vector2 ToCartesianCoordinate() const;
  // transformation cartesian coord to homogeneous coord
  Vector4 ToHomogeneousCoordinate() const;
  // transformation to Vector2 by eliminating last component
  Vector2 ToVector2() const;

  std::string ToString() const;

 private:
  float x_;
  float y_;
  float z_;
  float pad_ = 0.f;
};

// scalar multiplication
inline Vector3 operator*(float scalar, const Vector3 &vector) {
  return vector * scalar;
}
inline Vector3 operator/(const Vector3 &vector, float scalar) {
  float inv_scalar = 1.f / scalar;
  return inv_scalar * vector;
}
}  // namespace ho_renderer

#endif  // _HORENDERER_VECTOR3_H_