#ifndef _HORENDERER_CAMERA_BUILDER_H_
#define _HORENDERER_CAMERA_BUILDER_H_

#include <memory>
#include <string>

#include "core/math/include/vector3.h"
#include "scene/camera/include/camera.h"

namespace ho_renderer {
class CameraBuilder {
 public:
  CameraBuilder();
  CameraBuilder(const CameraBuilder& camera) = delete;
  CameraBuilder& operator=(const CameraBuilder& camera) = delete;
  ~CameraBuilder();

  CameraBuilder& set_name(const std::string& name);
  CameraBuilder& set_fov(float fov);
  CameraBuilder& set_viewport_width(float viewport_width);
  CameraBuilder& set_viewport_height(float viewport_height);
  CameraBuilder& set_near_distance(float near_distance);
  CameraBuilder& set_far_distance(float far_distance);
  CameraBuilder& set_rotate_velocity(float rotate_velocity);
  CameraBuilder& set_move_velocity(float move_velocity);
  CameraBuilder& set_world_coord(const Vector3& world_coord);
  CameraBuilder& set_world_forward(const Vector3& world_forward);
  CameraBuilder& set_world_right(const Vector3& world_right);
  CameraBuilder& set_world_up(const Vector3& world_up);

  std::unique_ptr<Camera> Build() const;
  void Reset();

 private:
  std::string name_;
  float fov_;
  float viewport_width_;
  float viewport_height_;  // width / height
  float near_distance_;
  float far_distance_;
  float rotate_velocity_;
  float move_velocity_;
  Vector3 world_coord_;
  Vector3 world_forward_;
  Vector3 world_right_;
  Vector3 world_up_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_CAMERA_BUILDER_H_