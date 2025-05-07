#ifndef _HORENDERER_VERTEX_SHADER_H_
#define _HORENDERER_VERTEX_SHADER_H_

// Responsibility : Transform attributes vertex has.

#include "core/math/include/affine_transform.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/transformed_vertex.h"

namespace ho_renderer {
class VertexShader {
 public:
  VertexShader();
  VertexShader(const VertexShader&) = delete;
  VertexShader& operator=(const VertexShader&) = delete;
  ~VertexShader();

  TransformedVertex& TransformLocalPositionToView(
      TransformedVertex& v, const AffineTransform& transform) const;
  TransformedVertex& TransformLocalPositionToProjection(
      TransformedVertex& v, const AffineTransform& transform) const;
  TransformedVertex& TransformViewPositionToProjection(
      TransformedVertex& v, const AffineTransform& transform) const;
  TransformedVertex& TransformLocalNormal(
      TransformedVertex& v, const AffineTransform& transform) const;
  TransformedVertex& TransformLocalTangent(
      TransformedVertex& v, const AffineTransform& transform) const;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_VERTEX_SHADER_H_