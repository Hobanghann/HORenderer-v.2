#include "rendering_pipeline/shaders/include/vertex_shader.h"

#include "app/include/debug.h"
#include "asset/include/vertex.h"
#include "math/include/affine_transform.h"

namespace ho_renderer {
VertexShader::VertexShader() = default;
VertexShader::~VertexShader() = default;

Vertex& ho_renderer::VertexShader::TransformCoordinate(
    Vertex& vertex, const AffineTransform& transformation) const {
  vertex.set_coordinate((transformation.Transform(vertex.coordinate())));
  return vertex;
}
}  // namespace ho_renderer