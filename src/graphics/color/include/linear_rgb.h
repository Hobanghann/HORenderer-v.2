#ifndef _HORENDERER_LINEAR_RGB_H_
#define _HORENDERER_LINEAR_RGB_H_

#include <cstdint>

namespace ho_renderer {
class SRGB;
class LinearRGB {
 public:
  static const LinearRGB kWHITE;
  static const LinearRGB kBLACK;
  static const LinearRGB kRED;
  static const LinearRGB kGREEN;
  static const LinearRGB kBLUE;
  static const LinearRGB kCYAN;
  static const LinearRGB kMAGENTA;
  static const LinearRGB kYELLOW;
  static const LinearRGB kORANGE;
  static const LinearRGB kPURPLE;
  static const LinearRGB kGRAY;
  static const LinearRGB kDARK_GRAY;
  static const LinearRGB kLIGHT_GRAY;
  static const LinearRGB kBROWN;
  static const LinearRGB kPINK;
  static const LinearRGB kKHAKI;
  static const LinearRGB kDARK_GREEN;
  static const LinearRGB kOLIVE;
  static const LinearRGB kLIME;
  static const LinearRGB kTEAL;
  static const LinearRGB kVIOLET;
  static const LinearRGB kINDIGO;
  static const LinearRGB kGOLD;
  static const LinearRGB kSILVER;

  LinearRGB();
  LinearRGB(const LinearRGB&);
  LinearRGB(float red, float green, float blue, float alpha = 1.f);
  explicit LinearRGB(const SRGB&);
  explicit LinearRGB(const std::uint32_t argb32);
  LinearRGB& operator=(const LinearRGB&);
  ~LinearRGB();

  float red() const;
  float green() const;
  float blue() const;
  float alpha() const;

  LinearRGB& set_alpha(float alpha);
  LinearRGB& set_red(float red);
  LinearRGB& set_green(float green);
  LinearRGB& set_blue(float blue);

  bool operator==(const LinearRGB&) const;
  bool operator!=(const LinearRGB&) const;
  LinearRGB operator+(const LinearRGB&) const;
  LinearRGB& operator+=(const LinearRGB&);
  LinearRGB operator-(const LinearRGB&) const;
  LinearRGB& operator-=(const LinearRGB&);
  LinearRGB operator*(const LinearRGB&) const;
  LinearRGB& operator*=(const LinearRGB&);
  LinearRGB operator/(const LinearRGB&) const;
  LinearRGB& operator/=(const LinearRGB&);

  float GetLuminance(float r_weight, float g_weight, float b_weight) const;
  std::uint32_t ToRGBA32() const;
  std::uint32_t ToBGRA32() const;

 private:
  static constexpr float kMAX32 = 255.9999;
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

inline LinearRGB operator*(const LinearRGB& rgb, float scalar) {
  return LinearRGB(rgb.red() * scalar, rgb.green() * scalar,
                   rgb.blue() * scalar, rgb.alpha());
}
inline LinearRGB operator*(float scalar, const LinearRGB& rgb) {
  return rgb * scalar;
}
}  // namespace ho_renderer

#endif  // _HORENDERER_LINEAR_RGB_H_