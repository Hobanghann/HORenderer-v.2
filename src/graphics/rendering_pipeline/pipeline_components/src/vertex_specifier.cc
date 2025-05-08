#include "graphics/rendering_pipeline/pipeline_components/include/vertex_specifier.h"

#include <cstdint>
#include <vector>

#include "graphics/resource/include/vertex.h"
#include "tools/include/debug.h"

namespace ho_renderer {
VertexSpecifier::VertexSpecifier() = default;
VertexSpecifier::~VertexSpecifier() = default;

std::vector<TransformedVertex>* VertexSpecifier::ReadVertices(
    std::vector<TransformedVertex>* output_buffer, const Mesh* mesh) const {
  ASSERT_MSG(output_buffer != nullptr,
             "VertexSpecifier::ReadVertices Error : output buffer is null");
  ASSERT_MSG(mesh != nullptr,
             "VertexSpecifier::ReadVertices Error : mesh is null");
  if (output_buffer == nullptr || mesh == nullptr) {
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
  ASSERT_MSG(mesh != nullptr,
             "VertexSpecifier::ReadIndices Error : mesh is null");
  return mesh->indices();
}
}  // namespace ho_renderer