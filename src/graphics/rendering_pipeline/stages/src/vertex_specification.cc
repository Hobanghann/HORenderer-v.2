#include "graphics/rendering_pipeline/stages/include/vertex_specification.h"

#include "tools/include/debug.h"
namespace ho_renderer {

VertexSpecification::VertexSpecification() = default;
VertexSpecification::~VertexSpecification() = default;

std::vector<TransformedVertex>* VertexSpecification::ReadVertices(
    std::vector<TransformedVertex>* output_buffer, const Mesh* mesh) const {
  ASSERT_MSG(
      output_buffer != nullptr,
      "VertexSpecification::ReadVertices Error : output vertex buffer is null");
  ASSERT_MSG(mesh != nullptr,
             "VertexSpecification::ReadVertices Error : mesh is null");
  if (output_buffer == nullptr || mesh == nullptr) {
    return output_buffer;
  }
  return vertex_specifier_.ReadVertices(output_buffer, mesh);
}
const std::vector<std::uint32_t>& VertexSpecification::ReadIndices(
    const Mesh* mesh) const {
  ASSERT_MSG(mesh != nullptr,
             "VertexSpecification::ReadIndices Error : mesh is null");
  if (mesh == nullptr) {
    return std::vector<std::uint32_t>();
  }
  return vertex_specifier_.ReadIndices(mesh);
}
}  // namespace ho_renderer