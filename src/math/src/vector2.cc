#include "math/include/vector2.h"

#include <cassert>
#include <string>

#include "app/include/debug.h"
#include "math/include/math_utils.h"
#include "math/include/vector3.h"

namespace ho_renderer {

const Vector2 Vector2::kUnitX = Vector2(1.f, 0.f);
const Vector2 Vector2::kUnitY = Vector2(0.f, 1.f);
const Vector2 Vector2::kZero = Vector2(0.f, 0.f);

Vector2::Vector2() : x_(0.f), y_(0.f) {}
Vector2::Vector2(float x, float y) : x_(x), y_(y) {}
Vector2::Vector2(const Vector2&) = default;
Vector2& Vector2::operator=(const Vector2&) = default;
Vector2::~Vector2() = default;

// getter and setter
float Vector2::x() const { return x_; }
float Vector2::y() const { return y_; }
Vector2& Vector2::set_x(float x) {
  x_ = x;
  return *this;
}
Vector2& Vector2::set_y(float y) {
  y_ = y;
  return *this;
}

// addition
Vector2 Vector2::operator+(const Vector2& vector) const {
  return Vector2(x_ + vector.x(), y_ + vector.y());
}
Vector2& Vector2::operator+=(const Vector2& vector) {
  x_ += vector.x();
  y_ += vector.y();
  return *this;
}

// subtraction
Vector2 Vector2::operator-(const Vector2& vector) const {
  return Vector2(x_ - vector.x(), y_ - vector.y());
}
Vector2& Vector2::operator-=(const Vector2& vector) {
  x_ -= vector.x();
  y_ -= vector.y();
  return *this;
}

// scalar multiplication with -1
Vector2 Vector2::operator-() const { return -1.f * *this; }

// comparison
bool Vector2::operator==(const Vector2& vector) const {
  return MathUtils::IsEqual(x_, vector.x()) &&
         MathUtils::IsEqual(y_, vector.y());
}
bool Vector2::operator!=(const Vector2& vector) const {
  return !(*this == vector);
}

// dot product
float Vector2::Dot(const Vector2& vector) const {
  return x_ * vector.x() + y_ * vector.y();
}

// magnitude
float Vector2::GetMagnitude() const {
  return MathUtils::Sqrtf(GetSqrdMagnitude());
}
float Vector2::GetSqrdMagnitude() const { return this->Dot(*this); }

// normalization
void Vector2::Normalize() {
  float inv_mag = MathUtils::InvSqrtf(GetSqrdMagnitude());
  if (MathUtils::IsFloatNaN(inv_mag)) {
    return;
  }
  *this = inv_mag * *this;
}
Vector2 Vector2::GetNormalized() const {
  float inv_mag = MathUtils::InvSqrtf(GetSqrdMagnitude());
  if (MathUtils::IsFloatNaN(inv_mag)) {
    return Vector2::kZero;
  }
  return inv_mag * *this;
}

Vector3 Vector2::ToHomogeneousCoordinate() const {
  return Vector3(x_, y_, 1.f);
}

std::string Vector2::ToString() const {
  char buf[100];
  snprintf(buf, sizeof(buf), "(%.3f, %.3f)", x_, y_);
  return buf;
}
}  // namespace ho_renderer