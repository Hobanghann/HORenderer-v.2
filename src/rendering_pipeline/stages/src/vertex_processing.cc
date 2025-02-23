#include "rendering_pipeline/stages/include/vertex_processing.h"

#include <cassert>

#include "app/include/debug.h"
#include "asset/include/vertex.h"
#include "rendering_pipeline/shaders/include/vertex_shader.h"

namespace ho_renderer {
VertexProcessing::VertexProcessing() : vertex_shader_(new VertexShader()) {}
VertexProcessing::~VertexProcessing() = default;

VertexProcessing& VertexProcessing::SetInputVertexBuffer(
    std::vector<Vertex>* vertex_buffer) {
  input_vertex_buffer_ = vertex_buffer;
  return *this;
}
VertexProcessing& VertexProcessing::SetInputTransform(
    AffineTransform* transform) {
  input_transform_ = transform;
  return *this;
}

VertexProcessing& VertexProcessing::ResetInputs() {
  input_vertex_buffer_ = nullptr;
  input_transform_ = nullptr;
  return *this;
}

std::vector<Vertex>* VertexProcessing::GetOutputVertexBuffer() {
  if (output_vertex_buffer_ == nullptr) {
#ifdef DEBUG
    DEBUG_MSG("output_vertex_buffer_ is null.")
    assert(false);
#endif
  }
  return output_vertex_buffer_;
}

VertexProcessing& VertexProcessing::ResetOutputs() {
  output_vertex_buffer_ = nullptr;
  return *this;
}

void ho_renderer::VertexProcessing::Process() {
  if (input_vertex_buffer_ == nullptr) {
#ifdef DEBUG
    DEBUG_MSG("input_vertex_buffer_ is null.")
    assert(false);
#endif
  }
  if (input_transform_ == nullptr) {
#ifdef DEBUG
    DEBUG_MSG("input_transform_ is null.")
    assert(false);
#endif
  }
  for (auto vertex_itr = input_vertex_buffer_->begin();
       vertex_itr != input_vertex_buffer_->end(); vertex_itr++) {
    vertex_shader_->TransformCoordinate(*vertex_itr, *input_transform_);
  }
  output_vertex_buffer_ = input_vertex_buffer_;
}
}  // namespace ho_renderer