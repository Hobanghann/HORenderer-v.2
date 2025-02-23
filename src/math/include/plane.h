#ifndef _HORENDERER_MATH_PLANE_H_
#define _HORENDERER_MATH_PLANE_H_

#include "math/include/vector3.h"
#include "math/include/vector4.h"

// plane defined by normal vector and 1 point
// when plane defined by 4-dimensional vector, x, y, z component is normal
// vector component, w component is -(scalar product normal vector and point)
namespace ho_renderer {
class Plane {
 public:
  // construct plane from vector and point
  Plane(const Vector3& normal_vector, const Vector3& point);
  // construct plane from coefficient
  Plane(const Vector4& coefficient);
  Plane(const Plane&);
  Plane& operator=(const Plane&);
  ~Plane();

  Vector3 normal_vector() const;
  Vector3 normalized_normal_vector() const;

  float GetDistanceFromPoint(const Vector3& point) const;
  float EvaluatePoint(const Vector3& point) const;

 private:
  Vector3 normal_vector_;
  Vector3 normalized_normal_vector_;
  float normal_dot_point_;
};

}  // namespace ho_renderer

#endif  // _HORENDERER_MATH_PLANE_H_