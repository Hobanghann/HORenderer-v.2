#include "graphics/rendering_pipeline/pipeline_objects/include/line.h"

#include <cstdint>

#include "graphics/rendering_pipeline/pipeline_objects/include/primitive.h"

namespace ho_renderer {
Line::Line(const Line& line) = default;
Line::Line(const Material* mat, std::uint32_t index0, std::uint32_t index1)
    : Primitive(Type::kLine, mat), index0_(index0), index1_(index1) {}
Line& Line::operator=(const Line& line) = default;
Line::~Line() = default;

std::uint32_t Line::index0() const { return index0_; }
std::uint32_t Line::index1() const { return index1_; }

Line& Line::set_index0(std::uint32_t index) {
  index0_ = index;
  return *this;
}
Line& Line::set_index1(std::uint32_t index) {
  index1_ = index;
  return *this;
}
}  // namespace ho_renderer
