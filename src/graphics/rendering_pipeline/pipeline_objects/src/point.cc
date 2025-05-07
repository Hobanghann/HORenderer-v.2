#include "graphics/rendering_pipeline/pipeline_objects/include/point.h"

#include <cstdint>

#include "graphics/rendering_pipeline/pipeline_objects/include/primitive.h"
#include "graphics/resource/include/material.h"

namespace ho_renderer {
Point::Point(const Material* mat, std::uint32_t index0)
    : Primitive(Type::kPoint, mat), index0_(index0) {}
Point& Point::operator=(const Point& point) = default;
Point::~Point() = default;

std::uint32_t Point::index0() const { return index0_; }

Point& Point::set_index0(std::uint32_t index) {
  index0_ = index;
  return *this;
}
}  // namespace ho_renderer