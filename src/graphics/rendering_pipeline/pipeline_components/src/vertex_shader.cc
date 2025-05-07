#include "graphics/rendering_pipeline/pipeline_components/include/vertex_shader.h"

#include "core/math/include/affine_transform.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/transformed_vertex.h"

namespace ho_renderer {
VertexShader::VertexShader() = default;
VertexShader::~VertexShader() = default;

TransformedVertex& VertexShader::TransformLocalPositionToView(
    TransformedVertex& v, const AffineTransform& transform) const {
  v.set_view_coord(
      transform.Transform(v.source_vertex()->position()).ToVector3());
  return v;
}
TransformedVertex& VertexShader::TransformLocalPositionToProjection(
    TransformedVertex& v, const AffineTransform& transform) const {
  v.set_clip_coord(transform.Transform(v.source_vertex()->position()));
  return v;
}
TransformedVertex& VertexShader::TransformViewPositionToProjection(
    TransformedVertex& v, const AffineTransform& transform) const {
  v.set_clip_coord(
      transform.Transform(v.view_coord().ToHomogeneousCoordinate()));
  return v;
}
TransformedVertex& VertexShader::TransformLocalNormal(
    TransformedVertex& v, const AffineTransform& transform) const {
  v.set_normal_vector(
      transform.Transform(Vector4(v.source_vertex()->normal_vector()))
          .ToVector3().GetNormalized());
  return v;
}
TransformedVertex& VertexShader::TransformLocalTangent(
    TransformedVertex& v, const AffineTransform& transform) const {
  v.set_tangent_vector(
      transform.Transform(Vector4(v.source_vertex()->normal_vector()))
          .ToVector3().GetNormalized());
  return v;
}
}  // namespace ho_renderer