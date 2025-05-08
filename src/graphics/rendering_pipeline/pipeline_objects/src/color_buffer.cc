#include "graphics/rendering_pipeline/pipeline_objects/include/color_buffer.h"

#include <cstdint>
#include <memory>
#include <string>

#include "tools/include/debug.h"

namespace ho_renderer {

ColorBuffer::ColorBuffer(const int screen_width, const int screen_height,
                         std::uint32_t background_color_bit)
    : screen_width_(screen_width),
      screen_height_(screen_height),
      background_color_bit_(background_color_bit),
      color_buffer_(new uint32_t[screen_width * screen_height]),
      is_buffer_injected_(false) {
  ASSERT_MSG(screen_width > 0 && screen_height > 0,
             "ColorBuffer::ColorBuffer Error : screen width, height must be "
             "bigger than zero");
  ResetBuffer();
}
ColorBuffer::~ColorBuffer() = default;

std::uint32_t ColorBuffer::GetColor(const int x, const int y) const {
  ASSERT_MSG(x >= 0 && x < screen_width_,
             "ColorBuffer::GetColor Error : x coordinate out of range");
  ASSERT_MSG(x >= 0 && x < screen_height_,
             "ColorBuffer::GetColor Error : y coordinate out of range");
  ASSERT_MSG(color_buffer_ != nullptr,
             "ColorBuffer::GetColor Error : color buffer is null");
  return color_buffer_[screen_width_ * y + x];
}

void ColorBuffer::SetColor(const int x, const int y,
                           const std::uint32_t color_bit) {
  ASSERT_MSG(x >= 0 && x < screen_width_,
             "ColorBuffer::SetColor Error : x coordinate out of range");
  ASSERT_MSG(x >= 0 && x < screen_height_,
             "ColorBuffer::SetColor Error : y coordinate out of range");
  ASSERT_MSG(color_buffer_ != nullptr,
             "ColorBuffer::SetColor Error : color buffer is null");
  color_buffer_[screen_width_ * y + x] = color_bit;
}

const std::uint32_t* ColorBuffer::GetBuffer() const {
  return color_buffer_.get();
}

void ColorBuffer::ImportExternalBuffer(
    std::unique_ptr<std::uint32_t[]> color_buffer) {
  ASSERT_MSG(color_buffer_ != nullptr,
             "ColorBuffer::ImportExternalBuffer Error : imported color buffer "
             "is null");
  is_buffer_injected_ = true;
  color_buffer_ = std::move(color_buffer);
}

void ColorBuffer::ResetBuffer() {
  for (int i = 0; i < screen_height_ * screen_width_; i++) {
    color_buffer_[i] = background_color_bit_;
  }
}

}  // namespace ho_renderer