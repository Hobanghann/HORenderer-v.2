#ifndef _HORENDERER_RENDERINGPIPELINE_STAGES_RASTERIZATION_H_
#define _HORENDERER_RENDERINGPIPELINE_STAGES_RASTERIZATION_H_

// Rasterization stage receives primitive buffer
// From primitive buffer, rasterization stage Rasterizes each primitive to
// fragment, and send each fragment to fragment shader

#include <memory>
#include <vector>

#include "graphics/rendering_pipeline/pipeline_components/include/rasterizer.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/fragment.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/frame_buffer.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/primitive.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/transformed_vertex.h"
#include "graphics/rendering_pipeline/system/include/pipeline_settings.h"

namespace ho_renderer {
class Rasterization {
 public:
  Rasterization();
  Rasterization(const Rasterization &) = delete;
  Rasterization &operator=(const Rasterization &) = delete;
  ~Rasterization();

  std::vector<Fragment> *Rasterize(std::vector<Fragment> *output_buffer,
                                   const Primitive *primitive,
                                   std::vector<TransformedVertex> *v_buffer,
                                   FrameBuffer &frame_buffer,
                                   const PipelineSettings &settings);

 private:
  Rasterizer rasterizer_;
};

}  // namespace ho_renderer

#endif  // _HORENDERER_RENDERINGPIPELINE_STAGES_RASTERIZATION_H_