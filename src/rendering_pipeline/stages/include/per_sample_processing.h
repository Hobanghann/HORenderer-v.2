#ifndef _HORENDERER_RENDERINGPIPELINE_STAGES_PERSAMPLEPROCESSING_H_
#define _HORENDERER_RENDERINGPIPELINE_STAGES_PERSAMPLEPROCESSING_H_

#include <memory>

#include "rendering_pipeline/pipeline/include/pipeline_settings.h"
#include "rendering_pipeline/pipeline_objects/include/fragment.h"
#include "rendering_pipeline/pipeline_objects/include/frame_buffer.h"
#include "rendering_pipeline/shaders/include/depth_testing_shader.h"
#include "rendering_pipeline/shaders/include/frame_writing_shader.h"
#include "rendering_pipeline/shaders/include/scissor_testing_shader.h"

namespace ho_renderer {
class PerSampleProcessing {
 public:
  PerSampleProcessing();
  PerSampleProcessing(const PerSampleProcessing&) = delete;
  PerSampleProcessing& operator=(const PerSampleProcessing) = delete;
  ~PerSampleProcessing();

  PerSampleProcessing& SetInputFragment(const Fragment* fragment);
  PerSampleProcessing& SetInputPipelineSettings(
      const PipelineSettings* pipeline_settings);
  PerSampleProcessing& SetInputFrameBuffer(FrameBuffer* frame_buffer);

  PerSampleProcessing& ResetInputs();

  FrameBuffer* GetOutputFrameBuffer() const;

  PerSampleProcessing& ResetOutputs();

  void Process();

 private:
  // shaders
  std::unique_ptr<ScissorTestingShader> scissor_testing_shader_;
  std::unique_ptr<DepthTestingShader> depth_testing_shader_;
  std::unique_ptr<FrameWritingShader> frame_writing_shader_;
  // inputs
  const Fragment* input_fragment_;
  const PipelineSettings* input_pipeline_settings_;
  FrameBuffer* input_output_frame_buffer_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_RENDERINGPIPELINE_STAGES_PERSAMPLEPROCESSING_H_