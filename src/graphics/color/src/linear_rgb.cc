#include "graphics/color/include/linear_rgb.h"

#include <cstdint>

#include "core/math/include/math_utils.h"
#include "graphics/color/include/srgb.h"
#include "tools/include/debug.h"

namespace ho_renderer {

const LinearRGB LinearRGB::kWhite = LinearRGB(1.0f, 1.0f, 1.0f, 1.0f);
const LinearRGB LinearRGB::kBlack = LinearRGB(0.0f, 0.0f, 0.0f, 1.0f);
const LinearRGB LinearRGB::kRED = LinearRGB(1.0f, 0.0f, 0.0f, 1.0f);
const LinearRGB LinearRGB::kGREEN = LinearRGB(0.0f, 1.0f, 0.0f, 1.0f);
const LinearRGB LinearRGB::kBLUE = LinearRGB(0.0f, 0.0f, 1.0f, 1.0f);

const LinearRGB LinearRGB::kCYAN = LinearRGB(0.0f, 1.0f, 1.0f, 1.0f);
const LinearRGB LinearRGB::kMAGENTA = LinearRGB(1.0f, 0.0f, 1.0f, 1.0f);
const LinearRGB LinearRGB::kYELLOW = LinearRGB(1.0f, 1.0f, 0.0f, 1.0f);
const LinearRGB LinearRGB::kORANGE = LinearRGB(1.0f, 0.5f, 0.0f, 1.0f);
const LinearRGB LinearRGB::kPURPLE = LinearRGB(0.5f, 0.0f, 0.5f, 1.0f);

const LinearRGB LinearRGB::kGRAY = LinearRGB(0.5f, 0.5f, 0.5f, 1.0f);
const LinearRGB LinearRGB::kDARK_GRAY = LinearRGB(0.25f, 0.25f, 0.25f, 1.0f);
const LinearRGB LinearRGB::kLIGHT_GRAY = LinearRGB(0.75f, 0.75f, 0.75f, 1.0f);

const LinearRGB LinearRGB::kBROWN = LinearRGB(0.6f, 0.3f, 0.1f, 1.0f);
const LinearRGB LinearRGB::kPINK = LinearRGB(1.0f, 0.75f, 0.8f, 1.0f);
const LinearRGB LinearRGB::kKHAKI = LinearRGB(0.4f, 0.4f, 0.2f, 1.0f);
const LinearRGB LinearRGB::kDARK_GREEN = LinearRGB(0.13f, 0.55f, 0.13f, 1.0f);
const LinearRGB LinearRGB::kOLIVE = LinearRGB(0.5f, 0.5f, 0.0f, 1.0f);
const LinearRGB LinearRGB::kLIME = LinearRGB(0.75f, 1.0f, 0.0f, 1.0f);
const LinearRGB LinearRGB::kTEAL = LinearRGB(0.0f, 0.5f, 0.5f, 1.0f);
const LinearRGB LinearRGB::kVIOLET = LinearRGB(0.54f, 0.17f, 0.89f, 1.0f);
const LinearRGB LinearRGB::kINDIGO = LinearRGB(0.29f, 0.0f, 0.51f, 1.0f);
const LinearRGB LinearRGB::kGOLD = LinearRGB(1.0f, 0.84f, 0.0f, 1.0f);
const LinearRGB LinearRGB::kSILVER = LinearRGB(0.75f, 0.75f, 0.75f, 1.0f);

LinearRGB::LinearRGB() : red_(0.f), green_(0.f), blue_(0.f), alpha_(1.f) {}
LinearRGB::LinearRGB(const LinearRGB& rgb) = default;
LinearRGB::LinearRGB(float red, float green, float blue, float alpha)
    : red_(red), green_(green), blue_(blue), alpha_(alpha) {}
LinearRGB::LinearRGB(const SRGB& srgb)
    : red_(MathUtils::Powf(srgb.red(), SRGB::kGAMMA)),
      green_(MathUtils::Powf(srgb.green(), SRGB::kGAMMA)),
      blue_(MathUtils::Powf(srgb.blue(), SRGB::kGAMMA)),
      alpha_(srgb.alpha()) {}
LinearRGB::LinearRGB(const std::uint32_t argb32) {
  std::uint32_t r_bit = (argb32 & kRED_MASK);
  std::uint32_t g_bit = (argb32 & kGREEN_MASK) >> 8;
  std::uint32_t b_bit = (argb32 & kBLUE_MASK) >> 16;
  std::uint32_t a_bit = (argb32 & kALPHA_MASK) >> 24;

  red_ = static_cast<float>(r_bit) * kINVERSE_MAX32;
  green_ = static_cast<float>(g_bit) * kINVERSE_MAX32;
  blue_ = static_cast<float>(b_bit) * kINVERSE_MAX32;
  alpha_ = static_cast<float>(a_bit) * kINVERSE_MAX32;
}
LinearRGB::LinearRGB(const Vector4& v)
    : red_(v.x()), green_(v.y()), blue_(v.z()), alpha_(v.w()) {}
LinearRGB& LinearRGB::operator=(const LinearRGB&) = default;
LinearRGB::~LinearRGB() = default;

float LinearRGB::red() const { return red_; }
float LinearRGB::green() const { return green_; }
float LinearRGB::blue() const { return blue_; }
float LinearRGB::alpha() const { return alpha_; }

LinearRGB& LinearRGB::set_alpha(float alpha) {
  alpha_ = alpha;
  return *this;
}
LinearRGB& LinearRGB::set_red(float red) {
  red_ = red;
  return *this;
}
LinearRGB& LinearRGB::set_green(float green) {
  green_ = green;
  return *this;
}
LinearRGB& LinearRGB::set_blue(float blue) {
  blue_ = blue;
  return *this;
}

bool LinearRGB::operator==(const LinearRGB& rgb) const {
  return MathUtils::IsEqual(red_, rgb.red_) &&
         MathUtils::IsEqual(green_, rgb.green_) &&
         MathUtils::IsEqual(blue_, rgb.blue_) &&
         MathUtils::IsEqual(alpha_, rgb.alpha_);
}
bool LinearRGB::operator!=(const LinearRGB& rgb) const {
  return !(*this == rgb);
}
// use premultiplied alpha
LinearRGB LinearRGB::operator+(const LinearRGB& rgb) const {
  return LinearRGB(red_ + rgb.red_, green_ + rgb.green_, blue_ + rgb.blue_,
                   alpha_ + rgb.alpha_ - alpha_ * rgb.alpha_);
}
LinearRGB& LinearRGB::operator+=(const LinearRGB& rgb) {
  red_ += rgb.red_;
  green_ += rgb.green_;
  blue_ += rgb.blue_;
  alpha_ = alpha_ + rgb.alpha_ - alpha_ * rgb.alpha_;
  return *this;
}
LinearRGB LinearRGB::operator-(const LinearRGB& rgb) const {
  return LinearRGB(red_ - rgb.red_, green_ - rgb.green_, blue_ - rgb.blue_,
                   alpha_ - rgb.alpha_ + alpha_ * rgb.alpha_);
}
LinearRGB& LinearRGB::operator-=(const LinearRGB& rgb) {
  red_ -= rgb.red_;
  green_ -= rgb.green_;
  blue_ -= rgb.blue_;
  alpha_ = alpha_ - rgb.alpha_ + alpha_ * rgb.alpha_;
  return *this;
}
LinearRGB LinearRGB::operator*(const LinearRGB& rgb) const {
  return LinearRGB(red_ * rgb.red_, green_ * rgb.green_, blue_ * rgb.blue_,
                   alpha_ * rgb.alpha_);
}
LinearRGB& LinearRGB::operator*=(const LinearRGB& rgb) {
  red_ *= rgb.red_;
  green_ *= rgb.green_;
  blue_ *= rgb.blue_;
  alpha_ *= rgb.alpha_;
  return *this;
}
LinearRGB LinearRGB::operator/(const LinearRGB& rgb) const {
  ASSERT_MSG(rgb.red_ != 0.f,
             "LinearRGB::operator/ Error: red component is zero");
  ASSERT_MSG(rgb.green_ != 0.f,
             "LinearRGB::operator/ Error: green component is zero");
  ASSERT_MSG(rgb.blue_ != 0.f,
             "LinearRGB::operator/ Error: blue component is zero");
  ASSERT_MSG(rgb.alpha_ != 0.f,
             "LinearRGB::operator/ Error: alpha component is zero");

  return LinearRGB(red_ / rgb.red_, green_ / rgb.green_, blue_ / rgb.blue_,
                   alpha_ / rgb.alpha_);
}
LinearRGB& LinearRGB::operator/=(const LinearRGB& rgb) {
  ASSERT_MSG(rgb.red_ != 0.f,
             "LinearRGB::operator/ Error: red component is zero");
  ASSERT_MSG(rgb.green_ != 0.f,
             "LinearRGB::operator/ Error: green component is zero");
  ASSERT_MSG(rgb.blue_ != 0.f,
             "LinearRGB::operator/ Error: blue component is zero");
  ASSERT_MSG(rgb.alpha_ != 0.f,
             "LinearRGB::operator/ Error: alpha component is zero");

  red_ /= rgb.red_;
  green_ /= rgb.green_;
  blue_ /= rgb.blue_;
  alpha_ /= rgb.alpha_;
  return *this;
}

float LinearRGB::GetLuminance(float r_weight, float g_weight,
                              float b_weight) const {
  return r_weight * red_ + g_weight * green_, b_weight * blue_;
}

std::uint32_t LinearRGB::ToRGBA32() const {
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

std::uint32_t LinearRGB::ToBGRA32() const {
  std::uint32_t a_bit =
      static_cast<std::uint32_t>(MathUtils::Clamp(0.f, 1.f, alpha_) * kMAX32)
      << 24;
  std::uint32_t r_bit =
      static_cast<std::uint32_t>(MathUtils::Clamp(0.f, 1.f, red_) * kMAX32)
      << 16;
  std::uint32_t g_bit =
      static_cast<std::uint32_t>(MathUtils::Clamp(0.f, 1.f, green_) * kMAX32)
      << 8;
  std::uint32_t b_bit =
      static_cast<std::uint32_t>(MathUtils::Clamp(0.f, 1.f, blue_) * kMAX32);
  return a_bit | r_bit | g_bit | b_bit;
}

Vector4 LinearRGB::ToVector4() const {
  return Vector4(red_, blue_, green_, alpha_);
}
}  // namespace ho_renderer
