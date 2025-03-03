#ifndef _HORENDERER_RENDERINGPIPELINE_STAGES_RASTERIZATION_H_
#define _HORENDERER_RENDERINGPIPELINE_STAGES_RASTERIZATION_H_

// Rasterization stage receives primitive buffer
// From primitive buffer, rasterization stage Rasterizes each primitive to
// fragment, and send each fragment to fragment shader

#include <memory>
#include <vector>

#include "rendering_pipeline/pipeline/include/pipeline_settings.h"
#include "rendering_pipeline/pipeline_objects/include/fragment.h"
#include "rendering_pipeline/pipeline_objects/include/frame_buffer.h"
#include "rendering_pipeline/pipeline_objects/include/primitive.h"
#include "rendering_pipeline/pipeline_objects/include/render_object_state.h"
#include "rendering_pipeline/shaders/include/rasterizing_shader.h"

namespace ho_renderer {
class Rasterization {
 public:
  Rasterization();
  Rasterization(const Rasterization&) = delete;
  Rasterization& operator=(const Rasterization&) = delete;
  ~Rasterization();

  Rasterization& SetInputPipelineSettings(PipelineSettings* pipeline_settings);
  Rasterization& SetInputVertexBuffer(std::vector<Vertex>* vertex_buffer);
  Rasterization& SetInputViewCoordinateBuffer(
      std::vector<Vector3>* view_coordinate_buffer);
  Rasterization& SetInputNDCBuffer(std::vector<Vector3>* ndc_buffer);
  Rasterization& SetInputViewportNDCBuffer(
      std::vector<Vector3>* viewport_ndc_buffer);
  Rasterization& SetInputPrimitive(const Primitive* point_primitive);
  Rasterization& SetInputFrameBuffer(const FrameBuffer* frame_buffer);

  Rasterization& ResetInputs();

  std::vector<Fragment>* GetOutputFragmentBuffer() const;

  Rasterization& ResetOutputs();

  void Rasterize();

 private:
  // shader
  std::unique_ptr<RasterizingShader> rasterizing_shader_;

  // input
  PipelineSettings* input_pipeline_settings_;
  std::vector<Vertex>* input_vertex_buffer_;
  std::vector<Vector3>* input_view_coordinate_buffer_;
  std::vector<Vector3>* input_ndc_buffer_;
  std::vector<Vector3>* input_viewport_ndc_buffer_;
  const Primitive* input_primitive_;
  // for early z-testing
  const FrameBuffer* input_frame_buffer_;

  // output
  std::vector<Fragment>* output_fragment_buffer_;
};

}  // namespace ho_renderer

#endif  // _HORENDERER_RENDERINGPIPELINE_STAGES_RASTERIZATION_H_