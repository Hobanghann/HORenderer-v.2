#ifndef _HORENDERER_RENDERINGPIPELINE_SHADERS_VERTEXSPECIFYINGSHADER_H_
#define _HORENDERER_RENDERINGPIPELINE_SHADERS_VERTEXSPECIFYINGSHADER_H_

#include <vector>

#include "asset/include/game_object.h"
#include "asset/include/vertex.h"

namespace ho_renderer {
class VertexSpecifyingShader {
 public:
  VertexSpecifyingShader();
  VertexSpecifyingShader(const VertexSpecifyingShader&) = delete;
  VertexSpecifyingShader& operator=(const VertexSpecifyingShader&) = delete;
  ~VertexSpecifyingShader();

  std::vector<Vertex>* ReadVertexBuffer(const GameObject& game_object) const;
  std::vector<uint32_t>* ReadIndexBuffer(const GameObject& game_object) const;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_RENDERINGPIPELINE_SHADERS_VERTEXSPECIFYINGSHADER_H_