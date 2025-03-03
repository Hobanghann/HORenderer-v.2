#ifndef _HORENDERER_RENDERINGPIPELINE_STAGES_VERTEXPROCESSING_H_
#define _HORENDERER_RENDERINGPIPELINE_STAGES_VERTEXPROCESSING_H_

// Responsibility : Define how vertex shader process on vertices

#include <memory>
#include <vector>

#include "asset/include/vertex.h"
#include "math/include/affine_transform.h"
#include "rendering_pipeline/shaders/include/vertex_shader.h"

namespace ho_renderer {
class VertexProcessing {
 public:
  VertexProcessing();
  VertexProcessing(const VertexProcessing& stage) = delete;
  VertexProcessing& operator=(const VertexProcessing& stage) = delete;
  ~VertexProcessing();

  VertexProcessing& SetInputVertexBuffer(std::vector<Vertex>* vertex_buffer);
  VertexProcessing& SetInputModelingTransform(AffineTransform* transform);
  VertexProcessing& SetInputViewTransform(AffineTransform* transform);
  VertexProcessing& SetInputProjectionTransform(AffineTransform* transform);

  VertexProcessing& ResetInputs();

  std::vector<Vertex>* GetOutputVertexBuffer();
  std::vector<Vector3>* GetOutputViewCoordinateBuffer();

  VertexProcessing& ResetOutputs();

  void Process();

 private:
  // shader
  std::unique_ptr<VertexShader> vertex_shader_;
  // input
  std::vector<Vertex>* input_vertex_buffer_;
  AffineTransform* input_modeling_transform_;
  AffineTransform* input_view_transform_;
  AffineTransform* input_projection_transform_;
  // output
  std::vector<Vertex>* output_vertex_buffer_;
  std::vector<Vector3>* output_view_coordinate_buffer_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_RENDERINGPIPELINE_VERTEXPROCESSING_H_