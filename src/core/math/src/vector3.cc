#include "core/math/include/vector3.h"

#include <immintrin.h>

#include <string>

#include "core/math/include/math_utils.h"
#include "core/math/include/quaternion.h"
#include "core/math/include/vector2.h"
#include "core/math/include/vector4.h"

namespace ho_renderer {
const Vector3 Vector3::kUnitX = Vector3(1.f, 0.f, 0.f);
const Vector3 Vector3::kUnitY = Vector3(0.f, 1.f, 0.f);
const Vector3 Vector3::kUnitZ = Vector3(0.f, 0.f, 1.f);
const Vector3 Vector3::kZero = Vector3(0.f, 0.f, 0.f);

// constructor
Vector3::Vector3() : x_(0.f), y_(0.f), z_(0.f), pad_(0.f) {}
Vector3::Vector3(float x, float y, float z) : x_(x), y_(y), z_(z), pad_(0.f) {}
Vector3::Vector3(const Vector3 &) = default;
// make vector2 to vector4
Vector3::Vector3(const Vector2 &vector)
    : x_(vector.x()), y_(vector.y()), z_(0.f), pad_(0.f) {};
Vector3::Vector3(const Quaternion &quaternion)
    : x_(quaternion.vector_part().x()),
      y_(quaternion.vector_part().y()),
      z_(quaternion.vector_part().z()),
      pad_(0.f) {}
Vector3 &Vector3::operator=(const Vector3 &) = default;
Vector3::~Vector3() = default;

// getter and setter
float Vector3::x() const { return x_; }
float Vector3::y() const { return y_; }
float Vector3::z() const { return z_; }
Vector3 &Vector3::set_x(float x) {
  x_ = x;
  return *this;
}
Vector3 &Vector3::set_y(float y) {
  y_ = y;
  return *this;
}
Vector3 &Vector3::set_z(float z) {
  z_ = z;
  return *this;
}

// addition
Vector3 Vector3::operator+(const Vector3 &vector) const {
  __m128 a = _mm_load_ps(&x_);
  __m128 b = _mm_load_ps(&vector.x_);
  __m128 c = _mm_add_ps(a, b);
  float alignas(16) result[4];
  _mm_store_ps(result, c);
  return Vector3(result[0], result[1], result[2]);
}
Vector3 &Vector3::operator+=(const Vector3 &vector) {
  __m128 a = _mm_load_ps(&x_);
  __m128 b = _mm_load_ps(&vector.x_);
  __m128 c = _mm_add_ps(a, b);
  _mm_store_ps(&x_, c);
  return *this;
}

// subtraction
Vector3 Vector3::operator-(const Vector3 &vector) const {
  __m128 a = _mm_load_ps(&x_);
  __m128 b = _mm_load_ps(&vector.x_);
  __m128 c = _mm_sub_ps(a, b);
  float alignas(16) result[4];
  _mm_store_ps(result, c);
  return Vector3(result[0], result[1], result[2]);
}
Vector3 &Vector3::operator-=(const Vector3 &vector) {
  __m128 a = _mm_load_ps(&x_);
  __m128 b = _mm_load_ps(&vector.x_);
  __m128 c = _mm_sub_ps(a, b);
  _mm_store_ps(&x_, c);
  return *this;
}

// scalar multiplication
Vector3 Vector3::operator*(float scalar) const {
  __m128 a = _mm_load_ps(&x_);
  __m128 b = _mm_set1_ps(scalar);
  __m128 c = _mm_mul_ps(a, b);
  float alignas(16) result[4];
  _mm_store_ps(result, c);
  return Vector3(result[0], result[1], result[2]);
}
Vector3 &Vector3::operator*=(float scalar) {
  __m128 a = _mm_load_ps(&x_);
  __m128 b = _mm_set1_ps(scalar);
  __m128 c = _mm_mul_ps(a, b);
  _mm_store_ps(&x_, c);
  return *this;
}

// scalar multiplication with -1
Vector3 Vector3::operator-() const { return Vector3(-x_, -y_, -z_); }

// equality test
bool Vector3::operator==(const Vector3 &vector) const {
  return MathUtils::IsEqual(x_, vector.x()) &&
         MathUtils::IsEqual(y_, vector.y()) &&
         MathUtils::IsEqual(z_, vector.z());
}
bool Vector3::operator!=(const Vector3 &vector) const {
  return !(*this == vector);
}

// dot product
float Vector3::Dot(const Vector3 &vector) const {
  __m128 a = _mm_load_ps(&x_);
  __m128 b = _mm_load_ps(&vector.x_);
  __m128 result = _mm_dp_ps(a, b, 0b01110001);
  return _mm_cvtss_f32(result);
}

// cross product
Vector3 Vector3::Cross(const Vector3 &vector) const {
  __m128 a = _mm_load_ps(&x_);
  __m128 b = _mm_load_ps(&vector.x_);

  // Compute cross product using shuffles
  __m128 a_yzx = _mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 0, 2, 1));
  __m128 b_yzx = _mm_shuffle_ps(b, b, _MM_SHUFFLE(3, 0, 2, 1));
  __m128 a_zxy = _mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 1, 0, 2));
  __m128 b_zxy = _mm_shuffle_ps(b, b, _MM_SHUFFLE(3, 1, 0, 2));

  __m128 cross = _mm_sub_ps(_mm_mul_ps(a_yzx, b_zxy), _mm_mul_ps(a_zxy, b_yzx));

  Vector3 result;
  _mm_store_ps(&result.x_, cross);
  result.pad_ = 0.0f;  // Ensure padding is zero
  return result;
}

// magnitude
float Vector3::GetMagnitude() const { return sqrtf(GetSqrdMagnitude()); }
float Vector3::GetSqrdMagnitude() const { return this->Dot(*this); }

// normalization
void Vector3::Normalize() {
  float inv_mag = MathUtils::FastInvSqrtf(GetSqrdMagnitude());
  if (MathUtils::IsFloatNaN(inv_mag)) {
    return;
  }
  *this = inv_mag * *this;
}
Vector3 Vector3::GetNormalized() const {
  float inv_mag = MathUtils::FastInvSqrtf(GetSqrdMagnitude());
  if (MathUtils::IsFloatNaN(inv_mag)) {
    return Vector3::kZero;
  }
  return inv_mag * *this;
}

Vector2 Vector3::ToCartesianCoordinate() const {
  float z = z_;
  if (MathUtils::IsEqual(z, 0.f)) {
    z = MathUtils::kFloatMin;
  }
  float inv_z = 1.f / z;
  return Vector2(x_ * inv_z, y_ * inv_z);
}

Vector4 Vector3::ToHomogeneousCoordinate() const {
  return Vector4(x_, y_, z_, 1.f);
}

Vector2 Vector3::ToVector2() const { return Vector2(x_, y_); }

std::string Vector3::ToString() const {
  char buf[100];
  snprintf(buf, sizeof(buf), "(%.3f, %.3f, %.3f)", x_, y_, z_);
  return buf;
}
}  // namespace ho_renderer