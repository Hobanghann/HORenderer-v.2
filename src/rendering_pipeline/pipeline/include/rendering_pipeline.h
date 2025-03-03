#ifndef _HORENDERER_RENDERINGPIPELINE_PIPELINE_RENDERINGPIPELINE_H_
#define _HORENDERER_RENDERINGPIPELINE_PIPELINE_RENDERINGPIPELINE_H_

// Responsibility : manage pipeline stages and shaders
//                  define How whole pipeline works to render scene

#include <memory>

#include "engine/scene/include/scene.h"
#include "rendering_pipeline/pipeline/include/pipeline_settings.h"
#include "rendering_pipeline/stages/include/fragment_processing.h"
#include "rendering_pipeline/stages/include/per_sample_processing.h"
#include "rendering_pipeline/stages/include/pre_render.h"
#include "rendering_pipeline/stages/include/rasterization.h"
#include "rendering_pipeline/stages/include/vertex_post_processing.h"
#include "rendering_pipeline/stages/include/vertex_processing.h"
#include "rendering_pipeline/stages/include/vertex_specification.h"

namespace ho_renderer {
class RenderingPipeline {
 public:
  RenderingPipeline() = delete;
  RenderingPipeline(const RenderingPipeline&) = delete;
  RenderingPipeline(const int screen_width, const int screen_height,
                    const Vector2& viewport_position,
                    const float depth_range_min, const float depth_range_max);
  RenderingPipeline& operator=(const RenderingPipeline&) = delete;
  ~RenderingPipeline();

  PipelineSettings& pipeline_settings();
  FrameBuffer& frame_buffer();

  void Run(const Scene* scene);

 private:
  PipelineSettings pipeline_settings_;
  FrameBuffer frame_buffer_;
  std::unique_ptr<PreRenderStage> pre_render_stage_;
  std::unique_ptr<VertexSpecification> vertex_specification_stage_;
  std::unique_ptr<VertexProcessing> vertex_processing_stage_;
  std::unique_ptr<VertexPostProcessing> vertex_post_processing_stage_;
  std::unique_ptr<Rasterization> rasterization_stage_;
  std::unique_ptr<FragmentProcessing> fragment_processing_stage_;
  std::unique_ptr<PerSampleProcessing> per_sample_processing_stage_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_RENDERINGPIPELINE_PIPELINE_RENDERINGPIPELINE_H_