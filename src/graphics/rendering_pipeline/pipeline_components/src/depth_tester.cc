#include "graphics/rendering_pipeline/pipeline_components/include/depth_tester.h"

#include "graphics/rendering_pipeline/pipeline_objects/include/depth_buffer.h"

namespace ho_renderer {
DepthTestingShader::DepthTestingShader() = default;
DepthTestingShader::~DepthTestingShader() = default;

bool DepthTestingShader::IsDeeper(const Fragment& fragment,
                                  const DepthBuffer& depth_buffer) const {
  return depth_buffer.GetDepth(fragment.screen_coord().x(),
                               fragment.screen_coord().y()) < fragment.depth();
}
bool DepthTestingShader::IsShallower(const Fragment& fragment,
                                     const DepthBuffer& depth_buffer) const {
  return depth_buffer.GetDepth(fragment.screen_coord().x(),
                               fragment.screen_coord().y()) > fragment.depth();
}
}  // namespace ho_renderer
