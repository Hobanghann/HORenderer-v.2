#ifndef _HORENDERER_MATH_VECTOR3_H_
#define _HORENDERER_MATH_VECTOR3_H_

#include <string>

#include "math/include/vector2.h"

namespace ho_renderer {

class Vector4;

class Vector3 {
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
  // transformation homogeneous coordinate to cartesian coordinate
  Vector2 ToCartesianCoordinate() const;
  // transformation cartesian coordinate to homogeneous coordinate
  Vector4 ToHomogeneousCoordinate() const;
  // transformation to Vector2 by eliminating last component
  Vector2 ToVector2() const;

  std::string ToString() const;
 private:
  float x_;
  float y_;
  float z_;
};

// scalar multiplication
inline Vector3 operator*(const float scalar, const Vector3& vector) {
  return Vector3(scalar * vector.x(), scalar * vector.y(), scalar * vector.z());
}
}  // namespace ho_renderer

#endif  // _HORENDERER_MATH_VECOTR3_H_