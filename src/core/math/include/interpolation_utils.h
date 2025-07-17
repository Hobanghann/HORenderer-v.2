#ifndef _HORENDERER_INTERPOLATION_UTILS_H_
#define _HORENDERER_INTERPOLATION_UTILS_H_

#include "core/math/include/quaternion.h"
#include "core/math/include/vector2.h"
#include "core/math/include/vector3.h"
#include "core/math/include/vector4.h"

namespace ho_renderer {
class InterpolationUtils {
 public:
  InterpolationUtils() = delete;
  InterpolationUtils(const InterpolationUtils&) = delete;
  InterpolationUtils& operator=(const InterpolationUtils&) = delete;
  ~InterpolationUtils() = delete;
  static Vector2 GetBarycentric(const Vector2& target, const Vector2& v1,
                                const Vector2& v2);
  static Vector3 GetBarycentric(const Vector2& target, const Vector2& v1,
                                const Vector2& v2, const Vector2& v3);
  static Vector2 GetBarycentric(const Vector3& target, const Vector3& v1,
                                const Vector3& v2);
  static Vector3 GetBarycentric(const Vector3& target, const Vector3& v1,
                                const Vector3& v2, const Vector3& v3);
  static Vector2 GetBarycentric(const Vector4& target, const Vector4& v1,
                                const Vector4& v2);
  static Vector3 GetBarycentric(const Vector4& target, const Vector4& v1,
                                const Vector4& v2, const Vector4& v3);
  static float LerpInLine(float attribute1, float attribute2,
                          const Vector2& barycentric);
  static Vector2 LerpInLine(const Vector2& attribute1,
                            const Vector2& attribute2,
                            const Vector2& barycentric);
  static Vector3 LerpInLine(const Vector3& attribute1,
                            const Vector3& attribute2,
                            const Vector2& barycentric);
  static Vector4 LerpInLine(const Vector4& attribute1,
                            const Vector4& attribute2,
                            const Vector2& barycentric);
  static float LerpInTriangle(float attribute1, float attribute2,
                              float attribute3, const Vector3& barycentric);
  static Vector2 LerpInTriangle(const Vector2& attribute1,
                                const Vector2& attribute2,
                                const Vector2& attribute3,
                                const Vector3& barycentric);
  static Vector3 LerpInTriangle(const Vector3& attribute1,
                                const Vector3& attribute2,
                                const Vector3& attribute3,
                                const Vector3& barycentric);
  static Vector4 LerpInTriangle(const Vector4& attribute1,
                                const Vector4& attribute2,
                                const Vector4& attribute3,
                                const Vector3& barycentric);
  static float PlerpInLine(float attribute1, float attribute2,
                           const Vector2& barycentric, const Vector2& inv_w,
                           float interpolated_w);
  static Vector2 PlerpInLine(const Vector2& attribute1,
                             const Vector2& attribute2,
                             const Vector2& barycentric, const Vector2& inv_w,
                             float interpolated_w);
  static Vector3 PlerpInLine(const Vector3& attribute1,
                             const Vector3& attribute2,
                             const Vector2& barycentric, const Vector2& inv_w,
                             float interpolated_w);
  static Vector4 PlerpInLine(const Vector4& attribute1,
                             const Vector4& attribute2,
                             const Vector2& barycentric, const Vector2& inv_w,
                             float interpolated_w);
  static float PlerpInTriangle(float attribute1, float attribute2,
                               float attribute3, const Vector3& barycentric,
                               const Vector3& inv_w, float interpolated_w);
  static Vector2 PlerpInTriangle(const Vector2& attribute1,
                                 const Vector2& attribute2,
                                 const Vector2& attribute3,
                                 const Vector3& barycentric,
                                 const Vector3& inv_w, float interpolated_w);
  static Vector3 PlerpInTriangle(const Vector3& attribute1,
                                 const Vector3& attribute2,
                                 const Vector3& attribute3,
                                 const Vector3& barycentric,
                                 const Vector3& inv_w, float interpolated_w);
  static Vector4 PlerpInTriangle(const Vector4& attribute1,
                                 const Vector4& attribute2,
                                 const Vector4& attribute3,
                                 const Vector3& barycentric,
                                 const Vector3& inv_w, float interpolated_w);
  static float PlerpInLine_W(const Vector2& inv_w, const Vector2& barycentric);
  static float PlerpInTriangle_W(const Vector3& inv_w,
                                 const Vector3& barycentric);

  // Spherical linear interpolation
  // 1-scalar is used with q1, scalar is used with q2
  static Quaternion SlerpHalfRotationQuaternion(
      const Quaternion& half_rotation_quaternion1,
      const Quaternion& half_rotation_quaternion2, float scalar);
  static Quaternion SlerpHalfRotationQuaternionLong(
      const Quaternion& half_rotation_quaternion1,
      const Quaternion& half_rotation_quaternion2, float scalar);
};
}  // namespace ho_renderer
#endif  // _HORENDERER__INTERPOLATION_UTILS_H_