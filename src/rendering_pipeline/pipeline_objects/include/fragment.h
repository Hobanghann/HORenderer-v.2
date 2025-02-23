#ifndef _HORENDERER_RENDERINGPIPELINE_PIPELINEOBJECTS_FRAGMENT_H_
#define _HORENDERER_RENDERINGPIPELINE_PIPELINEOBJECTS_FRAGMENT_H_

// Fragment is data unit that cover one primitive_type.
// So one primitive_type is formed by multiple fragment.
// Fragment is attributed to interpolated attribute from vertices taht define
// primitive_type.

#include <cstdint>

#include "math/include/vector2.h"
#include "rendering_pipeline/pipeline/include/pipeline_settings.h"
#include "rendering_pipeline/pipeline_objects/include/primitive.h"

namespace ho_renderer {
class Fragment {
 public:
  Fragment();
  Fragment(const Fragment& fragment);
  Fragment(PrimitiveType primitive_type, const Primitive* primitive,
           const Vector2& coordinate, float interpolated_depth);
  Fragment(PrimitiveType primitive_type, const Primitive* primitive,
           const Vector2& coordinate, std::uint32_t color_bit,
           float interpolated_depth);
  Fragment& operator=(const Fragment& fragment);
  ~Fragment();

  const PrimitiveType belonging_primitive_type() const;
  const Primitive& belonging_primitive() const;
  const Vector2& screen_coordinate() const;
  const std::uint32_t color_bit() const;
  const float interpolated_depth() const;

  Fragment& set_belonging_primitive_type(PrimitiveType primitive_type);
  Fragment& set_belonging_primitive(Primitive* primitive);
  Fragment& set_screen_coordinate(const Vector2& coordinate);
  Fragment& set_color_bit(std::uint32_t color_bit);
  Fragment& set_interpolated_depth(float depth);

 private:
  PrimitiveType beloging_primitive_type_;
  const Primitive* belonging_primitive_;
  Vector2 screen_coordinate_;
  std::uint32_t color_bit_;
  float interpolated_depth_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_RENDERINGPIPELINE_PIPELINEOBJECTS_FRAGMENT_H_