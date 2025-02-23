#ifndef _HORENDERER_MATH_FRUSTRUM_H_
#define _HORENDERER_MATH_FRUSTRUM_H_

#include <vector>

#include "math/include/matrix4x4.h"
#include "math/include/plane.h"

// frustum defined by 6 planes in view, world, local space
// 6 planes that define frustum defined by affine_matrix
namespace ho_renderer {
class Frustum {
 public:
  enum PlanePosition {
    kLEFT = 0,
    kRIGHT,
    kBOTTOM,
    kTOP,
    kNEAR,
    kFAR,
    kPROJECTION
  };

  Frustum() = delete;
  Frustum(const Frustum& frustum);
  Frustum& operator=(const Frustum& frustum);
  ~Frustum();
  explicit Frustum(const Matrix4x4 affine_matrix);

  const Plane& GetPlane(PlanePosition position) const;
  const std::vector<Plane>& planes() const;

 private:
  std::vector<Plane> planes_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_MATH_FRUSTRUM_H_