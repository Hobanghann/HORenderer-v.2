#define _USE_MATH_DEFINES
#include "core/math/include/math_utils.h"

#include <immintrin.h>
#include <xmmintrin.h>

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <limits>

#include "core/math/include/vector2.h"
#include "core/math/include/vector3.h"
#include "core/math/include/vector4.h"

namespace ho_renderer {

const float MathUtils::kFloatMax = std::numeric_limits<float>::max();
const float MathUtils::kFloatMin = std::numeric_limits<float>::lowest();
const float MathUtils::kPi = M_PI;
const float MathUtils::kHalfPi = M_PI * 0.5f;
const float MathUtils::kInvPi = 1.f / M_PI;
const float MathUtils::kEpsion = 1e-5f;
const float MathUtils::kFloatNaN = std::numeric_limits<float>::quiet_NaN();
const float MathUtils::kDegree1InRad = kPi / 180.f;

bool MathUtils::IsEqual(float f1, float f2) { return fabs(f1 - f2) < kEpsion; }
bool MathUtils::IsNotEqual(float f1, float f2) { return !(IsEqual(f1, f2)); }
bool MathUtils::IsGreater(float f1, float f2) { return (f1 - f2) > kEpsion; }
bool MathUtils::IsGreaterEqual(float f1, float f2) {
  return (f1 - f2) >= -kEpsion;
}
bool MathUtils::IsLess(float f1, float f2) { return (f2 - f1) > kEpsion; }
bool MathUtils::IsLessEqual(float f1, float f2) {
  return (f2 - f1) >= -kEpsion;
}
float MathUtils::Abs(float f) { return std::abs(f); }
int MathUtils::Abs(const int i) { return std::abs(i); }
bool MathUtils::IsFloatNaN(float f) { return isnan(f); }
float MathUtils::Powf(float base, float exp) { return powf(base, exp); }
float MathUtils::FastPow(float base, int exp) {
  float result = 1.0f;

  if (exp < 0) {
    base = 1.0f / base;
    exp = -exp;
  }

  while (exp > 0) {
    if (exp & 1) result *= base;
    base *= base;
    exp >>= 1;
  }
  return result;
}
float MathUtils::Sqrtf(float f) { return f * FastInvSqrtf(f); }
float MathUtils::FastInvSqrtf(float f) {
  // Performs two passes of Newton-Raphson iteration on the hardware estimate
  //    v^-0.5 = x
  // => x^2 = v^-1
  // => 1/(x^2) = v
  // => F(x) = x^-2 - v
  //    F'(x) = -2x^-3

  //    x1 = x0 - F(x0)/F'(x0)
  // => x1 = x0 + 0.5 * (x0^-2 - Vec) * x0^3
  // => x1 = x0 + 0.5 * (x0 - Vec * x0^3)
  // => x1 = x0 + x0 * (0.5 - 0.5 * Vec * x0^2)
  //
  // This final form has one more operation than the legacy factorization (X1 =
  // 0.5*X0*(3-(Y*X0)*X0) but retains better accuracy (namely InvSqrt(1) = 1
  // exactly).
  if (MathUtils::IsEqual(f, 0.f)) {
    return kFloatNaN;
  }

  const __m128 fOneHalf = _mm_set_ss(0.5f);
  __m128 Y0, X0, X1, X2, FOver2;
  float temp;

  Y0 = _mm_set_ss(f);
  X0 = _mm_rsqrt_ss(Y0);  // 1/sqrt estimate (12 bits)
  FOver2 = _mm_mul_ss(Y0, fOneHalf);

  // 1st Newton-Raphson iteration
  X1 = _mm_mul_ss(X0, X0);
  X1 = _mm_sub_ss(fOneHalf, _mm_mul_ss(FOver2, X1));
  X1 = _mm_add_ss(X0, _mm_mul_ss(X0, X1));

  // 2nd Newton-Raphson iteration
  X2 = _mm_mul_ss(X1, X1);
  X2 = _mm_sub_ss(fOneHalf, _mm_mul_ss(FOver2, X2));
  X2 = _mm_add_ss(X1, _mm_mul_ss(X1, X2));

  _mm_store_ss(&temp, X2);
  return temp;
}
float MathUtils::Sinf(float radian) { return sinf(radian); }
float MathUtils::Cosf(float radian) { return cosf(radian); }
float MathUtils::Tanf(float radian) { return tanf(radian); }
float MathUtils::Asinf(float radian) { return asinf(radian); }
float MathUtils::Acosf(float radian) { return acosf(radian); }
float MathUtils::Atanf(float radian) { return atanf(radian); }
void MathUtils::SinCosf(float& out_sin, float& out_cos, float radian) {
  // Copied from UE4 Source Code
  // Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
  float quotient = (kInvPi * 0.5f) * radian;
  if (radian >= 0.0f) {
    quotient = (float)((int)(quotient + 0.5f));
  } else {
    quotient = (float)((int)(quotient - 0.5f));
  }
  float y = radian - (2.0f * kPi) * quotient;

  // Map y to [-pi/2,pi/2] with sin(y) = sin(Value).
  float sign = 0.f;
  if (y > kHalfPi) {
    y = kPi - y;
    sign = -1.0f;
  } else if (y < -kHalfPi) {
    y = -kPi - y;
    sign = -1.0f;
  } else {
    sign = +1.0f;
  }

  float y2 = y * y;

  // 11-degree minimax approximation
  out_sin =
      (((((-2.3889859e-08f * y2 + 2.7525562e-06f) * y2 - 0.00019840874f) * y2 +
         0.0083333310f) *
            y2 -
        0.16666667f) *
           y2 +
       1.0f) *
      y;

  // 10-degree minimax approximation
  float p =
      ((((-2.6051615e-07f * y2 + 2.4760495e-05f) * y2 - 0.0013888378f) * y2 +
        0.041666638f) *
           y2 -
       0.5f) *
          y2 +
      1.0f;
  out_cos = sign * p;
}
float MathUtils::Maxf(float f1, float f2) { return std::max({f1, f2}); }
float MathUtils::Maxf(float f1, float f2, float f3) {
  return std::max({f1, f2, f3});
}
float MathUtils::Minf(float f1, float f2) { return std::min({f1, f2}); }
float MathUtils::Minf(float f1, float f2, float f3) {
  return std::min({f1, f2, f3});
}
float MathUtils::Clamp(float min, float max, float value) {
  return value < min ? min : value > max ? max : value;
}
const Vector3& MathUtils::Clamp(const Vector3& min, const Vector3& max,
                                const Vector3& value) {
  return Vector3(Clamp(min.x(), max.x(), value.x()),
                 Clamp(min.y(), max.y(), value.y()),
                 Clamp(min.z(), max.z(), value.z()));
}
float MathUtils::DegreeToRadian(float degree) { return degree * kDegree1InRad; }

float MathUtils::GetSquaredDistance(const Vector2& vector1,
                                    const Vector2& vector2) {
  return (vector1 - vector2).Dot(vector1 - vector2);
}
float MathUtils::GetSquaredDistance(const Vector3& vector1,
                                    const Vector3& vector2) {
  return (vector1 - vector2).Dot(vector1 - vector2);
}
float MathUtils::GetSquaredDistance(const Vector4& vector1,
                                    const Vector4& vector2) {
  return (vector1 - vector2).Dot(vector1 - vector2);
}

float MathUtils::GetDistance(const Vector2& vector1, const Vector2& vector2) {
  return MathUtils::Sqrtf(GetSquaredDistance(vector1, vector2));
}
float MathUtils::GetDistance(const Vector3& vector1, const Vector3& vector2) {
  return MathUtils::Sqrtf(GetSquaredDistance(vector1, vector2));
}
float MathUtils::GetDistance(const Vector4& vector1, const Vector4& vector2) {
  return MathUtils::Sqrtf(GetSquaredDistance(vector1, vector2));
}
}  // namespace ho_renderer
