#include "asset/include/aab_bounding_volume.h"

#include <cassert>
#include <string>

#include "app/include/debug.h"
#include "asset/include/mesh.h"
#include "math/include/math_utils.h"
#include "math/include/vector3.h"

namespace ho_renderer {
AABBoundingVolume::AABBoundingVolume(const AABBoundingVolume& bounding_volume) =
    default;
AABBoundingVolume::AABBoundingVolume(const Mesh& mesh)
    : max_edges_(Vector3(MathUtils::kFLOAT_MIN, MathUtils::kFLOAT_MIN,
                         MathUtils::kFLOAT_MIN)),
      min_edges_(Vector3(MathUtils::kFLOAT_MAX, MathUtils::kFLOAT_MAX,
                         MathUtils::kFLOAT_MAX)) {
  for (auto vertex_itr = mesh.vertex_buffer().cbegin();
       vertex_itr != mesh.vertex_buffer().cend(); vertex_itr++) {
    Vector4 point = vertex_itr->coordinate();
    if (point.x() > max_edges_.x()) {
      max_edges_.set_x(point.x());
    }
    if (point.x() < min_edges_.x()) {
      min_edges_.set_x(point.x());
    }
    if (point.y() > max_edges_.y()) {
      max_edges_.set_y(point.y());
    }
    if (point.y() < min_edges_.y()) {
      min_edges_.set_y(point.y());
    }
    if (point.z() > max_edges_.z()) {
      max_edges_.set_z(point.z());
    }
    if (point.z() < min_edges_.z()) {
      min_edges_.set_z(point.z());
    }
  }
}
AABBoundingVolume& AABBoundingVolume::operator=(
    const AABBoundingVolume& bounding_volume) = default;
AABBoundingVolume::~AABBoundingVolume() = default;

const Vector3& AABBoundingVolume::max_edges() const { return max_edges_; }
const Vector3& AABBoundingVolume::min_edges() const { return min_edges_; }
}  // namespace ho_renderer