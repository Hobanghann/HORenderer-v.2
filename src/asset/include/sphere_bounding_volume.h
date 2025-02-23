#ifndef _HORENDERER_ASSET_SPHEREBOUNDINGVOLUME_H_
#define _HORENDERER_ASSET_SPHEREBOUNDINGVOLUME_H_
#include <vector>

#include "math/include/vector3.h"

namespace ho_renderer {
class Mesh;
class SphereBoundingVolume {
 public:
  SphereBoundingVolume() = delete;
  SphereBoundingVolume(const SphereBoundingVolume& bounding_volume);
  SphereBoundingVolume(const Mesh& mesh);
  SphereBoundingVolume& operator=(const SphereBoundingVolume& bounding_volume);
  ~SphereBoundingVolume();

  const Vector3& center() const;
  const float radius() const;

 private:
  Vector3 center_;
  float radius_;
};

}  // namespace ho_renderer
#endif  // _HORENDERER_ASSET_SPHEREBOUNDINGVOLUME_H_