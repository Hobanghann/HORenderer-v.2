#ifndef _HORENDERER_RENDERINGPIPELINE_STAGES_FRAGMENTPROCESSING_H_
#define _HORENDERER_RENDERINGPIPELINE_STAGES_FRAGMENTPROCESSING_H_

#include <cstdint>
#include <memory>
#include <vector>

#include "rendering_pipeline/pipeline/include/pipeline_settings.h"
#include "rendering_pipeline/shaders/include/fragment_shader.h"

namespace ho_renderer {
class FragmentProcessing {
 public:
  FragmentProcessing();
  FragmentProcessing(const FragmentProcessing&) = delete;
  FragmentProcessing& operator=(const FragmentProcessing&) = delete;
  ~FragmentProcessing();

  FragmentProcessing& SetInputFragment(Fragment* fragment);
  FragmentProcessing& SetInputPipelineSettings(
      PipelineSettings* pipeline_settings);

  FragmentProcessing& ResetInputs();

  Fragment* GetOutputFragment() const;

  FragmentProcessing& ResetOutputs();

  void Process();

 private:
  // shader
  std::unique_ptr<FragmentShader> fragment_shader_;

  // input
  Fragment* input_output_fragment_;
  PipelineSettings* input_pipeline_settings_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_RENDERINGPIPELINE_STAGES_FRAGMENTPROCESSING_H_