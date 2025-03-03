#include "rendering_pipeline/shaders/include/vertex_specifying_shader.h"

#include "app/include/debug.h"
#include "rendering_pipeline/pipeline/include/resources_manager.h"

namespace ho_renderer {
VertexSpecifyingShader::VertexSpecifyingShader() = default;
VertexSpecifyingShader::~VertexSpecifyingShader() = default;

std::vector<Vertex>* VertexSpecifyingShader::ReadVertexBuffer(
    const GameObject& game_object) const {
  std::vector<Vertex>* vertex_stream = ResourcesManager::GetClearVertexBuffer();
  *vertex_stream = game_object.mesh().vertex_buffer();
  return vertex_stream;
}
std::vector<uint32_t>* VertexSpecifyingShader::ReadIndexBuffer(
    const GameObject& game_object) const {
  std::vector<std::uint32_t>* index_stream =
      ResourcesManager::GetClearIndexBuffer();
  *index_stream = game_object.mesh().index_buffer();
  return index_stream;
}
}  // namespace ho_renderer