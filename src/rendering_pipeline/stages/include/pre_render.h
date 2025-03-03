#ifndef _HORENDERER_RENDERINGPIPELINE_STAGES_PRE_RENDER_H_
#define _HORENDERER_RENDERINGPIPELINE_STAGES_PRE_RENDER_H_

#include <vector>

#include "engine/light/include/ambient_light.h"
#include "engine/light/include/directional_light.h"
#include "engine/light/include/point_light.h"
#include "math/include/affine_transform.h"
#include "rendering_pipeline/pipeline_objects/include/frame_buffer.h"

namespace ho_renderer {
class PreRenderStage {
 public:
  PreRenderStage();
  PreRenderStage(const PreRenderStage& stage) = delete;
  PreRenderStage& operator=(const PreRenderStage&) = delete;
  ~PreRenderStage();

  PreRenderStage& SetInputFrameBuffer(FrameBuffer* frame_buffer);
  PreRenderStage& SetInputTransform(AffineTransform* transform);
  PreRenderStage& SetInputAmbientLight(AmbientLight* light);
  PreRenderStage& SetInputDirectionalLight(DirectionalLight* light);
  PreRenderStage& SetInputPointLight(PointLight* light);

  PreRenderStage& ResetInputs();

  PreRenderStage& ResetOutputs();

  void PreRender();

 private:
  // inputs
  FrameBuffer* input_frame_buffer_;
  AffineTransform* input_transform_;
  AmbientLight* input_ambient_light_;
  DirectionalLight* input_directional_light_;
  std::vector<PointLight*> input_point_lights_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_RENDERINGPIPELINE_STAGES_PRE_RENDER_H_