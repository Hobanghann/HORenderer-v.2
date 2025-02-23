#define _USE_MATH_DEFINES
#include "math/include/math_utils.h"

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
const float MathUtils::kEPSILON = std::numeric_limits<float>::epsilon();
const float MathUtils::kFLOAT_NAN = std::numeric_limits<float>::quiet_NaN();
const float MathUtils::kDEGREE1_IN_RADIAN = kPI / 180.f;

bool MathUtils::IsEqual(const float f1, const float f2) {
  return fabs(f1 - f2) < kEPSILON;
}
bool MathUtils::IsNotEqual(const float f1, const float f2) {
  return !(IsEqual(f1, f2));
}

float MathUtils::Abs(const float f) { return std::abs(f); }
int MathUtils::Abs(const int i) { return std::abs(i); }
bool MathUtils::IsFloatNaN(const float f) { return isnan(f); }
float MathUtils::Pow(float base, float exp) { return powf(base, exp); }
float MathUtils::Sqrtf(const float f) { return sqrtf(f); }
float MathUtils::Sinf(const float radian) { return sinf(radian); }
float MathUtils::Cosf(const float radian) { return cosf(radian); }
float MathUtils::Tanf(const float radian) { return tanf(radian); }

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
  if (value < min) {
    return min;
  }
  if (value > max) {
    return max;
  }
  return value;
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
