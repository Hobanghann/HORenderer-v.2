#include "rendering_pipeline/pipeline_objects/include/fragment.h"

#include "app/include/debug.h"
#include "engine/color/include/linear_rgb.h"

namespace ho_renderer {
Fragment::Fragment() = default;
Fragment::Fragment(const Fragment& fragment) = default;
Fragment::Fragment(PrimitiveType primitive_type, const Primitive* primitive,
                   const Vector3& view_coordinate, const Vector2& coordinate,
                   float interpolated_depth)
    : beloging_primitive_type_(primitive_type),
      belonging_primitive_(primitive),
      view_coordinate_(view_coordinate),
      screen_coordinate_(coordinate),
      interpolated_depth_(interpolated_depth) {}
Fragment::Fragment(PrimitiveType primitive_type, const Primitive* primitive,
                   const Vector3& view_coordinate, const Vector2& coordinate,
                   const LinearRGB& color, float interpolated_depth)
    : beloging_primitive_type_(primitive_type),
      belonging_primitive_(primitive),
      view_coordinate_(view_coordinate),
      screen_coordinate_(coordinate),
      color_(color),
      interpolated_depth_(interpolated_depth) {}
Fragment& Fragment::operator=(const Fragment& fragment) = default;
Fragment::~Fragment() = default;

const PrimitiveType Fragment::belonging_primitive_type() const {
  return beloging_primitive_type_;
}
const Primitive& Fragment::belonging_primitive() const {
  return *belonging_primitive_;
}
const Vector3& Fragment::view_coordinate() const { return view_coordinate_; }
const Vector2& Fragment::screen_coordinate() const {
  return screen_coordinate_;
}
const LinearRGB& Fragment::color() const { return color_; }
const float Fragment::interpolated_depth() const { return interpolated_depth_; }

Fragment& Fragment::set_belonging_primitive_type(PrimitiveType primitive_type) {
  beloging_primitive_type_ = primitive_type;
  return *this;
}
Fragment& Fragment::set_belonging_primitive(Primitive* primitive) {
  belonging_primitive_ = primitive;
  return *this;
}
Fragment& Fragment::set_view_coordinate(const Vector3& view_coordinate) {
  view_coordinate_ = view_coordinate;
  return *this;
}
Fragment& Fragment::set_screen_coordinate(const Vector2& coordinate) {
  screen_coordinate_ = coordinate;
  return *this;
}
Fragment& Fragment::set_color(const LinearRGB& color) {
  color_ = color;
  return *this;
}
Fragment& Fragment::set_interpolated_depth(float depth) {
  interpolated_depth_ = depth;
  return *this;
}
}  // namespace ho_renderer