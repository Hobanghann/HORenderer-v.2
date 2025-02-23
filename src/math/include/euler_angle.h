#ifndef _HORENDERER_MATH_EULERANGLE_H_
#define _HORENDERER_MATH_EULERANGLE_H_

namespace ho_renderer {
class EulerAngle {
 public:
  EulerAngle();
  EulerAngle(const float pitch, const float yaw, const float roll);
  EulerAngle(const EulerAngle& euler_angle);
  EulerAngle& operator=(const EulerAngle& euler_angle);
  ~EulerAngle();

  float pitch_angle() const;
  float yaw_angle() const;
  float roll_angle() const;

  EulerAngle& set_pitch_angle(const float angle);
  EulerAngle& set_yaw_angle(const float angle);
  EulerAngle& set_roll_angle(const float angle);

 private:
  float pitch_angle_;  // x axis
  float yaw_angle_;    // y axis
  float roll_angle_;   // z axis
};
}  // namespace ho_renderer

#endif  // _HORENDERER_MATH_EULERANGLE_H_