#include "core/math/include/interpolation_utils.h"

#include "core/math/include/math_utils.h"
#include "core/math/include/quaternion.h"
#include "core/math/include/vector2.h"
#include "core/math/include/vector3.h"
#include "core/math/include/vector4.h"

namespace ho_renderer {
// barycentric start from v2 to v1
Vector2 InterpolationUtils::GetBarycentric(const Vector2& target,
                                           const Vector2& v1,
                                           const Vector2& v2) {
  float denominator;
  float numerator;
  if (MathUtils::IsNotEqual(v1.x(), v2.x())) {
    denominator = v1.x() - v2.x();
    numerator = (target.x() - v2.x());
  } else if (MathUtils::IsNotEqual(v1.y(), v2.y())) {
    denominator = v1.y() - v2.y();
    numerator = (target.y() - v2.y());
  } else {
    return Vector2(MathUtils::kFloatNaN, MathUtils::kFloatNaN);
  }
  float lambda1 = numerator / denominator;
  return {lambda1, 1.f - lambda1};
}
Vector3 InterpolationUtils::GetBarycentric(const Vector2& target,
                                           const Vector2& v1, const Vector2& v2,
                                           const Vector2& v3) {
  Vector2 a = v1 - v3;
  Vector2 b = v2 - v3;
  Vector2 c = target - v3;
  float a_dot_a = a.Dot(a);
  float b_dot_b = b.Dot(b);
  float a_dot_b = a.Dot(b);
  float c_dot_a = c.Dot(a);
  float c_dot_b = c.Dot(b);
  float denominator = (a_dot_b * a_dot_b) - (a_dot_a * b_dot_b);
  if (MathUtils::IsEqual(denominator, 0.f)) {
    return Vector3(MathUtils::kFloatNaN, MathUtils::kFloatNaN,
                   MathUtils::kFloatNaN);
  }
  float inv_denominator = 1.f / denominator;
  float lambda1 = ((c_dot_b * a_dot_b) - (c_dot_a * b_dot_b)) * inv_denominator;
  float lambda2 = ((c_dot_a * a_dot_b) - (c_dot_b * a_dot_a)) * inv_denominator;
  return {lambda1, lambda2, 1.f - lambda1 - lambda2};
}
Vector2 InterpolationUtils::GetBarycentric(const Vector3& target,
                                           const Vector3& v1,
                                           const Vector3& v2) {
  float denominator;
  float numerator;
  if (MathUtils::IsNotEqual(v1.x(), v2.x())) {
    denominator = v1.x() - v2.x();
    numerator = (target.x() - v2.x());
  } else if (MathUtils::IsNotEqual(v1.y(), v2.y())) {
    denominator = v1.y() - v2.y();
    numerator = (target.y() - v2.y());
  } else if (MathUtils::IsNotEqual(v1.z(), v2.z())) {
    denominator = v1.z() - v2.z();
    numerator = (target.z() - v2.z());
  } else {
    return Vector2(MathUtils::kFloatNaN, MathUtils::kFloatNaN);
  }
  float lambda1 = numerator / denominator;
  return {lambda1, 1.f - lambda1};
}
Vector3 InterpolationUtils::GetBarycentric(const Vector3& target,
                                           const Vector3& v1, const Vector3& v2,
                                           const Vector3& v3) {
  Vector3 a = v1 - v3;
  Vector3 b = v2 - v3;
  Vector3 c = target - v3;
  float a_dot_a = a.Dot(a);
  float b_dot_b = b.Dot(b);
  float a_dot_b = a.Dot(b);
  float c_dot_a = c.Dot(a);
  float c_dot_b = c.Dot(b);
  float denominator = (a_dot_b * a_dot_b) - (a_dot_a * b_dot_b);
  if (MathUtils::IsEqual(denominator, 0.f)) {
    return Vector3(MathUtils::kFloatNaN, MathUtils::kFloatNaN,
                   MathUtils::kFloatNaN);
  }
  float inv_denominator = 1.f / denominator;
  float lambda1 = ((c_dot_b * a_dot_b) - (c_dot_a * b_dot_b)) * inv_denominator;
  float lambda2 = ((c_dot_a * a_dot_b) - (c_dot_b * a_dot_a)) * inv_denominator;
  return {lambda1, lambda2, 1.f - lambda1 - lambda2};
}
Vector2 InterpolationUtils::GetBarycentric(const Vector4& target,
                                           const Vector4& v1,
                                           const Vector4& v2) {
  float denominator;
  float numerator;
  if (MathUtils::IsNotEqual(v1.x(), v2.x())) {
    denominator = v1.x() - v2.x();
    numerator = (target.x() - v2.x());
  } else if (MathUtils::IsNotEqual(v1.y(), v2.y())) {
    denominator = v1.y() - v2.y();
    numerator = (target.y() - v2.y());
  } else if (MathUtils::IsNotEqual(v1.z(), v2.z())) {
    denominator = v1.z() - v2.z();
    numerator = (target.z() - v2.z());
  } else if (MathUtils::IsNotEqual(v1.w(), v2.w())) {
    denominator = v1.w() - v2.w();
    numerator = (target.w() - v2.w());
  } else {
    return Vector2(MathUtils::kFloatNaN, MathUtils::kFloatNaN);
  }
  float lambda1 = numerator / denominator;
  return {lambda1, 1.f - lambda1};
}
Vector3 InterpolationUtils::GetBarycentric(const Vector4& target,
                                           const Vector4& v1, const Vector4& v2,
                                           const Vector4& v3) {
  Vector4 a = v1 - v3;
  Vector4 b = v2 - v3;
  Vector4 c = target - v3;
  float a_dot_a = a.Dot(a);
  float b_dot_b = b.Dot(b);
  float a_dot_b = a.Dot(b);
  float c_dot_a = c.Dot(a);
  float c_dot_b = c.Dot(b);
  float denominator = (a_dot_b * a_dot_b) - (a_dot_a * b_dot_b);
  if (MathUtils::IsEqual(denominator, 0.f)) {
    return Vector3(MathUtils::kFloatNaN, MathUtils::kFloatNaN,
                   MathUtils::kFloatNaN);
  }
  float inv_denominator = 1.f / denominator;
  float lambda1 = ((c_dot_b * a_dot_b) - (c_dot_a * b_dot_b)) * inv_denominator;
  float lambda2 = ((c_dot_a * a_dot_b) - (c_dot_b * a_dot_a)) * inv_denominator;
  return {lambda1, lambda2, 1.f - lambda1 - lambda2};
}

float InterpolationUtils::LerpInLine(float attribute1, float attribute2,
                                     const Vector2& barycentric) {
  return barycentric.x() * attribute1 + barycentric.y() * attribute2;
}
Vector2 ho_renderer::InterpolationUtils::LerpInLine(
    const Vector2& attribute1, const Vector2& attribute2,
    const Vector2& barycentric) {
  return barycentric.x() * attribute1 + barycentric.y() * attribute2;
}
Vector3 ho_renderer::InterpolationUtils::LerpInLine(
    const Vector3& attribute1, const Vector3& attribute2,
    const Vector2& barycentric) {
  return barycentric.x() * attribute1 + barycentric.y() * attribute2;
}
Vector4 ho_renderer::InterpolationUtils::LerpInLine(
    const Vector4& attribute1, const Vector4& attribute2,
    const Vector2& barycentric) {
  return barycentric.x() * attribute1 + barycentric.y() * attribute2;
}
float InterpolationUtils::LerpInTriangle(float attribute1, float attribute2,
                                         float attribute3,
                                         const Vector3& barycentric) {
  return barycentric.x() * attribute1 + barycentric.y() * attribute2 +
         barycentric.z() * attribute3;
}
Vector2 InterpolationUtils::LerpInTriangle(const Vector2& attribute1,
                                           const Vector2& attribute2,
                                           const Vector2& attribute3,
                                           const Vector3& barycentric) {
  return barycentric.x() * attribute1 + barycentric.y() * attribute2 +
         barycentric.z() * attribute3;
}
Vector3 InterpolationUtils::LerpInTriangle(const Vector3& attribute1,
                                           const Vector3& attribute2,
                                           const Vector3& attribute3,
                                           const Vector3& barycentric) {
  return barycentric.x() * attribute1 + barycentric.y() * attribute2 +
         barycentric.z() * attribute3;
}
Vector4 InterpolationUtils::LerpInTriangle(const Vector4& attribute1,
                                           const Vector4& attribute2,
                                           const Vector4& attribute3,
                                           const Vector3& barycentric) {
  return barycentric.x() * attribute1 + barycentric.y() * attribute2 +
         barycentric.z() * attribute3;
}
float InterpolationUtils::PlerpInLine(float attribute1, float attribute2,
                                      const Vector2& barycentric,
                                      const Vector2& inv_w,
                                      float interpolated_w) {
  return interpolated_w * (inv_w.x() * barycentric.x() * attribute1 +
                           inv_w.y() * barycentric.y() * attribute2);
}
Vector2 InterpolationUtils::PlerpInLine(const Vector2& attribute1,
                                        const Vector2& attribute2,
                                        const Vector2& barycentric,
                                        const Vector2& inv_w,
                                        float interpolated_w) {
  return interpolated_w * (inv_w.x() * barycentric.x() * attribute1 +
                           inv_w.y() * barycentric.y() * attribute2);
}
Vector3 InterpolationUtils::PlerpInLine(const Vector3& attribute1,
                                        const Vector3& attribute2,
                                        const Vector2& barycentric,
                                        const Vector2& inv_w,
                                        float interpolated_w) {
  return interpolated_w * (inv_w.x() * barycentric.x() * attribute1 +
                           inv_w.y() * barycentric.y() * attribute2);
}
Vector4 InterpolationUtils::PlerpInLine(const Vector4& attribute1,
                                        const Vector4& attribute2,
                                        const Vector2& barycentric,
                                        const Vector2& inv_w,
                                        float interpolated_w) {
  return interpolated_w * (inv_w.x() * barycentric.x() * attribute1 +
                           inv_w.y() * barycentric.y() * attribute2);
}
float InterpolationUtils::PlerpInTriangle(float attribute1, float attribute2,
                                          float attribute3,
                                          const Vector3& barycentric,
                                          const Vector3& inv_w,
                                          float interpolated_w) {
  return interpolated_w * (inv_w.x() * barycentric.x() * attribute1 +
                           inv_w.y() * barycentric.y() * attribute2 +
                           inv_w.z() * barycentric.z() * attribute3);
}
Vector2 InterpolationUtils::PlerpInTriangle(const Vector2& attribute1,
                                            const Vector2& attribute2,
                                            const Vector2& attribute3,
                                            const Vector3& barycentric,
                                            const Vector3& inv_w,
                                            float interpolated_w) {
  return interpolated_w * (inv_w.x() * barycentric.x() * attribute1 +
                           inv_w.y() * barycentric.y() * attribute2 +
                           inv_w.z() * barycentric.z() * attribute3);
}
Vector3 InterpolationUtils::PlerpInTriangle(const Vector3& attribute1,
                                            const Vector3& attribute2,
                                            const Vector3& attribute3,
                                            const Vector3& barycentric,
                                            const Vector3& inv_w,
                                            float interpolated_w) {
  return interpolated_w * (inv_w.x() * barycentric.x() * attribute1 +
                           inv_w.y() * barycentric.y() * attribute2 +
                           inv_w.z() * barycentric.z() * attribute3);
}
Vector4 InterpolationUtils::PlerpInTriangle(const Vector4& attribute1,
                                            const Vector4& attribute2,
                                            const Vector4& attribute3,
                                            const Vector3& barycentric,
                                            const Vector3& inv_w,
                                            float interpolated_w) {
  return interpolated_w * (inv_w.x() * barycentric.x() * attribute1 +
                           inv_w.y() * barycentric.y() * attribute2 +
                           inv_w.z() * barycentric.z() * attribute3);
}
float InterpolationUtils::PlerpInLine_W(const Vector2& inv_w,
                                        const Vector2& barycentric) {
  return 1.f / (barycentric.x() * inv_w.x() + barycentric.y() * inv_w.y());
}
float InterpolationUtils::PlerpInTriangle_W(const Vector3& inv_w,
                                            const Vector3& barycentric) {
  return 1.f / (barycentric.x() * inv_w.x() + barycentric.y() * inv_w.y() +
                barycentric.z() * inv_w.z());
}
// Spherical linear interpolation
Quaternion InterpolationUtils::SlerpHalfRotationQuaternion(
    const Quaternion& half_rotation_quaternion1,
    const Quaternion& half_rotation_quaternion2, float scalar) {
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
    const Quaternion& half_rotation_quaternion2, float scalar) {
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