#include "graphics/color/include/srgb.h"

#include <cstdint>

#include "core/math/include/math_utils.h"
#include "graphics/color/include/linear_rgb.h"

namespace ho_renderer {
const SRGB SRGB::kWhite = SRGB(1.0f, 1.0f, 1.0f, 1.0f);
const SRGB SRGB::kBlack = SRGB(0.0f, 0.0f, 0.0f, 1.0f);
const SRGB SRGB::kRED = SRGB(1.0f, 0.0f, 0.0f, 1.0f);
const SRGB SRGB::kGREEN = SRGB(0.0f, 1.0f, 0.0f, 1.0f);
const SRGB SRGB::kBLUE = SRGB(0.0f, 0.0f, 1.0f, 1.0f);
const SRGB SRGB::kCYAN = SRGB(0.0f, 1.0f, 1.0f, 1.0f);
const SRGB SRGB::kMAGENTA = SRGB(1.0f, 0.0f, 1.0f, 1.0f);
const SRGB SRGB::kYELLOW = SRGB(1.0f, 1.0f, 0.0f, 1.0f);
const SRGB SRGB::kORANGE = SRGB(1.0f, 0.5f, 0.0f, 1.0f);
const SRGB SRGB::kPURPLE = SRGB(0.5f, 0.0f, 0.5f, 1.0f);
const SRGB SRGB::kGRAY = SRGB(0.5f, 0.5f, 0.5f, 1.0f);
const SRGB SRGB::kDARK_GRAY = SRGB(0.25f, 0.25f, 0.25f, 1.0f);
const SRGB SRGB::kLIGHT_GRAY = SRGB(0.75f, 0.75f, 0.75f, 1.0f);
const SRGB SRGB::kBROWN = SRGB(0.6f, 0.3f, 0.1f, 1.0f);
const SRGB SRGB::kPINK = SRGB(1.0f, 0.75f, 0.8f, 1.0f);

SRGB::SRGB() : red_(0.f), green_(0.f), blue_(0.f), alpha_(1.f) {}
SRGB::SRGB(const SRGB& rgb) = default;
SRGB::SRGB(float red, float green, float blue, float alpha)
    : red_(red), green_(green), blue_(blue), alpha_(alpha) {}
SRGB::SRGB(const LinearRGB& lrgb)
    : red_(MathUtils::Powf(lrgb.red(), kINVERSE_GAMMA)),
      green_(MathUtils::Powf(lrgb.green(), kINVERSE_GAMMA)),
      blue_(MathUtils::Powf(lrgb.blue(), kINVERSE_GAMMA)),
      alpha_(lrgb.alpha()) {}
SRGB::SRGB(const std::uint32_t argb32) {
  std::uint32_t r_bit = (argb32 & kRED_MASK);
  std::uint32_t g_bit = (argb32 & kGREEN_MASK) >> 8;
  std::uint32_t b_bit = (argb32 & kBLUE_MASK) >> 16;
  std::uint32_t a_bit = (argb32 & kALPHA_MASK) >> 24;

  red_ = static_cast<float>(r_bit) * kINVERSE_MAX32;
  green_ = static_cast<float>(g_bit) * kINVERSE_MAX32;
  blue_ = static_cast<float>(b_bit) * kINVERSE_MAX32;
  alpha_ = static_cast<float>(a_bit) * kINVERSE_MAX32;
}
SRGB::SRGB(const Vector4& v)
    : red_(v.x()), green_(v.y()), blue_(v.z()), alpha_(v.w()) {}
SRGB& SRGB::operator=(const SRGB&) = default;
SRGB::~SRGB() = default;

float SRGB::red() const { return red_; }
float SRGB::green() const { return green_; }
float SRGB::blue() const { return blue_; }
float SRGB::alpha() const { return alpha_; }

SRGB& SRGB::set_alpha(float alpha) {
  alpha_ = alpha;
  return *this;
}
SRGB& SRGB::set_red(float red) {
  red_ = red;
  return *this;
}
SRGB& SRGB::set_green(float green) {
  green_ = green;
  return *this;
}
SRGB& SRGB::set_blue(float blue) {
  blue_ = blue;
  return *this;
}

bool SRGB::operator==(const SRGB& rgb) const {
  return MathUtils::IsEqual(red_, rgb.red_) &&
         MathUtils::IsEqual(green_, rgb.green_) &&
         MathUtils::IsEqual(blue_, rgb.blue_) &&
         MathUtils::IsEqual(alpha_, rgb.alpha_);
}
bool SRGB::operator!=(const SRGB& rgb) const { return !(*this == rgb); }

std::uint32_t SRGB::ToRGBA32() const {
  std::uint32_t r_bit =
      static_cast<std::uint32_t>(MathUtils::Clamp(0.f, 1.f, red_) * kMAX32);
  std::uint32_t g_bit =
      static_cast<std::uint32_t>(MathUtils::Clamp(0.f, 1.f, green_) * kMAX32)
      << 8;
  std::uint32_t b_bit =
      static_cast<std::uint32_t>(MathUtils::Clamp(0.f, 1.f, blue_) * kMAX32)
      << 16;
  std::uint32_t a_bit =
      static_cast<std::uint32_t>(MathUtils::Clamp(0.f, 1.f, alpha_) * kMAX32)
      << 24;
  return a_bit | b_bit | g_bit | r_bit;
}

std::uint32_t SRGB::ToBGRA32() const {
  std::uint32_t a_bit = static_cast<std::uint32_t>(alpha_ * kMAX32) << 24;
  std::uint32_t r_bit = static_cast<std::uint32_t>(red_ * kMAX32) << 16;
  std::uint32_t g_bit = static_cast<std::uint32_t>(green_ * kMAX32) << 8;
  std::uint32_t b_bit = static_cast<std::uint32_t>(blue_ * kMAX32);
  return a_bit | r_bit | g_bit | b_bit;
}

Vector4 SRGB::ToVector4() const { return Vector4(red_, blue_, green_, alpha_); }
}  // namespace ho_renderer