#include "rendering_pipeline/pipeline_objects/include/frame_buffer.h"

#include "app/include/debug.h"

namespace ho_renderer {

FrameBuffer::FrameBuffer() : color_buffer_(nullptr), depth_buffer_(nullptr) {}
FrameBuffer::~FrameBuffer() = default;

FrameBuffer& FrameBuffer::CreateColorBuffer(
    const int screen_width, const int screen_height,
    std::uint32_t background_color_bit) {
  color_buffer_ = std::unique_ptr<ColorBuffer>(
      new ColorBuffer(screen_width, screen_height, background_color_bit));
  return *this;
}
FrameBuffer& FrameBuffer::CreateDepthBuffer(const int screen_width,
                                            const int screen_height,
                                            const float depth_range_min,
                                            const float depth_range_max) {
  depth_buffer_ = std::unique_ptr<DepthBuffer>(new DepthBuffer(
      screen_width, screen_height, depth_range_min, depth_range_max));
  return *this;
}

ColorBuffer& FrameBuffer::GetColorBuffer() const {
  if (color_buffer_ == nullptr) {
    // handling exception
  }
  return *color_buffer_;
}
DepthBuffer& FrameBuffer::GetDepthBuffer() const {
  if (depth_buffer_ == nullptr) {
    // handling exception
  }
  return *depth_buffer_;
}

FrameBuffer& FrameBuffer::ChangeColorBuffer(
    const int screen_width, const int screen_height,
    std::uint32_t background_color_bit) {
  color_buffer_ = std::unique_ptr<ColorBuffer>(
      new ColorBuffer(screen_width, screen_height, background_color_bit));
  return *this;
}
FrameBuffer& FrameBuffer::ChangeDepthBuffer(const int screen_width,
                                            const int screen_height,
                                            const float depth_range_min,
                                            const float depth_range_max) {
  depth_buffer_ = std::unique_ptr<DepthBuffer>(new DepthBuffer(
      screen_width, screen_height, depth_range_min, depth_range_max));
  return *this;
}

void FrameBuffer::ResetBuffers() {
  color_buffer_->ResetBuffer();
  depth_buffer_->ResetBuffer();
}
}  // namespace ho_renderer