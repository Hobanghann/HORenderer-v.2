#include "math/include/quaternion.h"

#include <cassert>

#include "math/include/math_utils.h"

namespace ho_renderer {
Quaternion::Quaternion() = default;
Quaternion::Quaternion(const Quaternion&) = default;
Quaternion::Quaternion(const Vector3& vector)
    : scalar_part_(0.f), vector_part_(vector) {}
Quaternion::Quaternion(const float scalar, const Vector3& vector)
    : scalar_part_(scalar), vector_part_(vector) {}
Quaternion::Quaternion(const float scalar1, const float scalar2,
                       const float scalar3, const float scalar4)
    : scalar_part_(scalar1), vector_part_(scalar2, scalar3, scalar4) {}
Quaternion& Quaternion::operator=(const Quaternion&) = default;
Quaternion::~Quaternion() = default;

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

Quaternion& Quaternion::operator*=(const float scalar) {
  scalar_part_ *= scalar;
  vector_part_ = scalar * vector_part_;
  return *this;
}
Quaternion& Quaternion::operator/=(const float scalar) {
  assert(scalar != 0.f);
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
  return Quaternion(scalar_part_, -1.f * vector_part_);
}
Quaternion Quaternion::GetAdditionInverseElement() const {
  return Quaternion(-1.f * scalar_part_, -1.f * vector_part_);
}
Quaternion Quaternion::GetMultiplicationInverseElement() const {
  return GetConjugation() / GetSqrdNorm();
}

bool Quaternion::IsPurelyImaginary() const { return scalar_part_ == 0.f; }
}  // namespace ho_renderer