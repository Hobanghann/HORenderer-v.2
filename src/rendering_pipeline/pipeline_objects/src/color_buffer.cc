#include "rendering_pipeline/pipeline_objects/include/color_buffer.h"

#include <cassert>
#include <string>

#include "app/include/debug.h"

namespace ho_renderer {

ColorBuffer::ColorBuffer(const int screen_width, const int screen_height,
                         std::uint32_t background_color_bit)
    : screen_width_(screen_width),
      screen_height_(screen_height),
      background_color_bit_(background_color_bit),
      is_buffer_injected_(false) {
  color_buffer_ = new uint32_t[screen_width_ * screen_height_];
  ResetBuffer();
}
ColorBuffer::~ColorBuffer() {
  if (!is_buffer_injected_) {
    delete[] color_buffer_;
  }
}

std::uint32_t ColorBuffer::GetColor(const int x, const int y) const {
  return color_buffer_[screen_width_ * y + x];
}

void ColorBuffer::SetColor(const int x, const int y,
                           const std::uint32_t color_bit) {
  color_buffer_[screen_width_ * y + x] = color_bit;
}

const std::uint32_t* ColorBuffer::GetBuffer() const { return color_buffer_; }

void ColorBuffer::InjectExternalBuffer(std::uint32_t* color_buffer) {
  is_buffer_injected_ = true;
  delete color_buffer_;
  color_buffer_ = color_buffer;
}

void ColorBuffer::ResetBuffer() {
  for (int i = 0; i < screen_height_ * screen_width_; i++) {
    color_buffer_[i] = background_color_bit_;
  }
}

}  // namespace ho_renderer