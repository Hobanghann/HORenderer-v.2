#ifndef _HORENDERER_RENDERINGPIPELINE_SHADERS_DEPTH_TESTING_SHADER_H_
#define _HORENDERER_RENDERINGPIPELINE_SHADERS_DEPTH_TESTING_SHADER_H_

#include "rendering_pipeline/pipeline_objects/include/depth_buffer.h"
#include "rendering_pipeline/pipeline_objects/include/fragment.h"

namespace ho_renderer {
class DepthTestingShader {
 public:
  DepthTestingShader();
  DepthTestingShader(const DepthTestingShader&) = delete;
  DepthTestingShader& operator=(const DepthTestingShader&) = delete;
  ~DepthTestingShader();

  bool IsDeeper(const Fragment& fragment,
                const DepthBuffer& depth_buffer) const;
  bool IsShallower(const Fragment& fragment,
                   const DepthBuffer& depth_buffer) const;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_RENDERINGPIPELINE_SHADERS_DEPTH_TESTING_SHADER_H_