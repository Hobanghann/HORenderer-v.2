#include "rendering_pipeline/pipeline_objects/include/triangle.h"

#include "app/include/debug.h"

namespace ho_renderer {
Triangle::Triangle(const Triangle& triangle) = default;
Triangle::Triangle(int index0, int index1, int index2)
    : Primitive(false),
      index0_(index0),
      index1_(index1),
      index2_(index2),
      is_backface_(false) {}
Triangle::Triangle(int index0, int index1, int index2, std::uint32_t color_bit)
    : Primitive(false, color_bit),
      index0_(index0),
      index1_(index1),
      index2_(index2),
      is_backface_(false) {}
Triangle& Triangle::operator=(const Triangle& triangle) = default;
Triangle::~Triangle() = default;

const int Triangle::index0() const { return index0_; }
const int Triangle::index1() const { return index1_; }
const int Triangle::index2() const { return index2_; }
const bool Triangle::is_backface() const { return is_backface_; }

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
}  // namespace ho_renderer