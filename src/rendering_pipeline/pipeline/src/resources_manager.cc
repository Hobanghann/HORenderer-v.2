#include "rendering_pipeline/pipeline/include/resources_manager.h"

#include <cassert>
#include <string>

#include "app/include/debug.h"

namespace ho_renderer {
std::vector<Vertex> *ResourcesManager::GetClearVertexBuffer() {
  vertex_buffer_->clear();
  return vertex_buffer_.get();
}
std::vector<std::uint32_t> *ResourcesManager::GetClearIndexBuffer() {
  index_buffer_->clear();
  return index_buffer_.get();
}
std::vector<Vector3> *ResourcesManager::GetClearViewCoordinateBuffer() {
  view_coordinate_buffer_->clear();
  return view_coordinate_buffer_.get();
}
std::vector<Vector3> *ResourcesManager::GetClearNDCBuffer() {
  ndc_buffer_->clear();
  return ndc_buffer_.get();
}
std::vector<Vector3> *ResourcesManager::GetClearViewportNDCBuffer() {
  viewport_ndc_buffer_->clear();
  return viewport_ndc_buffer_.get();
}
std::vector<Primitive *> *ResourcesManager::GetClearPrimitiveBuffer() {
  primitive_buffer_->clear();
  return primitive_buffer_.get();
}
std::vector<Fragment> *ResourcesManager::GetClearFragmentBuffer() {
  fragment_buffer_->clear();
  return fragment_buffer_.get();
}
std::vector<LinearRGB> *ResourcesManager::GetClearColorBuffer() {
  color_buffer_->clear();
  return color_buffer_.get();
}
RenderObjectState *ResourcesManager::GetClearRenderObjectState() {
  render_object_state_->set_object_culling_state(kINSIDE);
  return render_object_state_.get();
}

std::unique_ptr<std::vector<Vertex>> ResourcesManager::vertex_buffer_(
    new std::vector<Vertex>());
std::unique_ptr<std::vector<std::uint32_t>> ResourcesManager::index_buffer_(
    new std::vector<std::uint32_t>());
std::unique_ptr<std::vector<Vector3>> ResourcesManager::view_coordinate_buffer_(
    new std::vector<Vector3>());
std::unique_ptr<std::vector<Vector3>> ResourcesManager::ndc_buffer_(
    new std::vector<Vector3>());
std::unique_ptr<std::vector<Vector3>> ResourcesManager::viewport_ndc_buffer_(
    new std::vector<Vector3>());
std::unique_ptr<std::vector<Primitive *>> ResourcesManager::primitive_buffer_(
    new std::vector<Primitive *>());
std::unique_ptr<std::vector<Fragment>> ResourcesManager::fragment_buffer_(
    new std::vector<Fragment>());
std::unique_ptr<std::vector<LinearRGB>> ResourcesManager::color_buffer_(
    new std::vector<LinearRGB>());
std::unique_ptr<RenderObjectState> ResourcesManager::render_object_state_(
    new RenderObjectState());
}  // namespace ho_renderer