#ifndef _HORENDERER_VERTEX_SPECIFYER_H_
#define _HORENDERER_VERTEX_SPECIFYER_H_

#include <cstdint>
#include <vector>

#include "graphics/rendering_pipeline/pipeline_objects/include/transformed_vertex.h"
#include "graphics/resource/include/mesh.h"

namespace ho_renderer {
class VertexSpecifier {
 public:
  VertexSpecifier();
  VertexSpecifier(const VertexSpecifier&) = delete;
  VertexSpecifier& operator=(const VertexSpecifier&) = delete;
  ~VertexSpecifier();

  std::vector<TransformedVertex>* ReadVertices(
      std::vector<TransformedVertex>* output_buffer, const Mesh* mesh) const;
  const std::vector<std::uint32_t>& ReadIndices(const Mesh* mesh) const;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_VERTEX_SPECIFYIER_H_