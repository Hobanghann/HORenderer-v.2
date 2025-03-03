#ifndef _HORENDERER_ENGINE_COLOR_LINEAR_RGB_H_
#define _HORENDERER_ENGINE_COLOR_LINEAR_RGB_H_

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

  std::uint32_t ToARGB32() const;

 private:
  static constexpr float kMAX32 = 255.9999;
  static constexpr float kINVERSE_MAX32 = 1.f / 255.f;
  static constexpr std::uint32_t kALPHA_MASK = 0b11111111 << 24;
  static constexpr std::uint32_t kRED_MASK = 0b11111111 << 16;
  static constexpr std::uint32_t kGREEN_MASK = 0b11111111 << 8;
  static constexpr std::uint32_t kBLUE_MASK = 0b11111111;

  float red_;
  float blue_;
  float green_;
  float alpha_;
};

inline LinearRGB operator*(const LinearRGB& rgb, const float scalar) {
  return LinearRGB(rgb.red() * scalar, rgb.green() * scalar,
                   rgb.blue() * scalar, rgb.alpha());
}
inline LinearRGB operator*(const float scalar, const LinearRGB& rgb) {
  return rgb * scalar;
}
}  // namespace ho_renderer

#endif  // _HORENDERER_ENGINE_COLOR_LINEAR_RGB_H_