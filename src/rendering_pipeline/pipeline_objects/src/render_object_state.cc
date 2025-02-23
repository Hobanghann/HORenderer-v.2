#include "rendering_pipeline/pipeline_objects/include/render_object_state.h"

#include "app/include/debug.h"

namespace ho_renderer {
RenderObjectState::RenderObjectState()
    : object_culling_state_(FrustumCullingResult::kINSIDE) {}
RenderObjectState::RenderObjectState(const RenderObjectState& state) = default;
RenderObjectState& RenderObjectState::operator=(
    const RenderObjectState& state) = default;
RenderObjectState::~RenderObjectState() = default;

FrustumCullingResult RenderObjectState::object_culling_state() const {
  return object_culling_state_;
}

RenderObjectState& RenderObjectState::set_object_culling_state(
    FrustumCullingResult result) {
  object_culling_state_ = result;
  return *this;
}
}  // namespace ho_renderer