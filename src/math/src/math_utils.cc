#define _USE_MATH_DEFINES
#include "math/include/math_utils.h"

#include <xmmintrin.h>

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <limits>

#include "app/include/debug.h"
#include "math/include/vector2.h"
#include "math/include/vector3.h"
#include "math/include/vector4.h"

namespace ho_renderer {

const float MathUtils::kFLOAT_MAX = std::numeric_limits<float>::max();
const float MathUtils::kFLOAT_MIN = std::numeric_limits<float>::lowest();
const float MathUtils::kPI = M_PI;
const float MathUtils::kHALF_PI = M_PI * 0.5f;
const float MathUtils::kINV_PI = 1.f / M_PI;
const float MathUtils::kEPSILON = 1e-5f;
const float MathUtils::kFLOAT_NAN = std::numeric_limits<float>::quiet_NaN();
const float MathUtils::kDEGREE1_IN_RADIAN = kPI / 180.f;

bool MathUtils::IsEqual(const float f1, const float f2) {
  return fabs(f1 - f2) < kEPSILON;
}
bool MathUtils::IsNotEqual(const float f1, const float f2) {
  return !(IsEqual(f1, f2));
}
bool MathUtils::IsGreater(const float f1, const float f2) {
  return (f1 - f2) > kEPSILON;
}
bool MathUtils::IsGreaterEqual(const float f1, const float f2) {
  return (f1 - f2) >= -kEPSILON;
}
bool MathUtils::IsLess(const float f1, const float f2) {
  return (f2 - f1) > kEPSILON;
}
bool MathUtils::IsLessEqual(const float f1, const float f2) {
  return (f2 - f1) >= -kEPSILON;
}
float MathUtils::Abs(const float f) { return std::abs(f); }
int MathUtils::Abs(const int i) { return std::abs(i); }
bool MathUtils::IsFloatNaN(const float f) { return isnan(f); }
float MathUtils::Pow(float base, float exp) { return powf(base, exp); }
float MathUtils::Sqrtf(const float f) { return sqrtf(f); }
float MathUtils::InvSqrtf(const float f) {
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
    return kFLOAT_NAN;
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
float MathUtils::Sinf(const float radian) { return sinf(radian); }
float MathUtils::Cosf(const float radian) { return cosf(radian); }
float MathUtils::Tanf(const float radian) { return tanf(radian); }
float MathUtils::Asinf(const float radian) { return asinf(radian); }
float MathUtils::Acosf(const float radian) { return acosf(radian); }
float MathUtils::Atanf(const float radian) { return atanf(radian); }
void MathUtils::SinCosf(float& out_sin, float& out_cos, const float radian) {
  // Copied from UE4 Source Code
  // Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
  float quotient = (kINV_PI * 0.5f) * radian;
  if (radian >= 0.0f) {
    quotient = (float)((int)(quotient + 0.5f));
  } else {
    quotient = (float)((int)(quotient - 0.5f));
  }
  float y = radian - (2.0f * kPI) * quotient;

  // Map y to [-pi/2,pi/2] with sin(y) = sin(Value).
  float sign = 0.f;
  if (y > kHALF_PI) {
    y = kPI - y;
    sign = -1.0f;
  } else if (y < -kHALF_PI) {
    y = -kPI - y;
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
float MathUtils::Maxf(const float f1, const float f2) {
  return std::max({f1, f2});
}
float MathUtils::Maxf(const float f1, const float f2, const float f3) {
  return std::max({f1, f2, f3});
}
float MathUtils::Minf(const float f1, const float f2) {
  return std::min({f1, f2});
}
float MathUtils::Minf(const float f1, const float f2, const float f3) {
  return std::min({f1, f2, f3});
}
float MathUtils::Clamp(const float min, const float max, const float value) {
  return value < min ? min : value > max ? max : value;
}
float MathUtils::DegreeToRadian(const float degree) {
  return degree * kDEGREE1_IN_RADIAN;
}

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
