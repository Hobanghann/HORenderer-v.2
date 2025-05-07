#include "graphics/rendering_pipeline/pipeline_objects/include/triangle.h"

#include <cstdint>

#include "core/math/include/vector3.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/primitive.h"

namespace ho_renderer {
Triangle::Triangle(const Triangle& triangle) = default;
Triangle::Triangle(const Material* material, std::uint32_t index0,
                   std::uint32_t index1, std::uint32_t index2)
    : Primitive(Type::kTriangle, material),
      index0_(index0),
      index1_(index1),
      index2_(index2),
      is_backface_(false) {}
Triangle::Triangle(const Material* material, std::uint32_t index0,
                   std::uint32_t index1, std::uint32_t index2,
                   const Vector3& normal_vector, const Vector3& center)
    : Primitive(Type::kTriangle, material),
      index0_(index0),
      index1_(index1),
      index2_(index2),
      normal_(normal_vector),
      center_(center),
      is_backface_(false) {}
Triangle& Triangle::operator=(const Triangle& triangle) = default;
Triangle::~Triangle() = default;

std::uint32_t Triangle::index0() const { return index0_; }
std::uint32_t Triangle::index1() const { return index1_; }
std::uint32_t Triangle::index2() const { return index2_; }
const Vector3& Triangle::normal() const { return normal_; }
const Vector3& Triangle::center() const { return center_; }
bool Triangle::is_backface() const { return is_backface_; }

Triangle& Triangle::set_index0(std::uint32_t index) {
  index0_ = index;
  return *this;
}
Triangle& Triangle::set_index1(std::uint32_t index) {
  index1_ = index;
  return *this;
}
Triangle& Triangle::set_index2(std::uint32_t index) {
  index2_ = index;
  return *this;
}
Triangle& Triangle::set_normal(const Vector3& v) {
  normal_ = v;
  return *this;
}
Triangle& Triangle::set_center(const Vector3& v) {
  center_ = v;
  return *this;
}
Triangle& Triangle::set_is_backface(bool arg) {
  is_backface_ = arg;
  return *this;
}

}  // namespace ho_renderer
