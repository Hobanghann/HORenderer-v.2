#ifndef _HORENDERER_FRAGMENT_H_
#define _HORENDERER_FRAGMENT_H_

// Fragment is data unit that cover one primitive_type.
// So one primitive_type is formed by multiple fragment.
// Fragment is attributed to interpolated attribute from vertices taht define
// primitive_type.

#include "core/math/include/vector2.h"
#include "core/math/include/vector3.h"
#include "graphics/color/include/linear_rgb.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/primitive.h"
#include "graphics/rendering_pipeline/system/include/pipeline_enum.h"

namespace ho_renderer {
class primitive;
class Fragment {
 public:
  Fragment() = delete;
  Fragment(const Fragment& fragment);
  Fragment(const Primitive* source, const Vector2& screen_coord,
           const Vector3& view_coord, const Vector3& uv,
           const Vector3& frag_normal, const Vector3& tangent, float handedness,
           float depth);
  Fragment& operator=(const Fragment& fragment);
  ~Fragment();

  const Primitive* source() const;
  const Vector2& screen_coord() const;
  const Vector3& view_coord() const;
  const Vector3& uv_coord() const;
  const Vector3& fragment_normal() const;
  const Vector3& tangent() const;
  float handedness() const;
  float depth() const;
  const LinearRGB& color() const;
  const LinearRGB& surface_color_cache() const;
  float point_light_intensity_cache() const;
  const Vector3& frag_to_light_cache() const;

  Fragment& set_color(const LinearRGB& color);
  Fragment& set_surface_color_cache(const LinearRGB& color);
  Fragment& set_point_light_intensity_cache(float intensity);
  Fragment& set_frag_to_light_cache(const Vector3& vec);

 private:
  const Primitive* source_;
  Vector2 screen_coord_;
  Vector3 view_coord_;  // view_coord is used in lighting
  Vector3 uv_coord_;
  Vector3 fragment_normal_;  // used for smooth shading
  Vector3 tangent_;
  float handedness_;
  float depth_;
  LinearRGB color_;
  LinearRGB surface_color_cache_;
  float point_light_intensity_cache_;
  Vector3 frag_to_light_cache_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_FRAGMENT_H_