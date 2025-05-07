#ifndef _HORENDERER_RENDERING_PIPELINE_H_
#define _HORENDERER_RENDERING_PIPELINE_H_

// Responsibility : manage pipeline stages and pipeline_components
//                  define How whole pipeline works to render scene

#include <memory>

#include "graphics/rendering_pipeline/stages/include/fragment_processing.h"
#include "graphics/rendering_pipeline/stages/include/per_sample_processing.h"
#include "graphics/rendering_pipeline/stages/include/pre_render.h"
#include "graphics/rendering_pipeline/stages/include/rasterization.h"
#include "graphics/rendering_pipeline/stages/include/vertex_post_processing.h"
#include "graphics/rendering_pipeline/stages/include/vertex_processing.h"
#include "graphics/rendering_pipeline/stages/include/vertex_specification.h"
#include "graphics/rendering_pipeline/system/include/pipeline_resources_manager.h"
#include "graphics/rendering_pipeline/system/include/pipeline_settings.h"
#include "scene/system/include/scene.h"

namespace ho_renderer {
class RenderingPipeline {
 public:
  RenderingPipeline() = delete;
  RenderingPipeline(const RenderingPipeline&) = delete;
  RenderingPipeline(const int viewport_width, const int viewport_height);
  RenderingPipeline& operator=(const RenderingPipeline&) = delete;
  ~RenderingPipeline();

  PipelineSettings& pipeline_settings();
  FrameBuffer& frame_buffer();

  void Run(const Scene* scene);

 private:
  PipelineSettings pipeline_settings_;
  FrameBuffer frame_buffer_;
  PreRenderStage pre_render_;
  VertexSpecification vertex_specification_;
  VertexProcessing vertex_processing_;
  VertexPostProcessing vertex_post_processing_;
  Rasterization rasterization_;
  FragmentProcessing fragment_processing_;
  PerSampleProcessing per_sample_processing_;
  PipelineResourcesManager resource_manager_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_PIPELINE_RENDERING_PIPELINE_H_