#include "core/math/include/quaternion.h"

#include <string>

#include "core/math/include/math_utils.h"
#include "core/math/include/vector3.h"

namespace ho_renderer {
Quaternion::Quaternion() = default;
Quaternion::Quaternion(const Quaternion&) = default;
Quaternion::Quaternion(const Vector3& vector)
    : scalar_part_(0.f), vector_part_(vector) {}
Quaternion::Quaternion(float scalar, const Vector3& vector)
    : scalar_part_(scalar), vector_part_(vector) {}
Quaternion::Quaternion(float scalar1, float scalar2, float scalar3,
                       float scalar4)
    : scalar_part_(scalar1), vector_part_(scalar2, scalar3, scalar4) {}
Quaternion& Quaternion::operator=(const Quaternion&) = default;
Quaternion::~Quaternion() = default;

Quaternion Quaternion::CreateRotationQuartation(float angle,
                                                const Vector3& rotation_axis) {
  float sin;
  float cos;
  MathUtils::SinCosf(sin, cos, angle);
  return Quaternion(cos, sin * rotation_axis.GetNormalized());
}

Quaternion Quaternion::CreateHalfRotationQuartation(
    float angle, const Vector3& rotation_axis) {
  float sin;
  float cos;
  MathUtils::SinCosf(sin, cos, angle * 0.5f);
  return Quaternion(cos, sin * rotation_axis.GetNormalized());
}

float Quaternion::scalar_part() const { return scalar_part_; }
const Vector3& Quaternion::vector_part() const { return vector_part_; }

Quaternion& Quaternion::set_scalar_part(float scalar) {
  scalar_part_ = scalar;
  return *this;
}
Quaternion& Quaternion::set_vector_part(const Vector3& vector) {
  vector_part_ = vector;
  return *this;
}

Quaternion Quaternion::operator+(const Quaternion& quaternion) const {
  return Quaternion(scalar_part_ + quaternion.scalar_part_,
                    vector_part_ + quaternion.vector_part_);
}
Quaternion& Quaternion::operator+=(const Quaternion& quaternion) {
  scalar_part_ += quaternion.scalar_part_;
  vector_part_ += quaternion.vector_part_;
  return *this;
}

Quaternion Quaternion::operator-(const Quaternion& quaternion) const {
  return Quaternion(scalar_part_ - quaternion.scalar_part_,
                    vector_part_ - quaternion.vector_part_);
}
Quaternion& Quaternion::operator-=(const Quaternion& quaternion) {
  scalar_part_ -= quaternion.scalar_part_;
  vector_part_ -= quaternion.vector_part_;
  return *this;
}

Quaternion Quaternion::operator*(const Quaternion& quaternion) const {
  return Quaternion(scalar_part_ * quaternion.scalar_part_ -
                        vector_part_.Dot(quaternion.vector_part_),
                    scalar_part_ * quaternion.vector_part_ +
                        quaternion.scalar_part_ * vector_part_ +
                        vector_part_.Cross(quaternion.vector_part_));
}
Quaternion& Quaternion::operator*=(const Quaternion& quaternion) {
  scalar_part_ = scalar_part_ * quaternion.scalar_part_ -
                 vector_part_.Dot(quaternion.vector_part_);
  vector_part_ = scalar_part_ * quaternion.vector_part_ +
                 quaternion.scalar_part_ * vector_part_ +
                 vector_part_.Cross(quaternion.vector_part_);
  return *this;
}

Quaternion& Quaternion::operator*=(float scalar) {
  scalar_part_ *= scalar;
  vector_part_ = scalar * vector_part_;
  return *this;
}
Quaternion& Quaternion::operator/=(float scalar) {
  float inv_scalar = 1.f / scalar;
  *this *= inv_scalar;
  return *this;
}

float Quaternion::GetNorm() const {
  return MathUtils::Sqrtf(scalar_part_ * scalar_part_ +
                          vector_part_.GetSqrdMagnitude());
}
float Quaternion::GetSqrdNorm() const {
  return scalar_part_ * scalar_part_ + vector_part_.GetSqrdMagnitude();
}
Quaternion Quaternion::GetConjugation() const {
  return Quaternion(scalar_part_, -vector_part_);
}
Quaternion Quaternion::GetAdditionInverseElement() const {
  return Quaternion(-scalar_part_, -vector_part_);
}
Quaternion Quaternion::GetMultiplicationInverseElement() const {
  float sqrd_norm = GetSqrdNorm();
  if (MathUtils::IsEqual(sqrd_norm, 0.f)) {
    return *this;
  }
  return GetConjugation() / sqrd_norm;
}

bool Quaternion::IsPurelyImaginary() const {
  return MathUtils::IsEqual(scalar_part_, 0.f);
}

std::string Quaternion::ToString() const {
  char buf[100];
  snprintf(buf, sizeof(buf), "%.3f + %.3f*i, + %.3f*j + %.3f*k", scalar_part_,
           vector_part_.x(), vector_part_.y(), vector_part_.z());
  return buf;
}
}  // namespace ho_renderer