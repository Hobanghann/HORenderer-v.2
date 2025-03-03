#ifndef _HORENDERER_RENDERINGPIPELINE_PIPELINEOBJECTS_FRAGMENT_H_
#define _HORENDERER_RENDERINGPIPELINE_PIPELINEOBJECTS_FRAGMENT_H_

// Fragment is data unit that cover one primitive_type.
// So one primitive_type is formed by multiple fragment.
// Fragment is attributed to interpolated attribute from vertices taht define
// primitive_type.

#include "engine/color/include/linear_rgb.h"
#include "math/include/vector2.h"
#include "math/include/vector3.h"
#include "rendering_pipeline/pipeline/include/pipeline_settings.h"
#include "rendering_pipeline/pipeline_objects/include/primitive.h"

namespace ho_renderer {
class Fragment {
 public:
  Fragment();
  Fragment(const Fragment& fragment);
  Fragment(PrimitiveType primitive_type, const Primitive* primitive,
           const Vector3& view_coordinate, const Vector2& pixel,
           float interpolated_depth);
  Fragment(PrimitiveType primitive_type, const Primitive* primitive,
           const Vector3& view_coordinate, const Vector2& pixel,
           const LinearRGB& color, float interpolated_depth);
  Fragment& operator=(const Fragment& fragment);
  ~Fragment();

  const PrimitiveType belonging_primitive_type() const;
  const Primitive& belonging_primitive() const;
  const Vector3& view_coordinate() const;
  const Vector2& screen_coordinate() const;
  const LinearRGB& color() const;
  const float interpolated_depth() const;

  Fragment& set_belonging_primitive_type(PrimitiveType primitive_type);
  Fragment& set_belonging_primitive(Primitive* primitive);
  Fragment& set_view_coordinate(const Vector3& view_coordinate);
  Fragment& set_screen_coordinate(const Vector2& pixel);
  Fragment& set_color(const LinearRGB& color);
  Fragment& set_interpolated_depth(float depth);

 private:
  PrimitiveType beloging_primitive_type_;
  const Primitive* belonging_primitive_;
  Vector2 screen_coordinate_;
  LinearRGB color_;
  Vector3 view_coordinate_;
  float interpolated_depth_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_RENDERINGPIPELINE_PIPELINEOBJECTS_FRAGMENT_H_