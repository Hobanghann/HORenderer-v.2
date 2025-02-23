#ifndef _HORENDERER_ENGINE_SRGB_H_
#define _HORENDERER_ENGINE_SRGB_H_

// color is represented in 32bit

#include <cstdint>

namespace ho_renderer {
class SRGB {
 public:
  static uint32_t GetLinearColorBit(int alpha, int red, int green, int blue);
  static uint32_t GetGammaCorrectedColorBit(int alpha, int red, int green,
                                            int blue);
  // To ensure that the static color member is initialized before the other
  // static members
  static uint32_t GetLinearWhite();
  static uint32_t GetGammaCorrectedWhite();
  static uint32_t GetLinearBlack();
  static uint32_t GetGammaCorrectedBlack();
  static uint32_t GetLinearRed();
  static uint32_t GetGammeCorrectedRed();
  static uint32_t GetLinearGreen();
  static uint32_t GetGammaCorrectedGreen();
  static uint32_t GetLinearBlue();
  static uint32_t GetGammaCorrectedBlue();
  static uint32_t GetLinearCyan();
  static uint32_t GetGammaCorrectedCyan();
  static uint32_t GetLinearMagenta();
  static uint32_t GetGammaCorrectedMagenta();
  static uint32_t GetLinearYellow();
  static uint32_t GetGammaCorrectedYellow();
  static uint32_t GetLinearOrange();
  static uint32_t GetGammeCorrectedOrange();
  static uint32_t GetLinearPurple();
  static uint32_t GetGammaCorrectedPurple();

 private:
  static const float kINVERSE_GAMMA;
  static const float kINVERSE_MAX;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_ENGINE_SRGB_H_