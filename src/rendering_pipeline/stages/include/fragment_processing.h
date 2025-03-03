#ifndef _HORENDERER_RENDERINGPIPELINE_STAGES_FRAGMENTPROCESSING_H_
#define _HORENDERER_RENDERINGPIPELINE_STAGES_FRAGMENTPROCESSING_H_

#include <cstdint>
#include <memory>
#include <vector>

#include "engine/light/include/ambient_light.h"
#include "engine/light/include/directional_light.h"
#include "engine/light/include/point_light.h"
#include "engine/scene/include./scene.h"
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
  FragmentProcessing& SetInputAmbientLight(AmbientLight* light);
  FragmentProcessing& SetInputDirectionalLight(DirectionalLight* light);
  FragmentProcessing& SetInputPointLight(PointLight* lights);

  FragmentProcessing& ResetInputs();

  Fragment* GetOutputFragment() const;

  FragmentProcessing& ResetOutputs();

  void Process();

 private:
  // shader
  std::unique_ptr<FragmentShader> fragment_shader_;

  // input
  const Scene* input_scene_;
  Fragment* input_output_fragment_;
  PipelineSettings* input_pipeline_settings_;
  AmbientLight* input_ambient_light_;
  DirectionalLight* input_directional_light_;
  std::vector<PointLight*> input_point_lights_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_RENDERINGPIPELINE_STAGES_FRAGMENTPROCESSING_H_