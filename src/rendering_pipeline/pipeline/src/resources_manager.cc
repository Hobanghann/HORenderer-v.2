#include "rendering_pipeline/pipeline/include/resources_manager.h"

#include <cassert>
#include <string>

#include "app/include/debug.h"

namespace ho_renderer {
std::vector<Vertex> *ResourcesManager::AllocateVertexBuffer() {
  vertex_buffer_ = new std::vector<Vertex>();
  return vertex_buffer_;
}
std::vector<std::uint32_t> *ResourcesManager::AllocateIndexBuffer() {
  index_buffer_ = new std::vector<std::uint32_t>();
  return index_buffer_;
}
std::vector<Vector3> *ResourcesManager::AllocateCoordinateBuffer() {
  coordinate_buffer_ = new std::vector<Vector3>();
  return coordinate_buffer_;
}
std::vector<Primitive *> *ResourcesManager::AllocatePrimitiveBuffer() {
  primitive_buffer_ = new std::vector<Primitive *>();
  return primitive_buffer_;
}
std::vector<Fragment> *ResourcesManager::AllocateFragmentBuffer() {
  fragment_buffer_ = new std::vector<Fragment>();
  return fragment_buffer_;
}
std::vector<std::uint32_t> *ResourcesManager::AllocateColorBuffer() {
  color_buffer_ = new std::vector<std::uint32_t>();
  return color_buffer_;
}
RenderObjectState *ResourcesManager::AllocateRenderObjectState() {
  render_object_state_ = new RenderObjectState();
  return render_object_state_;
}

void ResourcesManager::DeallocateVertexBuffer() {
  delete vertex_buffer_;
  vertex_buffer_ = nullptr;
}
void ResourcesManager::DeallocateIndexBuffer() {
  delete index_buffer_;
  index_buffer_ = nullptr;
}
void ResourcesManager::DeallocateCoordinateBuffer() {
  delete coordinate_buffer_;
  coordinate_buffer_ = nullptr;
}
void ResourcesManager::DeallocatePrimitiveBuffer() {
  for (auto itr = primitive_buffer_->begin(); itr != primitive_buffer_->end();
       itr++) {
    delete *itr;
  }
  delete primitive_buffer_;
  primitive_buffer_ = nullptr;
}
void ResourcesManager::DeallocateFragmentBuffer() {
  delete fragment_buffer_;
  fragment_buffer_ = nullptr;
}
void ResourcesManager::DeallocateColorBuffer() {
  delete color_buffer_;
  color_buffer_ = nullptr;
}
void ResourcesManager::DeallocateRenderObjectState() {
  delete render_object_state_;
  render_object_state_ = nullptr;
}

void ResourcesManager::DeallocateAll() {
  DeallocateVertexBuffer();
  DeallocateIndexBuffer();
  DeallocateCoordinateBuffer();
  DeallocatePrimitiveBuffer();
  DeallocateFragmentBuffer();
  DeallocateColorBuffer();
  DeallocateRenderObjectState();
}

std::vector<Vertex> *ResourcesManager::vertex_buffer_ = nullptr;
std::vector<std::uint32_t> *ResourcesManager::index_buffer_ = nullptr;
std::vector<Vector3> *ResourcesManager::coordinate_buffer_ = nullptr;
std::vector<Primitive *> *ResourcesManager::primitive_buffer_ = nullptr;
std::vector<Fragment> *ResourcesManager::fragment_buffer_ = nullptr;
std::vector<std::uint32_t> *ResourcesManager::color_buffer_ = nullptr;
RenderObjectState *ResourcesManager::render_object_state_ = nullptr;
}  // namespace ho_renderer