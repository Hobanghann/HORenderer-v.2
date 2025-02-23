#ifndef _HORENDERER_ASSET_AABBOUNDINGVOLUME_H_
#define _HORENDERER_ASSET_AABBOUNDINGVOLUME_H_

#include "math/include/vector3.h"

namespace ho_renderer {
class Mesh;
// axis aligned box bounding volume
class AABBoundingVolume {
 public:
  AABBoundingVolume() = delete;
  AABBoundingVolume(const AABBoundingVolume& bounding_volume);
  AABBoundingVolume(const Mesh& mesh);
  AABBoundingVolume& operator=(const AABBoundingVolume& bounding_volume);
  ~AABBoundingVolume();

  const Vector3& max_edges() const;
  const Vector3& min_edges() const;

 private:
  Vector3 max_edges_;
  Vector3 min_edges_;
};
}  // namespace ho_renderer
#endif  // _HORENDERER_ASSET_AABBOUNDINGVOLUME_H_