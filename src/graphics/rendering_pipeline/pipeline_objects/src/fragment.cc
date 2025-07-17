#include "graphics/rendering_pipeline/pipeline_objects/include/fragment.h"

#include "core/math/include/vector2.h"
#include "core/math/include/vector3.h"
#include "graphics/color/include/linear_rgb.h"
#include "graphics/rendering_pipeline/system/include/pipeline_enum.h"
#include "tools/include/debug.h"

namespace ho_renderer {
Fragment::Fragment(const Fragment& fragment) = default;
Fragment::Fragment(const Primitive* source, const Vector2& screen_coord,
                   const Vector3& view_coord, const Vector3& uv,
                   const Vector3& frag_normal, const Vector3& tangent,
                   float handedness, float depth)
    : source_(source),
      screen_coord_(screen_coord),
      view_coord_(view_coord),
      uv_coord_(uv),
      fragment_normal_(frag_normal),
      tangent_(tangent),
      handedness_(handedness),
      depth_(depth),
      color_(LinearRGB::kBlack) {
  ASSERT_MSG(source_ != nullptr,
             "Fragment::Fragment Error : source primitive is null");
}
Fragment& Fragment::operator=(const Fragment& fragment) = default;
Fragment::~Fragment() = default;

const Primitive* Fragment::source() const { return source_; }
const Vector2& Fragment::screen_coord() const { return screen_coord_; }
const Vector3& Fragment::view_coord() const { return view_coord_; }
const Vector3& Fragment::uv_coord() const { return uv_coord_; }
const Vector3& Fragment::fragment_normal() const { return fragment_normal_; }
const Vector3& Fragment::tangent() const { return tangent_; }
float Fragment::handedness() const { return handedness_; }
float Fragment::depth() const { return depth_; }
const LinearRGB& Fragment::color() const { return color_; }
const LinearRGB& Fragment::surface_color_cache() const {
  return surface_color_cache_;
}
float Fragment::point_light_intensity_cache() const {
  return point_light_intensity_cache_;
}
const Vector3& Fragment::frag_to_light_cache() const {
  return frag_to_light_cache_;
}

Fragment& Fragment::set_color(const LinearRGB& color) {
  color_ = color;
  return *this;
}
Fragment& Fragment::set_surface_color_cache(const LinearRGB& color) {
  surface_color_cache_ = color;
  return *this;
}
Fragment& Fragment::set_point_light_intensity_cache(float intensity) {
  point_light_intensity_cache_ = intensity;
  return *this;
}
Fragment& Fragment::set_frag_to_light_cache(const Vector3& vec) {
  frag_to_light_cache_ = vec;
  return *this;
}
}  // namespace ho_renderer