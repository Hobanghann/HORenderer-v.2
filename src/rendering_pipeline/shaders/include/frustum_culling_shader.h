#ifndef _HORENDERER_RENDERINGPIPELINE_SHADERS_FRUSTRUMCULLINGSHADER_H_
#define _HORENDERER_RENDERINGPIPELINE_SHADERS_FRUSTRUMCULLINGSHADER_H_

#include "asset/include/aab_bounding_volume.h"
#include "asset/include/sphere_bounding_volume.h"
#include "math/include/frustum.h"
#include "rendering_pipeline/pipeline_objects/include/render_object_state.h"

namespace ho_renderer {
class FrustumCullingShader {
 public:
  FrustumCullingShader();
  FrustumCullingShader(const FrustumCullingShader&) = delete;
  FrustumCullingShader& operator=(const FrustumCullingShader&) = delete;
  ~FrustumCullingShader();

  FrustumCullingResult CheckSphereCulling(
      const SphereBoundingVolume& bounding_volume,
      const Frustum& frustum) const;
  FrustumCullingResult CheckAABBCulling(
      const AABBoundingVolume& bounding_volume, const Frustum& frustum) const;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_RENDERINGPIPELINE_SHADERS_CULLINGSHADER_H_