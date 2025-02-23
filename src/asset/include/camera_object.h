#ifndef _HORENDERER_ASSET_CAMERAOBJECT_H_
#define _HORENDERER_ASSET_CAMERAOBJECT_H_

#include <memory>
#include <string>

#include "asset/include/transform.h"
#include "engine/include/input_listener.h"

namespace ho_renderer {
class CameraObject : public InputListener {
 public:
  CameraObject();
  CameraObject(const CameraObject& camera_object);
  CameraObject(const std::string& name);
  CameraObject& operator=(const CameraObject& camera_object);
  ~CameraObject();

  const std::string& name() const;
  const Transform& transform() const;
  float fov() const;
  float focal_length() const;
  float aspect_ratio() const;
  float near_distance() const;
  float far_distance() const;
  bool is_property_changed() const;

  CameraObject& set_name(const std::string& name);
  CameraObject& set_transform(const Transform& transform);
  CameraObject& set_fov(const float fov);
  CameraObject& set_aspect_ratio(const float screen_width,
                                 const float screen_height);
  CameraObject& set_near_distance(const float near_distance);
  CameraObject& set_far_distance(const float far_distance);
  CameraObject& set_is_property_changed(bool is_property_changed);

  void Update(InputReceiver& input_receiver,
              const float delta_time) override;

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
};
}  // namespace ho_renderer
#endif  // _HORENDERER_ASSET_CAMERAOBJECT_H_