#include "math/include/interpolation_utils.h"

#include <cassert>
#include <string>

#include "app/include/debug.h"
#include "math/include/math_utils.h"

namespace ho_renderer {
// barycentric start from pixel2 to pixel1
Vector2 InterpolationUtils::GetPixelBarycentric(const Vector2& target_pixel,
                                                const Vector2& pixel1,
                                                const Vector2& pixel2) {
  float denominator;
  float numerator;
  if (MathUtils::IsNotEqual(pixel1.x(), pixel2.x())) {
    denominator = pixel1.x() - pixel2.x();
    numerator = (target_pixel.x() - pixel2.x());
  } else if (MathUtils::IsNotEqual(pixel1.y(), pixel2.y())) {
    denominator = pixel1.y() - pixel2.y();
    numerator = (target_pixel.y() - pixel2.y());
  } else {
    return Vector2(MathUtils::kFLOAT_NAN, MathUtils::kFLOAT_NAN);
  }
  float lambda1 = numerator / denominator;
  return {lambda1, 1.f - lambda1};
}
Vector3 InterpolationUtils::GetPixelBarycentric(const Vector2& target_pixel,
                                                const Vector2& pixel1,
                                                const Vector2& pixel2,
                                                const Vector2& pixel3) {
  Vector2 a = pixel1 - pixel3;
  Vector2 b = pixel2 - pixel3;
  Vector2 c = target_pixel - pixel3;
  float a_dot_a = a.Dot(a);
  float b_dot_b = b.Dot(b);
  float a_dot_b = a.Dot(b);
  float c_dot_a = c.Dot(a);
  float c_dot_b = c.Dot(b);
  float denominator = (a_dot_b * a_dot_b) - (a_dot_a * b_dot_b);
  if (MathUtils::IsEqual(denominator, 0.f)) {
    return Vector3(MathUtils::kFLOAT_NAN, MathUtils::kFLOAT_NAN,
                   MathUtils::kFLOAT_NAN);
  }
  float inv_denominator = 1.f / denominator;
  float lambda1 = ((c_dot_b * a_dot_b) - (c_dot_a * b_dot_b)) * inv_denominator;
  float lambda2 = ((c_dot_a * a_dot_b) - (c_dot_b * a_dot_a)) * inv_denominator;
  return {lambda1, lambda2, 1.f - lambda1 - lambda2};
}
Vector2 InterpolationUtils::GetNDCBarycentric(const Vector3& target_ndc,
                                              const Vector3& ndc1,
                                              const Vector3& ndc2) {
  float denominator;
  float numerator;
  if (MathUtils::IsNotEqual(ndc1.x(), ndc2.x())) {
    denominator = ndc1.x() - ndc2.x();
    numerator = (target_ndc.x() - ndc2.x());
  } else if (MathUtils::IsNotEqual(ndc1.y(), ndc2.y())) {
    denominator = ndc1.y() - ndc2.y();
    numerator = (target_ndc.y() - ndc2.y());
  } else if (MathUtils::IsNotEqual(ndc1.z(), ndc2.z())) {
    denominator = ndc1.z() - ndc2.z();
    numerator = (target_ndc.z() - ndc2.z());
  } else {
    return Vector2(MathUtils::kFLOAT_NAN, MathUtils::kFLOAT_NAN);
  }
  float lambda1 = numerator / denominator;
  return {lambda1, 1.f - lambda1};
}
Vector3 InterpolationUtils::GetNDCBarycentric(const Vector3& target_ndc,
                                              const Vector3& ndc1,
                                              const Vector3& ndc2,
                                              const Vector3& ndc3) {
  Vector3 a = ndc1 - ndc3;
  Vector3 b = ndc2 - ndc3;
  Vector3 c = target_ndc - ndc3;
  float a_dot_a = a.Dot(a);
  float b_dot_b = b.Dot(b);
  float a_dot_b = a.Dot(b);
  float c_dot_a = c.Dot(a);
  float c_dot_b = c.Dot(b);
  float denominator = (a_dot_b * a_dot_b) - (a_dot_a * b_dot_b);
  if (MathUtils::IsEqual(denominator, 0.f)) {
    return Vector3(MathUtils::kFLOAT_NAN, MathUtils::kFLOAT_NAN,
                   MathUtils::kFLOAT_NAN);
  }
  float inv_denominator = 1.f / denominator;
  float lambda1 = ((c_dot_b * a_dot_b) - (c_dot_a * b_dot_b)) * inv_denominator;
  float lambda2 = ((c_dot_a * a_dot_b) - (c_dot_b * a_dot_a)) * inv_denominator;
  return {lambda1, lambda2, 1.f - lambda1 - lambda2};
}
Vector2 InterpolationUtils::GetClipCoordinateBarycentric(
    const Vector4& target_coordinate, const Vector4& coordinate1,
    const Vector4& coordinate2) {
  float denominator;
  float numerator;
  if (MathUtils::IsNotEqual(coordinate1.x(), coordinate2.x())) {
    denominator = coordinate1.x() - coordinate2.x();
    numerator = (target_coordinate.x() - coordinate2.x());
  } else if (MathUtils::IsNotEqual(coordinate1.y(), coordinate2.y())) {
    denominator = coordinate1.y() - coordinate2.y();
    numerator = (target_coordinate.y() - coordinate2.y());
  } else if (MathUtils::IsNotEqual(coordinate1.z(), coordinate2.z())) {
    denominator = coordinate1.z() - coordinate2.z();
    numerator = (target_coordinate.z() - coordinate2.z());
  } else if (MathUtils::IsNotEqual(coordinate1.w(), coordinate2.w())) {
    denominator = coordinate1.w() - coordinate2.w();
    numerator = (target_coordinate.w() - coordinate2.w());
  } else {
    return Vector2(MathUtils::kFLOAT_NAN, MathUtils::kFLOAT_NAN);
  }
  float lambda1 = numerator / denominator;
  return {lambda1, 1.f - lambda1};
}
Vector3 InterpolationUtils::GetClipCoordinateBarycentric(
    const Vector4& target_coordinate, const Vector4& coordinate1,
    const Vector4& coordinate2, const Vector4& coordinate3) {
  Vector4 a = coordinate1 - coordinate3;
  Vector4 b = coordinate2 - coordinate3;
  Vector4 c = target_coordinate - coordinate3;
  float a_dot_a = a.Dot(a);
  float b_dot_b = b.Dot(b);
  float a_dot_b = a.Dot(b);
  float c_dot_a = c.Dot(a);
  float c_dot_b = c.Dot(b);
  float denominator = (a_dot_b * a_dot_b) - (a_dot_a * b_dot_b);
  if (MathUtils::IsEqual(denominator, 0.f)) {
    return Vector3(MathUtils::kFLOAT_NAN, MathUtils::kFLOAT_NAN,
                   MathUtils::kFLOAT_NAN);
  }
  float inv_denominator = 1.f / denominator;
  float lambda1 = ((c_dot_b * a_dot_b) - (c_dot_a * b_dot_b)) * inv_denominator;
  float lambda2 = ((c_dot_a * a_dot_b) - (c_dot_b * a_dot_a)) * inv_denominator;
  return {lambda1, lambda2, 1.f - lambda1 - lambda2};
}

float InterpolationUtils::InterpolateAffineLine(
    const float& attribute1, const float& attribute2,
    const Vector2& ndc_barycentric) {
  return ndc_barycentric.x() * attribute1 + ndc_barycentric.y() * attribute2;
}
Vector2 ho_renderer::InterpolationUtils::InterpolateAffineLine(
    const Vector2& attribute1, const Vector2& attribute2,
    const Vector2& ndc_barycentric) {
  return ndc_barycentric.x() * attribute1 + ndc_barycentric.y() * attribute2;
}
Vector3 ho_renderer::InterpolationUtils::InterpolateAffineLine(
    const Vector3& attribute1, const Vector3& attribute2,
    const Vector2& ndc_barycentric) {
  return ndc_barycentric.x() * attribute1 + ndc_barycentric.y() * attribute2;
}
Vector4 ho_renderer::InterpolationUtils::InterpolateAffineLine(
    const Vector4& attribute1, const Vector4& attribute2,
    const Vector2& ndc_barycentric) {
  return ndc_barycentric.x() * attribute1 + ndc_barycentric.y() * attribute2;
}
float InterpolationUtils::InterpolateAffineTriangle(
    const float& attribute1, const float& attribute2, const float& attribute3,
    const Vector3& ndc_barycentric) {
  return ndc_barycentric.x() * attribute1 + ndc_barycentric.y() * attribute2 +
         ndc_barycentric.z() * attribute3;
}
Vector2 InterpolationUtils::InterpolateAffineTriangle(
    const Vector2& attribute1, const Vector2& attribute2,
    const Vector2& attribute3, const Vector3& ndc_barycentric) {
  return ndc_barycentric.x() * attribute1 + ndc_barycentric.y() * attribute2 +
         ndc_barycentric.z() * attribute3;
}
Vector3 InterpolationUtils::InterpolateAffineTriangle(
    const Vector3& attribute1, const Vector3& attribute2,
    const Vector3& attribute3, const Vector3& ndc_barycentric) {
  return ndc_barycentric.x() * attribute1 + ndc_barycentric.y() * attribute2 +
         ndc_barycentric.z() * attribute3;
}
Vector4 InterpolationUtils::InterpolateAffineTriangle(
    const Vector4& attribute1, const Vector4& attribute2,
    const Vector4& attribute3, const Vector3& ndc_barycentric) {
  return ndc_barycentric.x() * attribute1 + ndc_barycentric.y() * attribute2 +
         ndc_barycentric.z() * attribute3;
}
float InterpolationUtils::InterpolatePerspectiveCorrectLine(
    const float& attribute1, const float& attribute2,
    const Vector2& ndc_barycentric, const Vector2& inv_w,
    float interpolated_w) {
  return interpolated_w * (inv_w.x() * ndc_barycentric.x() * attribute1 +
                           inv_w.y() * ndc_barycentric.y() * attribute2);
}
Vector2 InterpolationUtils::InterpolatePerspectiveCorrectLine(
    const Vector2& attribute1, const Vector2& attribute2,
    const Vector2& ndc_barycentric, const Vector2& inv_w,
    float interpolated_w) {
  return interpolated_w * (inv_w.x() * ndc_barycentric.x() * attribute1 +
                           inv_w.y() * ndc_barycentric.y() * attribute2);
}
Vector3 InterpolationUtils::InterpolatePerspectiveCorrectLine(
    const Vector3& attribute1, const Vector3& attribute2,
    const Vector2& ndc_barycentric, const Vector2& inv_w,
    float interpolated_w) {
  return interpolated_w * (inv_w.x() * ndc_barycentric.x() * attribute1 +
                           inv_w.y() * ndc_barycentric.y() * attribute2);
}
Vector4 InterpolationUtils::InterpolatePerspectiveCorrectLine(
    const Vector4& attribute1, const Vector4& attribute2,
    const Vector2& ndc_barycentric, const Vector2& inv_w,
    float interpolated_w) {
  return interpolated_w * (inv_w.x() * ndc_barycentric.x() * attribute1 +
                           inv_w.y() * ndc_barycentric.y() * attribute2);
}
float InterpolationUtils::InterpolatePerspectiveCorrectTriangle(
    const float& attribute1, const float& attribute2, const float& attribute3,
    const Vector3& ndc_barycentric, const Vector3& inv_w,
    float interpolated_w) {
  return interpolated_w * (inv_w.x() * ndc_barycentric.x() * attribute1 +
                           inv_w.y() * ndc_barycentric.y() * attribute2 +
                           inv_w.z() * ndc_barycentric.z() * attribute3);
}
Vector2 InterpolationUtils::InterpolatePerspectiveCorrectTriangle(
    const Vector2& attribute1, const Vector2& attribute2,
    const Vector2& attribute3, const Vector3& ndc_barycentric,
    const Vector3& inv_w, float interpolated_w) {
  return interpolated_w * (inv_w.x() * ndc_barycentric.x() * attribute1 +
                           inv_w.y() * ndc_barycentric.y() * attribute2 +
                           inv_w.z() * ndc_barycentric.z() * attribute3);
}
Vector3 InterpolationUtils::InterpolatePerspectiveCorrectTriangle(
    const Vector3& attribute1, const Vector3& attribute2,
    const Vector3& attribute3, const Vector3& ndc_barycentric,
    const Vector3& inv_w, float interpolated_w) {
  return interpolated_w * (inv_w.x() * ndc_barycentric.x() * attribute1 +
                           inv_w.y() * ndc_barycentric.y() * attribute2 +
                           inv_w.z() * ndc_barycentric.z() * attribute3);
}
Vector4 InterpolationUtils::InterpolatePerspectiveCorrectTriangle(
    const Vector4& attribute1, const Vector4& attribute2,
    const Vector4& attribute3, const Vector3& ndc_barycentric,
    const Vector3& inv_w, float interpolated_w) {
  return interpolated_w * (inv_w.x() * ndc_barycentric.x() * attribute1 +
                           inv_w.y() * ndc_barycentric.y() * attribute2 +
                           inv_w.z() * ndc_barycentric.z() * attribute3);
}
float InterpolationUtils::InterpolateWPerspectiveCorrectLine(
    const Vector2& inv_w, const Vector2& ndc_barycentric) {
  return 1.f /
         (ndc_barycentric.x() * inv_w.x() + ndc_barycentric.y() * inv_w.y());
}
float InterpolationUtils::InterpolateWPerspectiveCorrectTriangle(
    const Vector3& inv_w, const Vector3& ndc_barycentric) {
  return 1.f /
         (ndc_barycentric.x() * inv_w.x() + ndc_barycentric.y() * inv_w.y() +
          ndc_barycentric.z() * inv_w.z());
}
// Spherical linear interpolation
Quaternion InterpolationUtils::SlerpHalfRotationQuaternionShort(
    const Quaternion& half_rotation_quaternion1,
    const Quaternion& half_rotation_quaternion2, const float scalar) {
  const Quaternion& q1 = half_rotation_quaternion1;
  Quaternion q2 = half_rotation_quaternion2;
  float alpha = 1.f - scalar;  // scalar of q1
  float beta = scalar;         // scalar of q2
  float q1_dot_q2 = Vector4(q1).Dot(Vector4(q2));
  // if q1 and q2 are parallel, interpolate linearly.
  if (MathUtils::IsNotEqual(q1_dot_q2, 1.f)) {
    if (q1_dot_q2 < 0.f) {
      q2 *= -1.f;
      q1_dot_q2 *= -1.f;
    }
    float angle = MathUtils::Acosf(q1_dot_q2);
    float inv_sin = 1.f / MathUtils::Sinf(angle);
    alpha = MathUtils::Sinf(angle * (1.f - scalar)) * inv_sin;
    beta = MathUtils::Sinf(angle * scalar) * inv_sin;
  }
  return alpha * q1 + beta * q2;
}
Quaternion InterpolationUtils::SlerpHalfRotationQuaternionLong(
    const Quaternion& half_rotation_quaternion1,
    const Quaternion& half_rotation_quaternion2, const float scalar) {
  const Quaternion& q1 = half_rotation_quaternion1;
  Quaternion q2 = half_rotation_quaternion2;
  float alpha = 1.f - scalar;  // scalar of q1
  float beta = scalar;         // scalar of q2
  float q1_dot_q2 = Vector4(q1).Dot(Vector4(q2));
  // if q1 and q2 are parallel, interpolate linearly.
  if (MathUtils::IsNotEqual(q1_dot_q2, 1.f)) {
    if (q1_dot_q2 > 0.f) {
      q2 *= -1.f;
      q1_dot_q2 *= -1.f;
    }
    float angle = MathUtils::Acosf(q1_dot_q2);
    float inv_sin = 1.f / MathUtils::Sinf(angle);
    alpha = MathUtils::Sinf(angle * (1.f - scalar)) * inv_sin;
    beta = MathUtils::Sinf(angle * scalar) * inv_sin;
  }
  return alpha * q1 + beta * q2;
}
}  // namespace ho_renderer