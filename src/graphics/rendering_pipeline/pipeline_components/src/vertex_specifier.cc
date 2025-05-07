#include "graphics/rendering_pipeline/pipeline_components/include/vertex_specifier.h"

#include <cstdint>
#include <vector>

#include "graphics/resource/include/vertex.h"

namespace ho_renderer {
VertexSpecifier::VertexSpecifier() = default;
VertexSpecifier::~VertexSpecifier() = default;

std::vector<TransformedVertex>* VertexSpecifier::ReadVertices(
    std::vector<TransformedVertex>* output_buffer, const Mesh* mesh) const {
  if (output_buffer == nullptr) {
    return nullptr;
  }
  const std::vector<Vertex>& vertices = mesh->vertices();
  for (auto itr = vertices.begin(); itr != vertices.end(); itr++) {
    output_buffer->emplace_back(&*itr);
  }
  return output_buffer;
}
const std::vector<std::uint32_t>& VertexSpecifier::ReadIndices(
    const Mesh* mesh) const {
  return mesh->indices();
}
}  // namespace ho_renderer