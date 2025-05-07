#include "graphics/resource/include/aab_bounding_volume.h"

#include <string>

#include "core/math/include/math_utils.h"
#include "core/math/include/vector3.h"
#include "graphics/resource/include/mesh.h"
#include "graphics/resource/include/vertex.h"

namespace ho_renderer {
AABBoundingVolume::AABBoundingVolume(const AABBoundingVolume& bounding_volume) =
    default;
AABBoundingVolume::AABBoundingVolume(const Vector3& max, const Vector3& min)
    : max_edges_(max), min_edges_(min), center_(0.5f * (max + min)) {}
AABBoundingVolume::AABBoundingVolume(const Mesh& model)
    : max_edges_(Vector3(MathUtils::kFloatMin, MathUtils::kFloatMin,
                         MathUtils::kFloatMin)),
      min_edges_(Vector3(MathUtils::kFloatMax, MathUtils::kFloatMax,
                         MathUtils::kFloatMax)) {
  const std::vector<Vertex>& v = model.vertices();
  for (auto vertex_itr = v.cbegin(); vertex_itr != v.cend(); vertex_itr++) {
    if (vertex_itr->position().x() > max_edges_.x()) {
      max_edges_.set_x(vertex_itr->position().x());
    }
    if (vertex_itr->position().x() < min_edges_.x()) {
      min_edges_.set_x(vertex_itr->position().x());
    }
    if (vertex_itr->position().y() > max_edges_.y()) {
      max_edges_.set_y(vertex_itr->position().y());
    }
    if (vertex_itr->position().y() < min_edges_.y()) {
      min_edges_.set_y(vertex_itr->position().y());
    }
    if (vertex_itr->position().z() > max_edges_.z()) {
      max_edges_.set_z(vertex_itr->position().z());
    }
    if (vertex_itr->position().z() < min_edges_.z()) {
      min_edges_.set_z(vertex_itr->position().z());
    }
  }
  center_ = 0.5f * (max_edges_ + min_edges_);
}
AABBoundingVolume& AABBoundingVolume::operator=(
    const AABBoundingVolume& bounding_volume) = default;
AABBoundingVolume::~AABBoundingVolume() = default;

const Vector3& AABBoundingVolume::max_edges() const { return max_edges_; }
const Vector3& AABBoundingVolume::min_edges() const { return min_edges_; }
const Vector3& AABBoundingVolume::center() const { return center_; }
}  // namespace ho_renderer