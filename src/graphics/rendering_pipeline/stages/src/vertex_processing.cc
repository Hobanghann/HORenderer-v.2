#include "graphics/rendering_pipeline/stages/include/vertex_processing.h"

#include <memory>
#include <vector>

#include "core/math/include/affine_transform.h"
#include "graphics/rendering_pipeline/pipeline_components/include/vertex_shader.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/transformed_vertex.h"
#include "tools/include/debug.h"

namespace ho_renderer {
VertexProcessing::VertexProcessing() = default;
VertexProcessing::~VertexProcessing() = default;

void VertexProcessing::TransformVertices(
    std::vector<TransformedVertex>* v_buffer,
    const AffineTransform& m_transform, const AffineTransform& v_transform,
    const AffineTransform& p_transform) const {
  ASSERT_MSG(
      v_buffer != nullptr,
      "VertexProcessing::TransformVertices Error : vertex buffer is null");
  if (v_buffer == nullptr) {
    return;
  }
  AffineTransform mv_transform = m_transform.GetComposeWith(v_transform);
  for (TransformedVertex& vertex : *v_buffer) {
    vertex_shader_.TransformLocalPositionToView(vertex, mv_transform);
    vertex_shader_.TransformViewPositionToProjection(vertex, p_transform);
    vertex_shader_.TransformLocalNormal(vertex, mv_transform);
    vertex_shader_.TransformLocalTangent(vertex, mv_transform);
  }
}
}  // namespace ho_renderer