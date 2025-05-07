#include "core/math/include/euler_angle.h"

#include <string>
#include <vector>

namespace ho_renderer {
EulerAngle::EulerAngle()
    : yaw_angle_(0.f), roll_angle_(0.f), pitch_angle_(0.f) {}
EulerAngle::EulerAngle(float pitch, float yaw, float roll)
    : pitch_angle_(pitch), yaw_angle_(yaw), roll_angle_(roll) {}
EulerAngle::EulerAngle(const EulerAngle& euler_angle) = default;
EulerAngle& EulerAngle::operator=(const EulerAngle& euler_angle) = default;
EulerAngle::~EulerAngle() = default;

float EulerAngle::yaw_angle() const { return yaw_angle_; }
float EulerAngle::roll_angle() const { return roll_angle_; }
float EulerAngle::pitch_angle() const { return pitch_angle_; }

EulerAngle& EulerAngle::set_yaw_angle(float angle) {
  yaw_angle_ = angle;
  return *this;
}
EulerAngle& EulerAngle::set_roll_angle(float angle) {
  roll_angle_ = angle;
  return *this;
}
EulerAngle& EulerAngle::set_pitch_angle(float angle) {
  pitch_angle_ = angle;
  return *this;
}

std::string EulerAngle::ToString() const {
  char buf[100];
  snprintf(buf, sizeof(buf), "pitch : %.3f, yaw : %.3f, roll : %.3f",
           pitch_angle_, yaw_angle_, roll_angle_);
  return buf;
}
}  // namespace ho_renderer