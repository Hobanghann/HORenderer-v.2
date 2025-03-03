#include "rendering_pipeline/pipeline_objects/include/point.h"

#include "app/include/debug.h"
#include "engine/color/include/linear_rgb.h"

namespace ho_renderer {
Point::Point(const Point& point) = default;
Point::Point(int index0) : Primitive(false), index0_(index0) {}
Point::Point(int index0, const LinearRGB& color)
    : Primitive(false, color), index0_(index0) {}
Point& Point::operator=(const Point& point) = default;
Point::~Point() = default;

const int Point::index0() const { return index0_; }

Point& Point::set_index0(int index0) {
  index0_ = index0;
  return *this;
}
}  // namespace ho_renderer