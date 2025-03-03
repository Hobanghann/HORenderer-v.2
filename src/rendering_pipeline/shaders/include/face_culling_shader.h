#ifndef _HORENDERER_RENDERINGPIPELINE_SHADERS_FACECULLINGSHADER_H_
#define _HORENDERER_RENDERINGPIPELINE_SHADERS_FACECULLINGSHADER_H_

#include <memory>
#include <vector>

#include "asset/include/vertex.h"
#include "math/include/vector3.h"
#include "rendering_pipeline/pipeline_objects/include/triangle.h"

namespace ho_renderer {
class FaceCullingShader {
 public:
  FaceCullingShader();
  FaceCullingShader(const FaceCullingShader&) = delete;
  FaceCullingShader& operator=(const FaceCullingShader&) = delete;
  ~FaceCullingShader();

  void BackfaceCulling(std::vector<Primitive*>& primitive_buffer,
                       std::vector<Vector3>& coordinate_buffer,
                       const Vector3& view_direction) const;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_RENDERINGPIPELINE_SHADERS_FACECULLINGSHADER_H_