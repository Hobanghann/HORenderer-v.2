#ifndef _HORENDERER_EULER_ANGLE_H_
#define _HORENDERER_EULER_ANGLE_H_

#include <string>

namespace ho_renderer {
class EulerAngle {
 public:
  EulerAngle();
  EulerAngle(float pitch, float yaw, float roll);
  EulerAngle(const EulerAngle& euler_angle);
  EulerAngle& operator=(const EulerAngle& euler_angle);
  ~EulerAngle();

  float pitch_angle() const;
  float yaw_angle() const;
  float roll_angle() const;

  EulerAngle& set_pitch_angle(float angle);
  EulerAngle& set_yaw_angle(float angle);
  EulerAngle& set_roll_angle(float angle);

  std::string ToString() const;

 private:
  float pitch_angle_;  // x axis
  float yaw_angle_;    // y axis
  float roll_angle_;   // z axis
};
}  // namespace ho_renderer

#endif  // _HORENDERER_EULER_ANGLE_H_