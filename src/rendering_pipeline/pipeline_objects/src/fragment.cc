#include "rendering_pipeline/pipeline_objects/include/fragment.h"

#include "app/include/debug.h"

namespace ho_renderer {
Fragment::Fragment() = default;
Fragment::Fragment(const Fragment& fragment) = default;
Fragment::Fragment(PrimitiveType primitive_type, const Primitive* primitive,
                   const Vector2& coordinate, float interpolated_depth)
    : beloging_primitive_type_(primitive_type),
      belonging_primitive_(primitive),
      screen_coordinate_(coordinate),
      interpolated_depth_(interpolated_depth) {}
Fragment::Fragment(PrimitiveType primitive_type, const Primitive* primitive,
                   const Vector2& coordinate, std::uint32_t color_bit,
                   float interpolated_depth)
    : beloging_primitive_type_(primitive_type),
      screen_coordinate_(coordinate),
      color_bit_(color_bit),
      interpolated_depth_(interpolated_depth) {}
Fragment& Fragment::operator=(const Fragment& fragment) = default;
Fragment::~Fragment() = default;

const PrimitiveType Fragment::belonging_primitive_type() const {
  return beloging_primitive_type_;
}
const Primitive& Fragment::belonging_primitive() const {
  return *belonging_primitive_;
}
const Vector2& Fragment::screen_coordinate() const {
  return screen_coordinate_;
}
const std::uint32_t Fragment::color_bit() const { return color_bit_; }
const float Fragment::interpolated_depth() const { return interpolated_depth_; }

Fragment& Fragment::set_belonging_primitive_type(PrimitiveType primitive_type) {
  beloging_primitive_type_ = primitive_type;
  return *this;
}
Fragment& Fragment::set_belonging_primitive(Primitive* primitive) {
  belonging_primitive_ = primitive;
  return *this;
}
Fragment& Fragment::set_screen_coordinate(const Vector2& coordinate) {
  screen_coordinate_ = coordinate;
  return *this;
}
Fragment& Fragment::set_color_bit(std::uint32_t color_bit) {
  color_bit_ = color_bit;
  return *this;
}
Fragment& Fragment::set_interpolated_depth(float depth) {
  interpolated_depth_ = depth;
  return *this;
}

}  // namespace ho_renderer