#ifndef _HORENDERER_MATH_QUATERNION_H_
#define _HORENDERER_MATH_QUATERNION_H_

#include <cassert>

#include "math/include/vector3.h"

namespace ho_renderer {
class Quaternion {
 public:
  Quaternion();
  Quaternion(const Quaternion&);
  explicit Quaternion(const Vector3& vector);
  Quaternion(const float scalar, const Vector3& vector);
  Quaternion(const float scalar1, const float scalar2, const float scalar3,
             const float scalar4);
  Quaternion& operator=(const Quaternion&);
  ~Quaternion();

  static Quaternion CreateRotationQuartation(const float angle,
                                             const Vector3& rotation_axis);

  static Quaternion CreateHalfRotationQuartation(const float angle,
                                                 const Vector3& rotation_axis);

  float scalar_part() const;
  const Vector3& vector_part() const;

  Quaternion& set_scalar_part(float scalar);
  Quaternion& set_vector_part(const Vector3& vector);

  Quaternion operator+(const Quaternion& quaternion) const;
  Quaternion& operator+=(const Quaternion& quaternion);

  Quaternion operator-(const Quaternion& quaternion) const;
  Quaternion& operator-=(const Quaternion& quaternion);

  Quaternion operator*(const Quaternion& quaternion) const;
  Quaternion& operator*=(const Quaternion& quaternion);

  Quaternion& operator*=(const float scalar);
  Quaternion& operator/=(const float scalar);

  float GetNorm() const;
  float GetSqrdNorm() const;
  Quaternion GetConjugation() const;
  Quaternion GetAdditionInverseElement() const;
  Quaternion GetMultiplicationInverseElement() const;

  bool IsPurelyImaginary() const;

 private:
  float scalar_part_;
  Vector3 vector_part_;
};

inline Quaternion operator*(const float scalar, const Quaternion& quaternion) {
  return Quaternion(scalar * quaternion.scalar_part(),
                    scalar * quaternion.vector_part());
}
inline Quaternion operator*(const Quaternion& quaternion, const float scalar) {
  return scalar * quaternion;
}

inline Quaternion operator/(const Quaternion& quaternion, const float scalar) {
  assert(scalar != 0.f);
  float inv_scalar = 1.f / scalar;
  return inv_scalar * quaternion;
}
}  // namespace ho_renderer

#endif