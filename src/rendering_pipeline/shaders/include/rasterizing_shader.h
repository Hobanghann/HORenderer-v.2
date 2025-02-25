#ifndef _HORENDERER_RENDERINGPIPELINE_SHADERS_RASTERIZING_SHADER_H_
#define _HORENDERER_RENDERINGPIPELINE_SHADERS_RASTERIZING_SHADER_H_

#include <memory>
#include <vector>

#include "asset/include/vertex.h"
#include "rendering_pipeline/pipeline_objects/include/fragment.h"
#include "rendering_pipeline/pipeline_objects/include/line.h"
#include "rendering_pipeline/pipeline_objects/include/point.h"
#include "rendering_pipeline/pipeline_objects/include/triangle.h"

namespace ho_renderer {
class RasterizingShader {
 public:
  RasterizingShader();
  RasterizingShader(const RasterizingShader&) = delete;
  RasterizingShader& operator=(const RasterizingShader&) = delete;
  ~RasterizingShader();

  std::vector<Fragment>* RasterizePoint(
      const std::vector<Vertex>& vertex_buffer,
      const std::vector<Vector3>& transformed_coordinate_buffer,
      const Point& primitive) const;
  std::vector<Fragment>* RasterizeLineAffine(
      const std::vector<Vertex>& vertex_buffer,
      const std::vector<Vector3>& transformed_coordinate_buffer,
      const Line& primitive) const;
  std::vector<Fragment>* RasterizeTriangleAffine(
      const std::vector<Vertex>& vertex_buffer,
      const std::vector<Vector3>& transformed_coordinate_buffer,
      const Triangle& primitive) const;
  std::vector<Fragment>* EdgeFunctionRasterizeTriangleAffine(
      const std::vector<Vertex>& vertex_buffer,
      const std::vector<Vector3>& transformed_coordinate_buffer,
      const Triangle& primitive) const;
  std::vector<Fragment>* RasterizeWireTriangleAffine(
      const std::vector<Vertex>& vertex_buffer,
      const std::vector<Vector3>& transformed_coordinate_buffer,
      const Triangle& primitive) const;
  std::vector<Fragment>* RasterizeLinePerspective(
      const std::vector<Vertex>& vertex_buffer,
      const std::vector<Vector3>& transformed_coordinate_buffer,
      const Line& primitive) const;
  std::vector<Fragment>* RasterizeTrianglePerspective(
      const std::vector<Vertex>& vertex_buffer,
      const std::vector<Vector3>& transformed_coordinate_buffer,
      const Triangle& primitive) const;
  std::vector<Fragment>* EdgeFunctionRasterizeTrianglePerspective(
      const std::vector<Vertex>& vertex_buffer,
      const std::vector<Vector3>& transformed_coordinate_buffer,
      const Triangle& primitive) const;
  std::vector<Fragment>* RasterizeWireTrianglePerspective(
      const std::vector<Vertex>& vertex_buffer,
      const std::vector<Vector3>& transformed_coordinate_buffer,
      const Triangle& primitive) const;
};
}  // namespace ho_renderer
#endif  // _HORENDERER_RENDERINGPIPELINE_SHADERS_RASTERIZING_SHADER_H_