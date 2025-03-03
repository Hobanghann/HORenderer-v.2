#ifndef _HORENDERER_RENDERINGPIPELINE_SHADERS_H_
#define _HORENDERER_RENDERINGPIPELINE_SHADERS_H_

// Responsibility : After read index buffer, assemble index to primitive.
//                  If there is remain index in index buffer, ignore.

#include <memory>
#include <vector>

#include "engine/color/include/linear_rgb.h"
#include "rendering_pipeline/pipeline_objects/include/line.h"
#include "rendering_pipeline/pipeline_objects/include/point.h"
#include "rendering_pipeline/pipeline_objects/include/triangle.h"

namespace ho_renderer {
class PrimitiveAssemblyShader {
 public:
  PrimitiveAssemblyShader();
  PrimitiveAssemblyShader(const PrimitiveAssemblyShader&) = delete;
  PrimitiveAssemblyShader& operator=(const PrimitiveAssemblyShader&) = delete;
  ~PrimitiveAssemblyShader();

  std::vector<Primitive*>* AssembleTexturedPoint(
      const std::vector<uint32_t>& index_buffer);
  std::vector<Primitive*>* AssembleTexturedLine(
      const std::vector<uint32_t>& index_buffer);
  std::vector<Primitive*>* AssembleTexturedTriangle(
      const std::vector<uint32_t>& index_buffer,
      const std::vector<Vector3>& view_coordinate_buffer);

  std::vector<Primitive*>* AssembleColoredPoint(
      const std::vector<uint32_t>& index_buffer,
      const std::vector<LinearRGB>& primitive_color_buffer);
  std::vector<Primitive*>* AssembleColoredLine(
      const std::vector<uint32_t>& index_buffer,
      const std::vector<LinearRGB>& primitive_color_buffer);
  std::vector<Primitive*>* AssembleColoredTriangle(
      const std::vector<uint32_t>& index_buffer,
      const std::vector<Vector3>& view_coordinate_buffer,
      const std::vector<LinearRGB>& primitive_color_buffer);
};
}  // namespace ho_renderer

#endif  // _HORENDERER_RENDERINGPIPELINE_SHADERS_H_