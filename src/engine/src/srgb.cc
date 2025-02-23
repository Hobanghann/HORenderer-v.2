#include "engine/include/srgb.h"

#include "app/include/debug.h"
#include "math/include/math_utils.h"

namespace ho_renderer {

uint32_t SRGB::GetLinearColorBit(int alpha, int red, int green, int blue) {
  uint32_t color = 0;
  color |= (alpha % 256) << 24;
  color |= (red % 256) << 16;
  color |= (green % 256) << 8;
  color |= (blue % 256);
  return color;
}
uint32_t SRGB::GetGammaCorrectedColorBit(int alpha, int red, int green,
                                         int blue) {
  uint32_t color = 0;
  int gamma_corrected_red = static_cast<int>(
      MathUtils::Pow((red % 256) * kINVERSE_MAX, kINVERSE_GAMMA) * 255);
  int gamma_corrected_green = static_cast<int>(
      MathUtils::Pow((green % 256) * kINVERSE_MAX, kINVERSE_GAMMA) * 255);
  int gamma_corrected_blue = static_cast<int>(
      MathUtils::Pow((blue % 256) * kINVERSE_MAX, kINVERSE_GAMMA) * 255);
  color |= (alpha % 256) << 24;
  color |= gamma_corrected_red << 16;
  color |= gamma_corrected_green << 8;
  color |= gamma_corrected_blue;
  return color;
}
std::uint32_t SRGB::GetLinearWhite() {
  return GetLinearColorBit(255, 255, 255, 255);
}
std::uint32_t SRGB::GetGammaCorrectedWhite() {
  return GetGammaCorrectedColorBit(255, 255, 255, 255);
}
std::uint32_t SRGB::GetLinearBlack() {
  return GetLinearColorBit(255, 255, 0, 0);
}
std::uint32_t SRGB::GetGammaCorrectedBlack() {
  return GetGammaCorrectedColorBit(255, 0, 0, 0);
}
std::uint32_t SRGB::GetLinearRed() { return GetLinearColorBit(255, 255, 0, 0); }
std::uint32_t SRGB::GetGammeCorrectedRed() {
  return GetGammaCorrectedColorBit(255, 255, 0, 0);
}
std::uint32_t SRGB::GetLinearGreen() {
  return GetLinearColorBit(255, 0, 255, 0);
}
std::uint32_t SRGB::GetGammaCorrectedGreen() {
  return GetGammaCorrectedColorBit(255, 0, 255, 0);
}
std::uint32_t SRGB::GetLinearBlue() {
  return GetLinearColorBit(255, 0, 0, 255);
}
std::uint32_t SRGB::GetGammaCorrectedBlue() {
  return GetGammaCorrectedColorBit(255, 0, 0, 255);
}
std::uint32_t SRGB::GetLinearCyan() {
  return GetLinearColorBit(255, 0, 255, 255);
}
std::uint32_t SRGB::GetGammaCorrectedCyan() {
  return GetGammaCorrectedColorBit(255, 0, 255, 255);
}
std::uint32_t SRGB::GetLinearMagenta() {
  return GetLinearColorBit(255, 255, 0, 255);
}
std::uint32_t SRGB::GetGammaCorrectedMagenta() {
  return GetGammaCorrectedColorBit(255, 255, 0, 255);
}
std::uint32_t SRGB::GetLinearYellow() {
  return GetLinearColorBit(255, 255, 255, 0);
}
std::uint32_t SRGB::GetGammaCorrectedYellow() {
  return GetGammaCorrectedColorBit(255, 255, 255, 0);
}
std::uint32_t SRGB::GetLinearOrange() {
  return GetLinearColorBit(255, 255, 165, 0);
}
std::uint32_t SRGB::GetGammeCorrectedOrange() {
  return GetGammaCorrectedColorBit(255, 255, 165, 0);
}
std::uint32_t SRGB::GetLinearPurple() {
  return GetLinearColorBit(255, 128, 0, 128);
}
std::uint32_t SRGB::GetGammaCorrectedPurple() {
  return GetGammaCorrectedColorBit(255, 128, 0, 128);
}

const float ho_renderer::SRGB::kINVERSE_GAMMA = 1.f / 2.2f;
const float ho_renderer::SRGB::kINVERSE_MAX = 1.f / 255.f;

}  // namespace ho_renderer