#ifndef _HORENDERER_MATH_MATHUTILS_H_
#define _HORENDERER_MATH_MATHUTILS_H_

namespace ho_renderer {
class Vector2;
class Vector3;
class Vector4;
class MathUtils {
 public:
  static const float kFLOAT_MAX;
  static const float kFLOAT_MIN;
  static const float kPI;
  static const float kEPSILON;
  static const float MathUtils::kFLOAT_NAN;
  static const float kDEGREE1_IN_RADIAN;
  MathUtils() = delete;
  MathUtils(const MathUtils&) = delete;
  MathUtils& operator=(const MathUtils&) = delete;
  ~MathUtils() = delete;
  static bool IsEqual(const float f1, const float f2);
  static bool IsNotEqual(const float f1, const float f2);
  static float Abs(const float f);
  static int Abs(const int i);
  static float Pow(float base, float exp);
  static float Sqrtf(const float f);
  static bool IsFloatNaN(const float f);
  static float Sinf(const float radian);
  static float Cosf(const float radian);
  static float Tanf(const float radian);
  static float Maxf(const float f1, const float f2);
  static float Maxf(const float f1, const float f2, const float f3);
  static float Minf(const float f1, const float f2);
  static float Minf(const float f1, const float f2, const float f3);
  static float Clamp(const float min, const float max, const float value);
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

#endif  // _HORENDERER_MATH_MATHUTILS_H_