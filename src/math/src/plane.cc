#include "math/include/plane.h"

#include <cassert>

#include "app/include/debug.h"
#include "math/include/math_utils.h"

namespace ho_renderer {
// construct plane from vector and point
Plane::Plane(const Vector3& normal_vector, const Vector3& point)
    : normal_vector_(normal_vector),
      normalized_normal_vector_(normal_vector.GetNormalized()),
      normal_dot_point_(normal_vector.Dot(point)) {}
// construct plane from coefficient
Plane::Plane(const Vector4& coefficient)
    : normal_vector_(
          Vector3(coefficient.x(), coefficient.y(), coefficient.z())),
      normalized_normal_vector_(normal_vector_.GetNormalized()),
      normal_dot_point_(-coefficient.w()) {}
Plane::Plane(const Plane&) = default;
Plane& Plane::operator=(const Plane&) = default;
Plane::~Plane() = default;

Vector3 Plane::normal_vector() const { return normal_vector_; }
Vector3 Plane::normalized_normal_vector() const {
  return normalized_normal_vector_;
}

float Plane::GetDistanceFromPoint(const Vector3& point) const {
  float inv_mag = MathUtils::InvSqrtf(normal_vector_.GetSqrdMagnitude());
  // if normal vector is zero vector -- plane can't define
  if (MathUtils::IsFloatNaN(inv_mag)) {
    assert(false);
  }
  return MathUtils::Abs(EvaluatePoint(point)) * inv_mag;
}
float Plane::EvaluatePoint(const Vector3& point) const {
  return normal_vector_.Dot(point) - normal_dot_point_;
}
}  // namespace ho_renderer