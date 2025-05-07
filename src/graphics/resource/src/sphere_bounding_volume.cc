#include "graphics/resource/include/sphere_bounding_volume.h"

#include <cassert>
#include <string>
#include <vector>

#include "core/math/include/math_utils.h"
#include "graphics/resource/include/mesh.h"
#include "graphics/resource/include/vertex.h"

namespace ho_renderer {
SphereBoundingVolume::SphereBoundingVolume(
    const SphereBoundingVolume& bounding_volume) = default;
SphereBoundingVolume::SphereBoundingVolume(const Vector3& center, float radius)
    : center_(center), radius_(radius) {}
SphereBoundingVolume::SphereBoundingVolume(const Mesh& mesh) : center_(Vector3::kZero), radius_(0.f) {
  const std::vector<Vertex>& v = mesh.vertices();
  std::size_t n = 0;
  for (const auto& vertex : v) {
    n += 1;
    Vector3 x = vertex.position().ToVector3();
    center_ += (x - center_) * (1.0f / static_cast<float>(n));
  }

  float max_squared_distance = 0.f;
  for (const auto& vertex : v) {
    float squared_distance =
        MathUtils::GetSquaredDistance(center_, vertex.position().ToVector3());
    max_squared_distance = std::max(max_squared_distance, squared_distance);
  }
  radius_ = MathUtils::Sqrtf(max_squared_distance);
}
SphereBoundingVolume& SphereBoundingVolume::operator=(
    const SphereBoundingVolume& bounding_volume) = default;
SphereBoundingVolume::~SphereBoundingVolume() = default;

const Vector3& SphereBoundingVolume::center() const { return center_; }
float SphereBoundingVolume::radius() const { return radius_; }
}  // namespace ho_renderer
