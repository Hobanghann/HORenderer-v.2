#include "engine/color/include/linear_rgb.h"

#include "engine/color/include/srgb.h"
#include "math/include/math_utils.h"

namespace ho_renderer {

const LinearRGB LinearRGB::kWHITE = LinearRGB(1.0f, 1.0f, 1.0f, 1.0f);
const LinearRGB LinearRGB::kBLACK = LinearRGB(0.0f, 0.0f, 0.0f, 1.0f);
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

LinearRGB::LinearRGB() : red_(0.f), green_(0.f), blue_(0.f), alpha_(1.f) {}
LinearRGB::LinearRGB(const LinearRGB& rgb) = default;
LinearRGB::LinearRGB(float red, float green, float blue, float alpha)
    : red_(red), green_(green), blue_(blue), alpha_(alpha) {}
LinearRGB::LinearRGB(const SRGB& srgb)
    : red_(MathUtils::Pow(srgb.red(), SRGB::kGAMMA)),
      green_(MathUtils::Pow(srgb.green(), SRGB::kGAMMA)),
      blue_(MathUtils::Pow(srgb.blue(), SRGB::kGAMMA)),
      alpha_(srgb.alpha()) {}
LinearRGB::LinearRGB(const std::uint32_t argb32) {
  std::uint32_t r_bit = (argb32 & kRED_MASK) >> 16;
  std::uint32_t g_bit = (argb32 & kGREEN_MASK) >> 8;
  std::uint32_t b_bit = (argb32 & kBLUE_MASK);
  std::uint32_t a_bit = (argb32 & kALPHA_MASK) >> 24;

  red_ = static_cast<float>(r_bit) * kINVERSE_MAX32;
  green_ = static_cast<float>(g_bit) * kINVERSE_MAX32;
  blue_ = static_cast<float>(b_bit) * kINVERSE_MAX32;
  alpha_ = static_cast<float>(a_bit) * kINVERSE_MAX32;
}
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
LinearRGB LinearRGB::operator+(const LinearRGB& rgb) const {
  return LinearRGB(red_ + rgb.red_, green_ + rgb.green_, blue_ + rgb.blue_,
                   alpha_ + rgb.alpha_);
}
LinearRGB& LinearRGB::operator+=(const LinearRGB& rgb) {
  red_ += rgb.red_;
  green_ += rgb.green_;
  blue_ += rgb.blue_;
  alpha_ += rgb.alpha_;
  return *this;
}
LinearRGB LinearRGB::operator-(const LinearRGB& rgb) const {
  return LinearRGB(red_ - rgb.red_, green_ - rgb.green_, blue_ - rgb.blue_,
                   alpha_ - rgb.alpha_);
}
LinearRGB& LinearRGB::operator-=(const LinearRGB& rgb) {
  red_ -= rgb.red_;
  green_ -= rgb.green_;
  blue_ -= rgb.blue_;
  alpha_ -= rgb.alpha_;
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
  return LinearRGB(red_ / rgb.red_, green_ / rgb.green_, blue_ / rgb.blue_,
                   alpha_ / rgb.alpha_);
}
LinearRGB& LinearRGB::operator/=(const LinearRGB& rgb) {
  red_ /= rgb.red_;
  green_ /= rgb.green_;
  blue_ /= rgb.blue_;
  alpha_ /= rgb.alpha_;
  return *this;
}

std::uint32_t LinearRGB::ToARGB32() const {
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
}  // namespace ho_renderer
