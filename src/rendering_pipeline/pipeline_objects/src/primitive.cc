#include "rendering_pipeline/pipeline_objects/include/primitive.h"

#include "app/include/debug.h"

namespace ho_renderer {
Primitive::Primitive() = default;
Primitive::Primitive(bool is_outof_frustum)
    : is_outof_frustum_(is_outof_frustum) {}
Primitive::Primitive(bool is_outof_frustum, std::uint32_t color_bit)
    : is_outof_frustum_(is_outof_frustum), color_bit_(color_bit) {}
Primitive::Primitive(const Primitive&) = default;
Primitive& Primitive::operator=(const Primitive&) = default;
Primitive::~Primitive() = default;

Primitive& Primitive::set_is_outof_frustum(bool arg) {
  is_outof_frustum_ = arg;
  return *this;
}
Primitive& Primitive::set_color_bit(std::uint32_t color_bit) {
  color_bit_ = color_bit;
  return *this;
}

const bool Primitive::is_outof_frustum() const { return is_outof_frustum_; }
const std::uint32_t Primitive::color_bit() const { return color_bit_; }
}  // namespace ho_renderer