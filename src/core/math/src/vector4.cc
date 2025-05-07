#include "core/math/include/vector4.h"

#include <immintrin.h>

#include <string>

#include "core/math/include/math_utils.h"
#include "core/math/include/quaternion.h"
#include "core/math/include/vector3.h"

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
Vector4::Vector4(const Quaternion& quaternion)
    : x_(quaternion.scalar_part()),
      y_(quaternion.vector_part().x()),
      z_(quaternion.vector_part().y()),
      w_(quaternion.vector_part().z()) {}
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
  __m128 a = _mm_load_ps(&x_);
  __m128 b = _mm_load_ps(&vector.x_);
  __m128 c = _mm_add_ps(a, b);
  float alignas(16) result[4];
  _mm_store_ps(result, c);
  return Vector4(result[0], result[1], result[2], result[3]);
}
Vector4& Vector4::operator+=(const Vector4& vector) {
  __m128 a = _mm_load_ps(&x_);
  __m128 b = _mm_load_ps(&vector.x_);
  __m128 c = _mm_add_ps(a, b);
  _mm_store_ps(&x_, c);
  return *this;
}

// subtraction
Vector4 Vector4::operator-(const Vector4& vector) const {
  __m128 a = _mm_load_ps(&x_);
  __m128 b = _mm_load_ps(&vector.x_);
  __m128 c = _mm_sub_ps(a, b);
  float alignas(16) result[4];
  _mm_store_ps(result, c);
  return Vector4(result[0], result[1], result[2], result[3]);
}
Vector4& Vector4::operator-=(const Vector4& vector) {
  __m128 a = _mm_load_ps(&x_);
  __m128 b = _mm_load_ps(&vector.x_);
  __m128 c = _mm_sub_ps(a, b);
  _mm_store_ps(&x_, c);
  return *this;
}

// scalar multiplication
Vector4 Vector4::operator*(float scalar) const {
  __m128 a = _mm_load_ps(&x_);
  __m128 b = _mm_set1_ps(scalar);
  __m128 c = _mm_mul_ps(a, b);
  float alignas(16) result[4];
  _mm_store_ps(result, c);
  return Vector4(result[0], result[1], result[2], result[3]);
}
Vector4& Vector4::operator*=(float scalar) {
  __m128 a = _mm_load_ps(&x_);
  __m128 b = _mm_set1_ps(scalar);
  __m128 c = _mm_mul_ps(a, b);
  _mm_store_ps(&x_, c);
  return *this;
}

// scalar multiplication with -1
Vector4 Vector4::operator-() const { return Vector4(-x_, -y_, -z_, -w_); }

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

// dot product
float ho_renderer::Vector4::Dot(const Vector4& vector) const {
  __m128 a = _mm_load_ps(&x_);
  __m128 b = _mm_load_ps(&vector.x_);
  __m128 result = _mm_dp_ps(a, b, 0b11110001);
  return _mm_cvtss_f32(result);
}

// magnitude
float Vector4::GetMagnitude() const { return sqrtf(GetSqrdMagnitude()); }
float Vector4::GetSqrdMagnitude() const { return this->Dot(*this); }

// normalization
void Vector4::Normalize() {
  float inv_mag = MathUtils::FastInvSqrtf(GetSqrdMagnitude());
  if (MathUtils::IsFloatNaN(inv_mag)) {
    return;
  }
  *this = inv_mag * *this;
}
Vector4 Vector4::GetNormalized() const {
  float inv_mag = MathUtils::FastInvSqrtf(GetSqrdMagnitude());
  if (MathUtils::IsFloatNaN(inv_mag)) {
    return Vector4::kZero;
  }
  return inv_mag * *this;
}

Vector3 Vector4::ToCartesianCoordinate() const {
  float w = w_;
  if (MathUtils::IsEqual(w, 0.f)) {
    w = MathUtils::kFloatMin;
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
