#ifndef _HORENDERER_AAB_BOUNDING_VOLUME_H_
#define _HORENDERER_AAB_BOUNDING_VOLUME_H_

#include "core/math/include/vector3.h"

namespace ho_renderer {
class Mesh;
// axis aligned box bounding volume
class AABBoundingVolume {
 public:
  AABBoundingVolume() = delete;
  AABBoundingVolume(const AABBoundingVolume& bounding_volume);
  AABBoundingVolume(const Vector3& max, const Vector3& min);
  AABBoundingVolume(const Mesh& mesh);
  AABBoundingVolume& operator=(const AABBoundingVolume& bounding_volume);
  ~AABBoundingVolume();

  const Vector3& max_edges() const;
  const Vector3& min_edges() const;
  const Vector3& center() const;

 private:
  Vector3 max_edges_;
  Vector3 min_edges_;
  Vector3 center_;
};
}  // namespace ho_renderer
#endif  // _HORENDERER_AAB_BOUNDING_VOLUME_H_