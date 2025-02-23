#include "rendering_pipeline/shaders/include/depth_testing_shader.h"

#include "app/include/debug.h"
#include "rendering_pipeline/pipeline_objects/include/depth_buffer.h"

namespace ho_renderer {
DepthTestingShader::DepthTestingShader() = default;
DepthTestingShader::~DepthTestingShader() = default;

bool DepthTestingShader::IsDeeper(const Fragment& fragment,
                                  const DepthBuffer& depth_buffer) const {
  return depth_buffer.GetDepth(fragment.screen_coordinate().x(),
                               fragment.screen_coordinate().y()) <
         fragment.interpolated_depth();
}
bool DepthTestingShader::IsShallower(const Fragment& fragment,
                                     const DepthBuffer& depth_buffer) const {
  return depth_buffer.GetDepth(fragment.screen_coordinate().x(),
                               fragment.screen_coordinate().y()) >
         fragment.interpolated_depth();
}
}  // namespace ho_renderer
