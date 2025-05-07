#ifndef _HORENDERER_CAMERA_H_
#define _HORENDERER_CAMERA_H_

#include <string>

#include "core/input/include/input_listener.h"
#include "core/math/include/affine_transform.h"
#include "scene/object/include/transform.h"

namespace ho_renderer {
class Camera : public InputListener {
 public:
  Camera() = delete;
  Camera(const Camera& camera);
  Camera(const std::string& name, const Transform& transform, float fov,
         float aspect_ratio, float near_distance, float far_distance,
         float rotate_velocity, float move_velocity);
  Camera& operator=(const Camera& camera);
  ~Camera();

  const std::string& name() const;
  const Transform& transform() const;
  float fov() const;
  float focal_length() const;
  float aspect_ratio() const;
  float near_distance() const;
  float far_distance() const;
  bool is_property_changed() const;

  Camera& set_name(const std::string& name);
  Camera& set_transform(const Transform& transform);
  Camera& set_fov(float fov);
  Camera& set_aspect_ratio(float viewport_width, float viewport_height);
  Camera& set_near_distance(float near_distance);
  Camera& set_far_distance(float far_distance);
  Camera& set_is_property_changed(bool is_property_changed);

  AffineTransform GetViewTransform() const;
  AffineTransform GetProjectionTransform() const;
  AffineTransform GetReversedProjectionTransform() const;

  void Update(InputReceiver& input_receiver, float delta_time) override;

 private:
  std::string name_;
  Transform transform_;
  float fov_;
  float focal_length_;
  float aspect_ratio_;  // width / height
  float near_distance_;
  float far_distance_;
  bool is_property_changed_;
  float rotate_velocity_;
  float move_velocity_;
};
}  // namespace ho_renderer
#endif  // _HORENDERER_CAMERA_H_