#ifndef _HORENDERER_FRUSTUM_H_
#define _HORENDERER_FRUSTUM_H_

#include <vector>

#include "core/math/include/matrix4x4.h"
#include "core/math/include/plane.h"

// frustum defined by 6 planes in view, world, local space
// 6 planes that define frustum defined by affine_matrix
namespace ho_renderer {
class Frustum {
 public:
  enum PlanePosition {
    kLeft = 0,
    kRight,
    kBottom,
    kTop,
    kNear,
    kFar,
    kProjection
  };

  Frustum() = delete;
  Frustum(const Frustum& frustum);
  Frustum& operator=(const Frustum& frustum);
  ~Frustum();
  explicit Frustum(const Matrix4x4& affine_matrix);

  const Plane& GetPlane(PlanePosition position) const;
  const std::vector<Plane>& planes() const;

 private:
  std::vector<Plane> planes_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_FRUSTUM_H_