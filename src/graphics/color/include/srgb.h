#ifndef _HORENDERER_SRGB_H_
#define _HORENDERER_SRGB_H_

// color is represented in 32bit

#include <cstdint>

#include "core/math/include/vector4.h"

namespace ho_renderer {
class LinearRGB;
class SRGB {
 public:
  static constexpr float kGAMMA = 2.2f;
  static const SRGB kWhite;
  static const SRGB kBlack;
  static const SRGB kRED;
  static const SRGB kGREEN;
  static const SRGB kBLUE;
  static const SRGB kCYAN;
  static const SRGB kMAGENTA;
  static const SRGB kYELLOW;
  static const SRGB kORANGE;
  static const SRGB kPURPLE;
  static const SRGB kGRAY;
  static const SRGB kDARK_GRAY;
  static const SRGB kLIGHT_GRAY;
  static const SRGB kBROWN;
  static const SRGB kPINK;

  SRGB();
  SRGB(const SRGB&);
  SRGB(float red, float green, float blue, float alpha = 1.f);
  explicit SRGB(const LinearRGB&);
  explicit SRGB(const std::uint32_t argb32);
  explicit SRGB(const Vector4& v);
  SRGB& operator=(const SRGB&);
  ~SRGB();

  float red() const;
  float green() const;
  float blue() const;
  float alpha() const;

  SRGB& set_alpha(float alpha);
  SRGB& set_red(float red);
  SRGB& set_green(float green);
  SRGB& set_blue(float blue);

  bool operator==(const SRGB&) const;
  bool operator!=(const SRGB&) const;

  std::uint32_t ToRGBA32() const;
  std::uint32_t ToBGRA32() const;
  Vector4 ToVector4() const;

 private:
  static constexpr float kINVERSE_GAMMA = 1.f / kGAMMA;
  static constexpr float kMAX32 = 255.9999f;
  static constexpr float kINVERSE_MAX32 = 1.f / 255.f;
  static constexpr std::uint32_t kRED_MASK = 0x000000FF;
  static constexpr std::uint32_t kGREEN_MASK = 0x0000FF00;
  static constexpr std::uint32_t kBLUE_MASK = 0x00FF0000;
  static constexpr std::uint32_t kALPHA_MASK = 0xFF000000;

  float red_;
  float blue_;
  float green_;
  float alpha_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_SRGB_H_