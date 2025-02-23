#include "rendering_pipeline/stages/include/vertex_specification.h"

#include "app/include/debug.h"

namespace ho_renderer {

VertexSpecification::VertexSpecification()
    : vertex_specifying_shader_(new VertexSpecifyingShader()) {}
VertexSpecification::~VertexSpecification() = default;

VertexSpecification& VertexSpecification::SetInputGameObject(
    const GameObject* game_object) {
  input_game_object_ = game_object;
  return *this;
}

VertexSpecification& VertexSpecification::ResetInputs() {
  input_game_object_ = nullptr;
  return *this;
}

std::vector<Vertex>* VertexSpecification::GetOutputVertexBuffer() {
  if (output_vertex_buffer_ == nullptr) {
#ifdef DEBUG
    DEBUG_MSG("output_vertex_buffer is null.")
    assert(false);
#endif
  }
  return output_vertex_buffer_;
}
std::vector<uint32_t>* VertexSpecification::GetOutputIndexBuffer() {
  if (output_index_buffer_ == nullptr) {
#ifdef DEBUG
    DEBUG_MSG("output_index_buffer_ is null.")
    assert(false);
#endif
  }
  return output_index_buffer_;
}

VertexSpecification& VertexSpecification::ResetOutputs() {
  output_vertex_buffer_ = nullptr;
  output_index_buffer_ = nullptr;
  return *this;
}

void VertexSpecification::ReadBuffer() {
  if (input_game_object_ == nullptr) {
#ifdef DEBUG
    DEBUG_MSG("input_game_object_ is null.")
    assert(false);
#endif
  }
  output_vertex_buffer_ =
      vertex_specifying_shader_->ReadVertexBuffer(*input_game_object_);
  output_index_buffer_ =
      vertex_specifying_shader_->ReadIndexBuffer(*input_game_object_);
}
}  // namespace ho_renderer