#include "rendering_pipeline/pipeline_objects/include/line.h"

#include "app/include/debug.h"
#include "engine/color/include/linear_rgb.h"

namespace ho_renderer {
Line::Line(const Line& line) = default;
Line::Line(int index0, int index1)
    : Primitive(false), index0_(index0), index1_(index1) {}
Line::Line(int index0, int index1, const LinearRGB& color)
    : Primitive(false, color), index0_(index0), index1_(index1) {}
Line& Line::operator=(const Line& line) = default;
Line::~Line() = default;

const int Line::index0() const { return index0_; }
const int Line::index1() const { return index1_; }

Line& Line::set_index0(int index0) {
  index0_ = index0;
  return *this;
}
Line& Line::set_index1(int index1) {
  index1_ = index1;
  return *this;
}
}  // namespace ho_renderer