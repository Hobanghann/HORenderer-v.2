#include "math/include/euler_angle.h"

#include "app/include/debug.h"

namespace ho_renderer {
EulerAngle::EulerAngle()
    : yaw_angle_(0.f), roll_angle_(0.f), pitch_angle_(0.f) {}
EulerAngle::EulerAngle(const float pitch, const float yaw, const float roll)
    : pitch_angle_(pitch), yaw_angle_(yaw), roll_angle_(roll) {}
EulerAngle::EulerAngle(const EulerAngle& euler_angle) = default;
EulerAngle& EulerAngle::operator=(const EulerAngle& euler_angle) = default;
EulerAngle::~EulerAngle() = default;

float EulerAngle::yaw_angle() const { return yaw_angle_; }
float EulerAngle::roll_angle() const { return roll_angle_; }
float EulerAngle::pitch_angle() const { return pitch_angle_; }

EulerAngle& EulerAngle::set_yaw_angle(const float angle) {
  yaw_angle_ = angle;
  return *this;
}
EulerAngle& EulerAngle::set_roll_angle(const float angle) {
  roll_angle_ = angle;
  return *this;
}
EulerAngle& EulerAngle::set_pitch_angle(const float angle) {
  pitch_angle_ = angle;
  return *this;
}
}  // namespace ho_renderer