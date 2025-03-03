#ifndef _HORENDERER_RENDERINGPIPELINE_STAGES_VERTEXPOSTPROCESSING_H_
#define _HORENDERER_RENDERINGPIPELINE_STAGES_VERTEXPOSTPROCESSING_H_

// Respolsibility : define how shaders work.

#include <vector>

#include "asset/include/game_object.h"
#include "asset/include/vertex.h"
#include "math/include/vector3.h"
#include "rendering_pipeline/pipeline/include/pipeline_settings.h"
#include "rendering_pipeline/pipeline_objects/include/primitive.h"
#include "rendering_pipeline/pipeline_objects/include/render_object_state.h"
#include "rendering_pipeline/shaders/include/clipping_shader.h"
#include "rendering_pipeline/shaders/include/face_culling_shader.h"
#include "rendering_pipeline/shaders/include/frustum_culling_shader.h"
#include "rendering_pipeline/shaders/include/perspective_divide_shader.h"
#include "rendering_pipeline/shaders/include/primitive_assembly_shader.h"
#include "rendering_pipeline/shaders/include/vertex_shader.h"
#include "rendering_pipeline/shaders/include/viewport_transform_shader.h"

namespace ho_renderer {

class VertexPostProcessing {
 public:
  VertexPostProcessing();
  VertexPostProcessing(const VertexPostProcessing&) = delete;
  VertexPostProcessing& operator=(const VertexPostProcessing&) = delete;
  ~VertexPostProcessing();

  VertexPostProcessing& SetInputGameObject(const GameObject* game_object);
  VertexPostProcessing& SetInputVertexBuffer(
      std::vector<Vertex>* vertex_buffer);
  VertexPostProcessing& SetInputIndexBuffer(
      std::vector<uint32_t>* index_buffer);
  VertexPostProcessing& SetInputViewCoordinateBuffer(
      std::vector<Vector3>* view_coordinate_buffer);
  VertexPostProcessing& SetInputPrimitiveColorBuffer(
      std::vector<LinearRGB>* primitive_color_buffer);
  VertexPostProcessing& SetInputFrustum(const Frustum* frustum);
  VertexPostProcessing& SetInputPipelineSettings(
      PipelineSettings* pipeline_settings);

  VertexPostProcessing& ResetInputs();

  std::vector<Primitive*>* GetOutputPrimitiveBuffer();
  std::vector<Vector3>* GetOutputNDCBuffer();
  std::vector<Vector3>* GetOutputViewportNDCBuffer();
  RenderObjectState* GetOutputRenderObjectStates();

  VertexPostProcessing& ResetOutputs();

  void Process();

 private:
  // shaders
  std::unique_ptr<VertexShader> vertex_shader_;
  std::unique_ptr<PrimitiveAssemblyShader> primitive_assembly_shader_;
  std::unique_ptr<FrustumCullingShader> frustum_culling_shader_;
  std::unique_ptr<PerspectiveDivideShader> perspective_divide_shader_;
  std::unique_ptr<FaceCullingShader> face_culling_shader_;
  std::unique_ptr<ClippingShader> clipping_shader_;
  std::unique_ptr<ViewportTransformShader> viewport_transform_shader_;

  // inputs
  const GameObject* input_game_object_;
  std::vector<Vertex>* input_vertex_buffer_;
  std::vector<std::uint32_t>* input_index_buffer_;
  std::vector<Vector3>* input_view_coordinate_buffer_;
  std::vector<LinearRGB>* input_primitive_color_buffer_;
  const Frustum* input_frustum_;
  PipelineSettings* input_pipeline_settings_;

  // outputs
  std::vector<Primitive*>* output_primitive_buffer_;
  std::vector<Vector3>* output_ndc_buffer_;
  std::vector<Vector3>* output_viewport_ndc_buffer_;
  RenderObjectState* output_render_object_states_;
};
}  // namespace ho_renderer

#endif /
