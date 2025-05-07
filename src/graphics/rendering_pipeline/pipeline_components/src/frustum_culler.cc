#include "graphics/rendering_pipeline/pipeline_components/include/frustum_culler.h"

#include <array>
#include <cstdint>

#include "core/math/include/frustum.h"
#include "core/math/include/vector4.h"
#include "graphics/rendering_pipeline/system/include/pipeline_enum.h"
#include "graphics/resource/include/aab_bounding_volume.h"
#include "graphics/resource/include/sphere_bounding_volume.h"

namespace ho_renderer {

FrustumCuller::FrustumCuller() = default;
FrustumCuller::~FrustumCuller() = default;

FrustumCullingResult FrustumCuller::CullPointAgainstFrustum(
    const Vector4& local_coord, const Frustum& frustum) const {
  for (auto plane_itr = frustum.planes().cbegin();
       plane_itr != frustum.planes().cend(); plane_itr++) {
    if (plane_itr->EvaluatePoint(local_coord.ToVector3()) > 0.f) {
      return FrustumCullingResult::kOutside;
    }
  }
  return FrustumCullingResult::kInside;
}
FrustumCullingResult FrustumCuller::CullLineAgainstFrustum(
    const Vector4& local_coord1, const Vector4& local_coord2,
    const Frustum& frustum) const {
  // flags mean point is outside plane(Left, Right, Bottom, Top, Near, Far)
  std::array<std::uint32_t, 6> flags = {0b100000, 0b010000, 0b001000,
                                        0b000100, 0b000010, 0b000001};
  std::uint32_t v1_flag = 0;
  std::uint32_t v2_flag = 0;
  for (int i = 0; i < frustum.planes().size(); i++) {
    const Plane& p = frustum.planes()[i];
    if (p.EvaluatePoint(local_coord1.ToVector3()) > 0.f) {
      v1_flag |= flags[i];
    }
    if (p.EvaluatePoint(local_coord2.ToVector3()) > 0.f) {
      v2_flag |= flags[i];
    }
  }
  if (v1_flag == 0 && v2_flag == 0) {
    return FrustumCullingResult::kInside;
  }
  if ((v1_flag & v2_flag) != 0) {
    return FrustumCullingResult::kOutside;
  }
  return FrustumCullingResult::kIntersect;
}
FrustumCullingResult FrustumCuller::CullSphereAgainstFrustum(
    const SphereBoundingVolume& bounding_volume, const Frustum& frustum) const {
  for (auto plane_itr = frustum.planes().cbegin();
       plane_itr != frustum.planes().cend(); plane_itr++) {
    float distance = plane_itr->GetDistanceFromPoint(bounding_volume.center());
    // center of sphere is outof frustum
    if (distance < bounding_volume.radius()) {
      return FrustumCullingResult::kIntersect;
    }
    if (plane_itr->EvaluatePoint(bounding_volume.center()) > 0.f) {
      return FrustumCullingResult::kOutside;
    }
  }
  // center of sphere is inside frustum
  return FrustumCullingResult::kInside;
}

FrustumCullingResult FrustumCuller::CullAABBAgainstFrustum(
    const AABBoundingVolume& bounding_volume, const Frustum& frustum) const {
  bool is_intersected = false;
  for (auto plane_itr = frustum.planes().cbegin();
       plane_itr != frustum.planes().cend(); plane_itr++) {
    const Vector3& normal_vector = plane_itr->normal_vector();
    Vector3 nearest_point = bounding_volume.min_edges();
    Vector3 farthest_point = bounding_volume.max_edges();
    if (normal_vector.x() < 0.f) {
      nearest_point.set_x(bounding_volume.max_edges().x());
      farthest_point.set_x(bounding_volume.min_edges().x());
    }
    if (normal_vector.y() < 0.f) {
      nearest_point.set_y(bounding_volume.max_edges().y());
      farthest_point.set_y(bounding_volume.min_edges().y());
    }
    if (normal_vector.z() < 0.f) {
      nearest_point.set_z(bounding_volume.max_edges().z());
      farthest_point.set_z(bounding_volume.min_edges().z());
    }
    if (plane_itr->EvaluatePoint(nearest_point) > 0.f) {
      return FrustumCullingResult::kOutside;
    } else {
      if (plane_itr->EvaluatePoint(farthest_point) > 0.f) {
        return FrustumCullingResult::kIntersect;
      }
    }
  }
  return FrustumCullingResult::kInside;
}
}  // namespace ho_renderer