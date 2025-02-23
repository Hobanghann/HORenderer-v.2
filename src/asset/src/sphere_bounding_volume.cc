#include "asset/include/sphere_bounding_volume.h"

#include <cassert>
#include <string>
#include <vector>

#include "app/include/debug.h"
#include "asset/include/mesh.h"
#include "asset/include/vertex.h"
#include "math/include/math_utils.h"

namespace ho_renderer {

SphereBoundingVolume::SphereBoundingVolume(
    const SphereBoundingVolume& bounding_volume) = default;
SphereBoundingVolume::SphereBoundingVolume(const Mesh& mesh) {
  const std::vector<Vertex>& vertex_buffer = mesh.vertex_buffer();
  // add all vertex coordinate
  for (auto vertex_itr = vertex_buffer.cbegin();
       vertex_itr != vertex_buffer.cend(); vertex_itr++) {
    center_ += vertex_itr->coordinate().ToVector3();
  }
  // calculate average coordinate
  center_ = (1.f / vertex_buffer.size()) * center_;

  // get max distance
  float max_squared_distance = 0.f;
  for (auto vertex_itr = vertex_buffer.cbegin();
       vertex_itr != vertex_buffer.cend(); vertex_itr++) {
    float squared_distance = MathUtils::GetSquaredDistance(
        center_, vertex_itr->coordinate().ToVector3());
    if (max_squared_distance < squared_distance) {
      max_squared_distance = squared_distance;
    }
  }
  // set radius
  radius_ = MathUtils::Sqrtf(max_squared_distance);
}
SphereBoundingVolume& SphereBoundingVolume::operator=(
    const SphereBoundingVolume& bounding_volume) = default;
SphereBoundingVolume::~SphereBoundingVolume() = default;

const Vector3& SphereBoundingVolume::center() const { return center_; }
const float SphereBoundingVolume::radius() const { return radius_; }
}  // namespace ho_renderer
