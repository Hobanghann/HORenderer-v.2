#include "graphics/rendering_pipeline/stages/include/vertex_specification.h"

namespace ho_renderer {

VertexSpecification::VertexSpecification() = default;
VertexSpecification::~VertexSpecification() = default;

std::vector<TransformedVertex>* VertexSpecification::ReadVertices(
    std::vector<TransformedVertex>* output_buffer,
    const Mesh *mesh) const {
  return vertex_specifier_.ReadVertices(output_buffer, mesh);
}
const std::vector<std::uint32_t>& VertexSpecification::ReadIndices(
    const Mesh* mesh) const {
  return vertex_specifier_.ReadIndices(mesh);
}
}  // namespace ho_renderer