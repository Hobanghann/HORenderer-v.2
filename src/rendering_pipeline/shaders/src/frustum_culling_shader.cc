#include "rendering_pipeline/shaders/include/frustum_culling_shader.h"

#include "app/include/debug.h"
#include "asset/include/aab_bounding_volume.h"
#include "asset/include/sphere_bounding_volume.h"
#include "math/include/frustum.h"
#include "math/include/math_utils.h"
#include "rendering_pipeline/pipeline_objects/include/render_object_state.h"

namespace ho_renderer {

FrustumCullingShader::FrustumCullingShader() = default;
FrustumCullingShader::~FrustumCullingShader() = default;

FrustumCullingResult FrustumCullingShader::CheckSphereCulling(
    const SphereBoundingVolume& bounding_volume, const Frustum& frustum) const {
  for (auto plane_itr = frustum.planes().cbegin();
       plane_itr != frustum.planes().cend(); plane_itr++) {
    float distance = plane_itr->GetDistanceFromPoint(bounding_volume.center());
    // center of sphere is outof frustum
    if (distance < bounding_volume.radius()) {
      return FrustumCullingResult::kINTERSECT;
    }
    if (plane_itr->EvaluatePoint(bounding_volume.center()) > 0.f) {
      return FrustumCullingResult::kOUTSIDE;
    }
  }
  // center of sphere is inside frustum
  return FrustumCullingResult::kINSIDE;
}

FrustumCullingResult FrustumCullingShader::CheckAABBCulling(
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
      return FrustumCullingResult::kOUTSIDE;
    } else {
      if (plane_itr->EvaluatePoint(farthest_point) > 0.f) {
        return FrustumCullingResult::kINTERSECT;
      }
    }
  }
  return FrustumCullingResult::kINSIDE;
}
}  // namespace ho_renderer