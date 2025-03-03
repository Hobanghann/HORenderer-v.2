#include "rendering_pipeline/pipeline_objects/include/primitive.h"

#include "app/include/debug.h"
#include "engine/color/include/linear_rgb.h"

namespace ho_renderer {
Primitive::Primitive() = default;
Primitive::Primitive(bool is_outof_frustum)
    : is_outof_frustum_(is_outof_frustum) {}
Primitive::Primitive(bool is_outof_frustum, const LinearRGB& color)
    : is_outof_frustum_(is_outof_frustum), color_(color) {}
Primitive::Primitive(const Primitive&) = default;
Primitive& Primitive::operator=(const Primitive&) = default;
Primitive::~Primitive() = default;

Primitive& Primitive::set_is_outof_frustum(bool arg) {
  is_outof_frustum_ = arg;
  return *this;
}
Primitive& Primitive::set_color(const LinearRGB& color) {
  color_ = color;
  return *this;
}

const bool Primitive::is_outof_frustum() const { return is_outof_frustum_; }
const LinearRGB& Primitive::color() const { return color_; }
}  // namespace ho_renderer