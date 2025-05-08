#include "graphics/rendering_pipeline/pipeline_objects/include/frame_buffer.h"

#include "tools/include/debug.h"
namespace ho_renderer {

FrameBuffer::FrameBuffer() : color_buffer_(nullptr), depth_buffer_(nullptr) {}
FrameBuffer::~FrameBuffer() = default;

FrameBuffer& FrameBuffer::CreateColorBuffer(
    const int screen_width, const int screen_height,
    std::uint32_t background_color_bit) {
  color_buffer_ = std::make_unique<ColorBuffer>(screen_width, screen_height,
                                                background_color_bit);
  return *this;
}
FrameBuffer& FrameBuffer::CreateDepthBuffer(const int screen_width,
                                            const int screen_height,
                                            const float depth_range_min,
                                            const float depth_range_max) {
  depth_buffer_ = std::make_unique<DepthBuffer>(
      screen_width, screen_height, depth_range_min, depth_range_max);
  return *this;
}

ColorBuffer* FrameBuffer::GetColorBuffer() const {
  ASSERT_MSG(color_buffer_ != nullptr,
             "FrameBuffer::GetColorBuffer Error : color buffer is not created "
             "(color buffer is null)");
  return color_buffer_.get();
}
DepthBuffer* FrameBuffer::GetDepthBuffer() const {
  ASSERT_MSG(depth_buffer_ != nullptr,
             "FrameBuffer::GetDepthBuffer Error : depth buffer is not created "
             "(depth buffer is null)");
  return depth_buffer_.get();
}

FrameBuffer& FrameBuffer::ChangeColorBuffer(
    const int screen_width, const int screen_height,
    std::uint32_t background_color_bit) {
  color_buffer_ = std::make_unique<ColorBuffer>(screen_width, screen_height,
                                                background_color_bit);
  return *this;
}
FrameBuffer& FrameBuffer::ChangeDepthBuffer(const int screen_width,
                                            const int screen_height,
                                            const float depth_range_min,
                                            const float depth_range_max) {
  depth_buffer_ = std::make_unique<DepthBuffer>(
      screen_width, screen_height, depth_range_min, depth_range_max);
  return *this;
}

void FrameBuffer::ResetBuffers() {
  ASSERT_MSG(color_buffer_ != nullptr,
             "FrameBuffer::ResetBuffers Error : color buffer is not created "
             "(color buffer is null)");
  ASSERT_MSG(depth_buffer_ != nullptr,
             "FrameBuffer::ResetBuffers Error : depth buffer is not created "
             "(depth buffer is null)");
  color_buffer_->ResetBuffer();
  depth_buffer_->ResetBuffer();
}
}  // namespace ho_renderer