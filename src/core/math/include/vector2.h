#ifndef _HORENDERER_VECTOR2_H_
#define _HORENDERER_VECTOR2_H_

#include <string>

namespace ho_renderer {

class Vector3;

class Vector2 {
 public:
  static const Vector2 kUnitX;
  static const Vector2 kUnitY;
  static const Vector2 kZero;

  Vector2();
  Vector2(float x, float y);
  Vector2(const Vector2&);
  Vector2& operator=(const Vector2&);
  ~Vector2();
  // getter and setter
  float x() const;
  float y() const;
  Vector2& set_x(float x);
  Vector2& set_y(float y);
  // addition
  Vector2 operator+(const Vector2& vector) const;
  Vector2& operator+=(const Vector2& vector);
  // subtraction
  Vector2 operator-(const Vector2& vector) const;
  Vector2& operator-=(const Vector2& vector);
  // scalar multiplication
  Vector2 operator*(float scalar) const;
  Vector2& operator*=(float scalar);
  // scalar multiplication with -1
  Vector2 operator-() const;
  // comparison
  bool operator==(const Vector2& vector) const;
  bool operator!=(const Vector2& vector) const;
  // dot product
  float Dot(const Vector2& vector) const;
  // magnitude
  float GetMagnitude() const;
  float GetSqrdMagnitude() const;
  // normalization
  void Normalize();
  Vector2 GetNormalized() const;
  // transformation cartesian coord to homogeneous coord
  Vector3 ToHomogeneousCoordinate() const;

  std::string ToString() const;

 private:
  float x_;
  float y_;
};

inline Vector2 operator*(float scalar, const Vector2& vector) {
  return vector * scalar;
}
inline Vector2 operator/(const Vector2& vector, float scalar) {
  float inv_scalar = 1.f / scalar;
  return inv_scalar * vector;
}
}  // namespace ho_renderer

#endif  //_HORENDERER_VECTOR2_H_
