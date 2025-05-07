#include "graphics/rendering_pipeline/system/include/pipeline_resources_manager.h"

#include <cassert>
#include <string>

namespace ho_renderer {
PipelineResourcesManager::PipelineResourcesManager() = default;
PipelineResourcesManager::~PipelineResourcesManager() = default;
std::vector<TransformedVertex> *
PipelineResourcesManager::GetClearVertexBuffer() {
  return GetClearBuffer(vertex_buffers_, vertex_buffer_used_);
}
std::vector<std::unique_ptr<Primitive>> *
PipelineResourcesManager::GetClearPrimitiveBuffer() {
  return GetClearBuffer(primitive_buffers_, primitive_buffer_used_);
}
std::vector<Fragment> *PipelineResourcesManager::GetClearFragmentBuffer() {
  return GetClearBuffer(fragment_buffers_, fragment_buffer_used_);
}

PipelineResourcesManager &PipelineResourcesManager::ReturnVertexBuffer(
    std::vector<TransformedVertex> *buffer) {
  ReturnBuffer(vertex_buffers_, vertex_buffer_used_, buffer);
  return *this;
}
PipelineResourcesManager &PipelineResourcesManager::ReturnPrimitiveBuffer(
    std::vector<std::unique_ptr<Primitive>> *buffer) {
  ReturnBuffer(primitive_buffers_, primitive_buffer_used_, buffer);
  return *this;
}
PipelineResourcesManager &PipelineResourcesManager::ReturnFragmentBuffer(
    std::vector<Fragment> *buffer) {
  ReturnBuffer(fragment_buffers_, fragment_buffer_used_, buffer);
  return *this;
}

template <typename T>
std::vector<T> *PipelineResourcesManager::GetClearBuffer(
    std::vector<std::unique_ptr<std::vector<T>>> &buffers,
    std::vector<bool> &usage_flags) {
  for (size_t i = 0; i < usage_flags.size(); ++i) {
    if (!usage_flags[i]) {
      usage_flags[i] = true;
      return buffers[i].get();
    }
  }
  auto *new_buffer = new std::vector<T>();
  buffers.emplace_back(new_buffer);
  usage_flags.push_back(true);
  return new_buffer;
}

template <typename T>
PipelineResourcesManager &PipelineResourcesManager::ReturnBuffer(
    std::vector<std::unique_ptr<std::vector<T>>> &buffers,
    std::vector<bool> &usage_flags, std::vector<T> *buffer) {
  for (size_t i = 0; i < buffers.size(); ++i) {
    if (buffers[i].get() == buffer) {
      buffer->clear();
      usage_flags[i] = false;
      return *this;
    }
  }
  // exception : Returned buffer not found in manager
  return *this;
}
}  // namespace ho_renderer