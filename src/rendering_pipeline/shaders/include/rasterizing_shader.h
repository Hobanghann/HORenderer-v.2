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

  std::vector<Fragment>* SplitPoint(
      const std::vector<Vertex>& vertex_buffer,
      const std::vector<Vector3>& transformed_coordinate_buffer,
      const Point& primitive) const;
  std::vector<Fragment>* SplitLineWithAffineInterpolation(
      const std::vector<Vertex>& vertex_buffer,
      const std::vector<Vector3>& transformed_coordinate_buffer,
      const Line& primitive) const;
  std::vector<Fragment>* SplitTriangleWithAffineInterpolation(
      const std::vector<Vertex>& vertex_buffer,
      const std::vector<Vector3>& transformed_coordinate_buffer,
      const Triangle& primitive) const;
  std::vector<Fragment>* SplitWireTriangleWithAffineInterpolation(
      const std::vector<Vertex>& vertex_buffer,
      const std::vector<Vector3>& transformed_coordinate_buffer,
      const Triangle& primitive) const;
  std::vector<Fragment>* SplitLineWithPerspectiveInterpolation(
      const std::vector<Vertex>& vertex_buffer,
      const std::vector<Vector3>& transformed_coordinate_buffer,
      const Line& primitive) const;
  std::vector<Fragment>* SplitTriangleWithPerspectiveInterpolation(
      const std::vector<Vertex>& vertex_buffer,
      const std::vector<Vector3>& transformed_coordinate_buffer,
      const Triangle& primitive) const;
  std::vector<Fragment>* SplitWireTriangleWithPerspectiveInterpolation(
      const std::vector<Vertex>& vertex_buffer,
      const std::vector<Vector3>& transformed_coordinate_buffer,
      const Triangle& primitive) const;
};
}  // namespace ho_renderer
#endif  // _HORENDERER_RENDERINGPIPELINE_SHADERS_RASTERIZING_SHADER_H_