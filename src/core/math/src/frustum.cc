#include "core/math/include/frustum.h"

#include <vector>

#include "core/math/include/matrix4x4.h"
#include "core/math/include/plane.h"

namespace ho_renderer {
Frustum::Frustum(const Frustum& frustum) = default;
Frustum& Frustum::operator=(const Frustum& frustum) = default;
Frustum::~Frustum() = default;

Frustum::Frustum(const Matrix4x4& affine_matrix) {
  Plane left_plane =
      Plane(-(affine_matrix.GetRow4() + affine_matrix.GetRow1()));
  Plane right_plane =
      Plane(-(affine_matrix.GetRow4() - affine_matrix.GetRow1()));
  Plane bottom_plane =
      Plane(-(affine_matrix.GetRow4() + affine_matrix.GetRow2()));
  Plane top_plane = Plane(-(affine_matrix.GetRow4() - affine_matrix.GetRow2()));
  Plane near_plane =
      Plane(-(affine_matrix.GetRow4() + affine_matrix.GetRow3()));
  Plane far_plane = Plane(-(affine_matrix.GetRow4() - affine_matrix.GetRow3()));
  planes_ = {left_plane, right_plane, bottom_plane,
             top_plane,  near_plane,  far_plane};
}
const Plane& Frustum::GetPlane(PlanePosition position) const {
  return planes_[position];
}
const std::vector<Plane>& Frustum::planes() const { return planes_; }
}  // namespace ho_renderer