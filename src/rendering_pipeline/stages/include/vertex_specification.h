#ifndef _HORENDERER_RENDERINGPIPELINE_STAGES_VERTEXSPECIFICATION_H_
#define _HORENDERER_RENDERINGPIPELINE_STAGES_VERTEXSPECIFICATION_H_

#include <memory>
#include <vector>

#include "asset/include/game_object.h"
#include "asset/include/mesh.h"
#include "asset/include/vertex.h"
#include "rendering_pipeline/shaders/include/vertex_specifying_shader.h"

namespace ho_renderer {
class VertexSpecification {
 public:
  VertexSpecification();
  VertexSpecification(const VertexSpecification&) = delete;
  VertexSpecification& operator=(const VertexSpecification&) = delete;
  ~VertexSpecification();

  VertexSpecification& SetInputGameObject(const GameObject* game_object);

  VertexSpecification& ResetInputs();

  std::vector<Vertex>* GetOutputVertexBuffer();
  std::vector<uint32_t>* GetOutputIndexBuffer();

  VertexSpecification& ResetOutputs();

  void ReadBuffer();

 private:
  // shader
  std::unique_ptr<VertexSpecifyingShader> vertex_specifying_shader_;
  // input
  const GameObject* input_game_object_;
  // output
  std::vector<Vertex>* output_vertex_buffer_;
  std::vector<uint32_t>* output_index_buffer_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_RENDERINGPIPELINE_STAGES_VERTEXSPECIFICATION_H_