#ifndef _HORENDERER_RENDERINGPIPELINE_SHADERS_RASTERIZING_SHADER_H_
#define _HORENDERER_RENDERINGPIPELINE_SHADERS_RASTERIZING_SHADER_H_

#include <memory>
#include <vector>

#include "asset/include/vertex.h"
#include "rendering_pipeline/pipeline_objects/include/fragment.h"
#include "rendering_pipeline/pipeline_objects/include/line.h"
#include "rendering_pipeline/pipeline_objects/include/point.h"
#include "rendering_pipeline/pipeline_objects/include/triangle.h"
#include "rendering_pipeline/pipeline_objects/include/frame_buffer.h"

namespace ho_renderer {
class RasterizingShader {
 public:
  RasterizingShader();
  RasterizingShader(const RasterizingShader&) = delete;
  RasterizingShader& operator=(const RasterizingShader&) = delete;
  ~RasterizingShader();

  std::vector<Fragment>* RasterizePoint(
      const FrameBuffer& frame_buffer, const std::vector<Vertex>& vertex_buffer,
      const std::vector<Vector3>& ndc_buffer,
      const std::vector<Vector3>& viewport_ndc_buffer,
      const Point& primitive) const;
  std::vector<Fragment>* RasterizeLineAffine(
      const FrameBuffer& frame_buffer, const std::vector<Vertex>& vertex_buffer,
      const std::vector<Vector3>& ndc_buffer,
      const std::vector<Vector3>& viewport_ndc_buffer,
      const Line& primitive) const;
  std::vector<Fragment>* RasterizeTriangleAffine(
      const FrameBuffer& frame_buffer, const std::vector<Vertex>& vertex_buffer,
      const std::vector<Vector3>& ndc_buffer,
      const std::vector<Vector3>& viewport_ndc_buffer,
      const Triangle& primitive) const;
  std::vector<Fragment>* EdgeFunctionRasterizeTriangleAffine(
      const FrameBuffer& frame_buffer, const std::vector<Vertex>& vertex_buffer,
      const std::vector<Vector3>& ndc_buffer,
      const std::vector<Vector3>& viewport_ndc_buffer,
      const Triangle& primitive) const;
  std::vector<Fragment>* RasterizeWireTriangleAffine(
      const FrameBuffer& frame_buffer, const std::vector<Vertex>& vertex_buffer,
      const std::vector<Vector3>& ndc_buffer,
      const std::vector<Vector3>& viewport_ndc_buffer,
      const Triangle& primitive) const;
  std::vector<Fragment>* RasterizeLinePerspective(
      const FrameBuffer& frame_buffer, const std::vector<Vertex>& vertex_buffer,
      const std::vector<Vector3>& ndc_buffer,
      const std::vector<Vector3>& viewport_ndc_buffer,
      const Line& primitive) const;
  std::vector<Fragment>* RasterizeTrianglePerspective(
      const FrameBuffer& frame_buffer, const std::vector<Vertex>& vertex_buffer,
      const std::vector<Vector3>& ndc_buffer,
      const std::vector<Vector3>& viewport_ndc_buffer,
      const Triangle& primitive) const;
  std::vector<Fragment>* EdgeFunctionRasterizeTrianglePerspective(
      const FrameBuffer& frame_buffer, const std::vector<Vertex>& vertex_buffer,
      const std::vector<Vector3>& ndc_buffer,
      const std::vector<Vector3>& viewport_ndc_buffer,
      const Triangle& primitive) const;
  std::vector<Fragment>* RasterizeWireTrianglePerspective(
      const FrameBuffer& frame_buffer, const std::vector<Vertex>& vertex_buffer,
      const std::vector<Vector3>& ndc_buffer,
      const std::vector<Vector3>& viewport_ndc_buffer,
      const Triangle& primitive) const;
};
}  // namespace ho_renderer
#endif  // _HORENDERER_RENDERINGPIPELINE_SHADERS_RASTERIZING_SHADER_H_