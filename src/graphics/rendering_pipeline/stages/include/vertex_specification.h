#ifndef _HORENDERER_VERTEX_SPECIFICATION_H_
#define _HORENDERER_VERTEX_SPECIFICATION_H_

#include <vector>

#include "graphics/rendering_pipeline/pipeline_components/include/vertex_specifier.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/transformed_vertex.h"
#include "graphics/resource/include/aab_bounding_volume.h"
#include "graphics/resource/include/model_node.h"
#include "graphics/resource/include/sphere_bounding_volume.h"

namespace ho_renderer {
class VertexSpecification {
 public:
  VertexSpecification();
  VertexSpecification(const VertexSpecification&) = delete;
  VertexSpecification& operator=(const VertexSpecification&) = delete;
  ~VertexSpecification();

  std::vector<TransformedVertex>* ReadVertices(
      std::vector<TransformedVertex>* output_buffer, const Mesh* mesh) const;
  const std::vector<std::uint32_t>& ReadIndices(const Mesh* mesh) const;

 private:
  VertexSpecifier vertex_specifier_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_VERTEX_SPECIFICATION_H_