#ifndef _HORENDERER_RENDERINGPIPELINE_SHADERS_H_
#define _HORENDERER_RENDERINGPIPELINE_SHADERS_H_

// Responsibility : After read index buffer, assemble index to primitive.
//                  If there is remain index in index buffer, ignore.

#include <memory>
#include <vector>

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

  std::vector<Primitive*>* AssemblePoint(
      const std::vector<uint32_t>& index_buffer);
  std::vector<Primitive*>* AssembleLine(
      const std::vector<uint32_t>& index_buffer);
  std::vector<Primitive*>* AssembleTriangle(
      const std::vector<uint32_t>& index_buffer);

  std::vector<Primitive*>* AssembleFilledPoint(
      const std::vector<uint32_t>& index_buffer,
      const std::vector<uint32_t>& primitive_color_buffer);
  std::vector<Primitive*>* AssembleFilledLine(
      const std::vector<uint32_t>& index_buffer,
      const std::vector<uint32_t>& primitive_color_buffer);
  std::vector<Primitive*>* AssembleFilledTriangle(
      const std::vector<uint32_t>& index_buffer,
      const std::vector<uint32_t>& primitive_color_buffer);
};
}  // namespace ho_renderer

#endif  // _HORENDERER_RENDERINGPIPELINE_SHADERS_H_