#ifndef _HORENDERER_RENDERINGPIPELINE_SHADERS_VERTEXSHADER_H_
#define _HORENDERER_RENDERINGPIPELINE_SHADERS_VERTEXSHADER_H_

// Responsibility : Transform attributes vertex have

#include "asset/include/vertex.h"
#include "math/include/affine_transform.h"

namespace ho_renderer {
class VertexShader {
 public:
  VertexShader();
  VertexShader(const VertexShader&) = delete;
  VertexShader& operator=(const VertexShader&) = delete;
  ~VertexShader();

  Vertex& TransformCoordinate(Vertex& vertex,
                              const AffineTransform& transformation) const;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_RENDERINGPIPELINE_SHADERS_VERTEXSHADER_H_