#include "rendering_pipeline/pipeline_objects/include/triangle.h"

#include "app/include/debug.h"
#include "engine/color/include/linear_rgb.h"

namespace ho_renderer {
Triangle::Triangle(const Triangle& triangle) = default;
Triangle::Triangle(int index0, int index1, int index2,
                   const Vector3& normal_vector)
    : Primitive(false),
      index0_(index0),
      index1_(index1),
      index2_(index2),
      normal_vector_(normal_vector),
      is_backface_(false) {}
Triangle::Triangle(int index0, int index1, int index2,
                   const Vector3& normal_vector, const LinearRGB& color)
    : Primitive(false, color),
      index0_(index0),
      index1_(index1),
      index2_(index2),
      normal_vector_(normal_vector),
      is_backface_(false) {}
Triangle::Triangle(int index0, int index1, int index2,
                   const Vector3& normal_vector, const LinearRGB& color,
                   float coefficient, float shininess)
    : Primitive(false, color),
      index0_(index0),
      index1_(index1),
      index2_(index2),
      normal_vector_(normal_vector),
      specular_reflection_coefficient_(coefficient),
      shininess_(shininess),
      is_backface_(false) {}
Triangle& Triangle::operator=(const Triangle& triangle) = default;
Triangle::~Triangle() = default;

const int Triangle::index0() const { return index0_; }
const int Triangle::index1() const { return index1_; }
const int Triangle::index2() const { return index2_; }
const bool Triangle::is_backface() const { return is_backface_; }
const Vector3& Triangle::normal_vector() const { return normal_vector_; }
const float Triangle::specular_reflection_coefficient() const {
  return specular_reflection_coefficient_;
}
const float Triangle::shininess() const { return shininess_; }

Triangle& Triangle::set_index0(int index0) {
  index0_ = index0;
  return *this;
}
Triangle& Triangle::set_index1(int index1) {
  index1_ = index1;
  return *this;
}
Triangle& Triangle::set_index2(int index2) {
  index2_ = index2;
  return *this;
}
Triangle& Triangle::set_is_backface(bool arg) {
  is_backface_ = arg;
  return *this;
}
Triangle& Triangle::set_normal_vector(const Vector3& normal_vector) {
  normal_vector_ = normal_vector;
  return *this;
}
Triangle& Triangle::set_specular_reflection_coefficient(const float c) {
  specular_reflection_coefficient_ = c;
  return *this;
}
Triangle& Triangle::set_shininess(const float s) {
  shininess_ = s;
  return *this;
}
}  // namespace ho_renderer