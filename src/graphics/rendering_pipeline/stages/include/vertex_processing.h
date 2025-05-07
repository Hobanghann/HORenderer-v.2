#ifndef _HORENDERER_VERTEX_PROCESSING_H_
#define _HORENDERER_VERTEX_PROCESSING_H_

// Responsibility : Define how vertex shader process on vertices

#include <memory>
#include <vector>

#include "core/math/include/affine_transform.h"
#include "graphics/rendering_pipeline/pipeline_components/include/vertex_shader.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/transformed_vertex.h"

namespace ho_renderer {
class VertexProcessing {
 public:
  VertexProcessing();
  VertexProcessing(const VertexProcessing& stage) = delete;
  VertexProcessing& operator=(const VertexProcessing& stage) = delete;
  ~VertexProcessing();

  void TransformVertices(std::vector<TransformedVertex>* v_buffer,
                         const AffineTransform& m_transform,
                         const AffineTransform& v_transform,
                         const AffineTransform& p_transform) const;

 private:
  VertexShader vertex_shader_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_VERTEX_PROCESSING_H_