#ifndef _HORENDERER_FRUSTUM_CULLER_H_
#define _HORENDERER_FRUSTUM_CULLER_H_

#include "graphics/rendering_pipeline/system/include/pipeline_enum.h"
#include "core/math/include/frustum.h"
#include "core/math/include/vector4.h"
#include "graphics/resource/include/aab_bounding_volume.h"
#include "graphics/resource/include/sphere_bounding_volume.h"

namespace ho_renderer {
class FrustumCuller {
 public:
  FrustumCuller();
  FrustumCuller(const FrustumCuller&) = delete;
  FrustumCuller& operator=(const FrustumCuller&) = delete;
  ~FrustumCuller();

  FrustumCullingResult CullPointAgainstFrustum(const Vector4& local_coord,
                                               const Frustum& frustum) const;
  FrustumCullingResult CullLineAgainstFrustum(const Vector4& local_coord1,
                                              const Vector4& local_coord2,
                                              const Frustum& frustum) const;
  FrustumCullingResult CullSphereAgainstFrustum(
      const SphereBoundingVolume& bounding_volume,
      const Frustum& frustum) const;
  FrustumCullingResult CullAABBAgainstFrustum(
      const AABBoundingVolume& bounding_volume, const Frustum& frustum) const;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_FRUSTUM_CULLER_H_