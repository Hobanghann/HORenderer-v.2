#ifndef _HORENDERER_MATH_UTILS_H_
#define _HORENDERER_MATH_UTILS_H_

namespace ho_renderer {
class Vector2;
class Vector3;
class Vector4;
class MathUtils {
 public:
  static const float kFloatMax;
  static const float kFloatMin;
  static const float kPi;
  static const float kHalfPi;
  static const float kInvPi;
  static const float kEpsion;
  static const float kFloatNaN;
  static const float kDegree1InRad;
  MathUtils() = delete;
  MathUtils(const MathUtils&) = delete;
  MathUtils& operator=(const MathUtils&) = delete;
  ~MathUtils() = delete;
  static bool IsEqual(float f1, float f2);         // ==
  static bool IsNotEqual(float f1, float f2);      // !=
  static bool IsGreater(float f1, float f2);       // >
  static bool IsGreaterEqual(float f1, float f2);  // >=
  static bool IsLess(float f1, float f2);          // <
  static bool IsLessEqual(float f1, float f2);     // <=
  static float Abs(float f);
  static int Abs(int i);
  static float Powf(float base, float exp);
  static float FastPow(float base, int exp);
  static float Sqrtf(float f);
  static float FastInvSqrtf(float f);
  static bool IsFloatNaN(float f);
  static float Sinf(float radian);
  static float Cosf(float radian);
  static float Tanf(float radian);
  static float Asinf(float radian);
  static float Acosf(float radian);
  static float Atanf(float radian);
  static void SinCosf(float& out_sin, float& out_cos, float radian);
  static float Maxf(float f1, float f2);
  static float Maxf(float f1, float f2, float f3);
  static float Minf(float f1, float f2);
  static float Minf(float f1, float f2, float f3);
  static float Clamp(float min, float max, float value);
  static const Vector3& Clamp(const Vector3& min, const Vector3& max, const Vector3& value);
  static float DegreeToRadian(const float degree);
  static float GetSquaredDistance(const Vector2& vector1,
                                  const Vector2& vector2);
  static float GetSquaredDistance(const Vector3& vector1,
                                  const Vector3& vector2);
  static float GetSquaredDistance(const Vector4& vector1,
                                  const Vector4& vector2);
  static float GetDistance(const Vector2& vector1, const Vector2& vector2);
  static float GetDistance(const Vector3& vector1, const Vector3& vector2);
  static float GetDistance(const Vector4& vector1, const Vector4& vector2);
};
}  // namespace ho_renderer

#endif  // _HORENDERER_MATH_UTILS_H_