#include "math/include/vector4.h"

#include <cassert>
#include <string>

#include "app/include/debug.h"
#include "math/include/math_utils.h"

namespace ho_renderer {
const Vector4 Vector4::kUnitX = Vector4(1.f, 0.f, 0.f, 0.f);
const Vector4 Vector4::kUnitY = Vector4(0.f, 1.f, 0.f, 0.f);
const Vector4 Vector4::kUnitZ = Vector4(0.f, 0.f, 1.f, 0.f);
const Vector4 Vector4::kUnitW = Vector4(0.f, 0.f, 0.f, 1.f);
const Vector4 Vector4::kZero = Vector4(0.f, 0.f, 0.f, 0.f);

Vector4::Vector4() : x_(0.f), y_(0.f), z_(0.f), w_(0.f) {}
Vector4::Vector4(float x, float y, float z, float w)
    : x_(x), y_(y), z_(z), w_(w) {}
// make vector3 to vector4
Vector4::Vector4(const Vector3& vector)
    : x_(vector.x()), y_(vector.y()), z_(vector.z()), w_(0.f) {}
Vector4::Vector4(const Vector4& vector) = default;
Vector4& Vector4::operator=(const Vector4& vector) = default;
Vector4::~Vector4() = default;

// getter add setter
float Vector4::x() const { return x_; }
float Vector4::y() const { return y_; }
float Vector4::z() const { return z_; }
float Vector4::w() const { return w_; }
Vector4& Vector4::set_x(float x) {
  x_ = x;
  return *this;
}
Vector4& Vector4::set_y(float y) {
  y_ = y;
  return *this;
}
Vector4& Vector4::set_z(float z) {
  z_ = z;
  return *this;
}
Vector4& Vector4::set_w(float w) {
  w_ = w;
  return *this;
}

// addition
Vector4 Vector4::operator+(const Vector4& vector) const {
  return Vector4(x_ + vector.x_, y_ + vector.y_, z_ + vector.z_,
                 w_ + vector.w_);
}
Vector4& Vector4::operator+=(const Vector4& vector) {
  x_ += vector.x_;
  y_ += vector.y_;
  z_ += vector.z_;
  w_ += vector.w_;
  return *this;
}

// subtraction
Vector4 Vector4::operator-(const Vector4& vector) const {
  return Vector4(x_ - vector.x_, y_ - vector.y_, z_ - vector.z_,
                 w_ - vector.w_);
}
Vector4& Vector4::operator-=(const Vector4& vector) {
  x_ -= vector.x_;
  y_ -= vector.y_;
  z_ -= vector.z_;
  w_ -= vector.w_;
  return *this;
}

// equality test
bool Vector4::operator==(const Vector4& vector) const {
  return MathUtils::IsEqual(x_, vector.x()) &&
         MathUtils::IsEqual(y_, vector.y()) &&
         MathUtils::IsEqual(z_, vector.z()) &&
         MathUtils::IsEqual(w_, vector.w());
}
bool Vector4::operator!=(const Vector4& vector) const {
  return !(*this == vector);
}

// scalar multiplication with -1
Vector4 Vector4::operator-() const { return -1.f * *this; }

// dot product
float ho_renderer::Vector4::Dot(const Vector4& vector) const {
  return x_ * vector.x_ + y_ * vector.y_ + z_ * vector.z_ + w_ * vector.w_;
}

// magnitude
float Vector4::GetMagnitude() const { return sqrtf(GetSqrdMagnitude()); }
float Vector4::GetSqrdMagnitude() const { return this->Dot(*this); }

// normalization
void Vector4::Normalize() {
  float magnitude = this->GetMagnitude();
  if (MathUtils::IsEqual(magnitude, 0.f)) {
    *this = Vector4::kZero;
    return;
  }
  float inv_magnitude = 1.f / magnitude;
  *this = inv_magnitude * *this;
}
Vector4 Vector4::GetNormalized() const {
  float magnitude = this->GetMagnitude();
  if (MathUtils::IsEqual(magnitude, 0.f)) {
    return Vector4::kZero;
  }
  float inv_magnitude = 1.f / magnitude;
  return inv_magnitude * *this;
}

Vector3 Vector4::ToCartesianCoordinate() const {
  float w = w_;
  if (MathUtils::IsEqual(w, 0.f)) {
    w = MathUtils::kFLOAT_MIN;
  }
  float inv_w = 1.f / w;
  return Vector3(inv_w * x_, inv_w * y_, inv_w * z_);
}

Vector3 Vector4::ToVector3() const { return Vector3(x_, y_, z_); }

std::string Vector4::ToString() const {
  char buf[100];
  snprintf(buf, sizeof(buf), "(%.3f, %.3f, %.3f, %.3f)", x_, y_, z_, w_);
  return buf;
}
}  // namespace ho_renderer
