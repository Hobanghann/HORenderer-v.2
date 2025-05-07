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
  static Vector2 GetPixelBarycentric(const Vector2& target_pixel,
                                     const Vector2& pixel1,
                                     const Vector2& pixel2);
  static Vector3 GetPixelBarycentric(const Vector2& target_pixel,
                                     const Vector2& pixel1,
                                     const Vector2& pixel2,
                                     const Vector2& pixel3);
  static Vector2 GetNDCBarycentric(const Vector3& target_ndc,
                                   const Vector3& ndc1, const Vector3& ndc2);
  static Vector3 GetNDCBarycentric(const Vector3& target_ndc,
                                   const Vector3& ndc1, const Vector3& ndc2,
                                   const Vector3& ndc3);
  static Vector2 GetClipCoordinateBarycentric(const Vector4& target_coord,
                                              const Vector4& coord1,
                                              const Vector4& coord2);
  static Vector3 GetClipCoordinateBarycentric(const Vector4& target_coord,
                                              const Vector4& coord1,
                                              const Vector4& coord2,
                                              const Vector4& coord3);
  static float InterpolateAffineLine(float attribute1, float attribute2,
                                     const Vector2& ndc_barycentric);
  static Vector2 InterpolateAffineLine(const Vector2& attribute1,
                                       const Vector2& attribute2,
                                       const Vector2& ndc_barycentric);
  static Vector3 InterpolateAffineLine(const Vector3& attribute1,
                                       const Vector3& attribute2,
                                       const Vector2& ndc_barycentric);
  static Vector4 InterpolateAffineLine(const Vector4& attribute1,
                                       const Vector4& attribute2,
                                       const Vector2& ndc_barycentric);
  static float InterpolateAffineTriangle(float attribute1, float attribute2,
                                         float attribute3,
                                         const Vector3& ndc_barycentric);
  static Vector2 InterpolateAffineTriangle(const Vector2& attribute1,
                                           const Vector2& attribute2,
                                           const Vector2& attribute3,
                                           const Vector3& ndc_barycentric);
  static Vector3 InterpolateAffineTriangle(const Vector3& attribute1,
                                           const Vector3& attribute2,
                                           const Vector3& attribute3,
                                           const Vector3& ndc_barycentric);
  static Vector4 InterpolateAffineTriangle(const Vector4& attribute1,
                                           const Vector4& attribute2,
                                           const Vector4& attribute3,
                                           const Vector3& ndc_barycentric);
  static float InterpolatePerspectiveCorrectLine(float attribute1,
                                                 float attribute2,
                                                 const Vector2& ndc_barycentric,
                                                 const Vector2& inv_w,
                                                 float interpolated_w);
  static Vector2 InterpolatePerspectiveCorrectLine(
      const Vector2& attribute1, const Vector2& attribute2,
      const Vector2& ndc_barycentric, const Vector2& inv_w,
      float interpolated_w);
  static Vector3 InterpolatePerspectiveCorrectLine(
      const Vector3& attribute1, const Vector3& attribute2,
      const Vector2& ndc_barycentric, const Vector2& inv_w,
      float interpolated_w);
  static Vector4 InterpolatePerspectiveCorrectLine(
      const Vector4& attribute1, const Vector4& attribute2,
      const Vector2& ndc_barycentric, const Vector2& inv_w,
      float interpolated_w);
  static float InterpolatePerspectiveCorrectTriangle(
      float attribute1, float attribute2, float attribute3,
      const Vector3& ndc_barycentric, const Vector3& inv_w,
      float interpolated_w);
  static Vector2 InterpolatePerspectiveCorrectTriangle(
      const Vector2& attribute1, const Vector2& attribute2,
      const Vector2& attribute3, const Vector3& ndc_barycentric,
      const Vector3& inv_w, float interpolated_w);
  static Vector3 InterpolatePerspectiveCorrectTriangle(
      const Vector3& attribute1, const Vector3& attribute2,
      const Vector3& attribute3, const Vector3& ndc_barycentric,
      const Vector3& inv_w, float interpolated_w);
  static Vector4 InterpolatePerspectiveCorrectTriangle(
      const Vector4& attribute1, const Vector4& attribute2,
      const Vector4& attribute3, const Vector3& ndc_barycentric,
      const Vector3& inv_w, float interpolated_w);
  static float InterpolateWPerspectiveCorrectLine(
      const Vector2& inv_w, const Vector2& ndc_barycentric);
  static float InterpolateWPerspectiveCorrectTriangle(
      const Vector3& inv_w, const Vector3& ndc_barycentric);

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