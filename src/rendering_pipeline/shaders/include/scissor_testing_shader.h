#ifndef _HORENDERER_RENDERINGPIPELINE_SHADERS_SCISSOR_TESTING_SHADER_H_
#define _HORENDERER_RENDERINGPIPELINE_SHADERS_SCISSOR_TESTING_SHADER_H_

#include "rendering_pipeline/pipeline_objects/include/fragment.h"

namespace ho_renderer {
class ScissorTestingShader {
 public:
  ScissorTestingShader();
  ScissorTestingShader(const ScissorTestingShader&) = delete;
  ScissorTestingShader& operator=(const ScissorTestingShader&) = delete;
  ~ScissorTestingShader();

  bool IsInFrame(const Fragment& fragment, int screen_width, int screen_height);
};
}  // namespace ho_renderer

#endif  // _HORENDERER_RENDERINGPIPELINE_SHADERS_SCISSOR_TESTING_SHADER_H_