#include "graphics/rendering_pipeline/pipeline_objects/include/depth_buffer.h"

#include "core/math/include/math_utils.h"
#include "tools/include/debug.h"

namespace ho_renderer {

DepthBuffer::DepthBuffer(const int screen_width, const int screen_height,
                         const float depth_range_min,
                         const float depth_range_max)
    : screen_width_(screen_width),
      screen_height_(screen_height),
      depth_buffer_(new float[screen_width * screen_height]),
      depth_range_min_(depth_range_min),
      depth_range_max_(depth_range_max),
      is_buffer_injected_(false) {
  ASSERT_MSG(screen_width > 0 && screen_height > 0,
             "DepthBuffer::DepthBuffer Error : screen width, height must be "
             "bigger than zero");
}

DepthBuffer::~DepthBuffer() = default;

void DepthBuffer::ResetBuffer() {
  for (int i = 0; i < screen_height_ * screen_width_; i++) {
    depth_buffer_[i] = MathUtils::kFloatMax;
  }
}

float DepthBuffer::GetDepth(const int x, const int y) const {
  ASSERT_MSG(x >= 0 && x < screen_width_,
             "DepthBuffer::GetDepth Error : x coordinate out of range");
  ASSERT_MSG(x >= 0 && x < screen_height_,
             "DepthBuffer::GetDepth Error : y coordinate out of range");
  ASSERT_MSG(depth_buffer_ != nullptr,
             "DepthBuffer::GetDepth Error : depth buffer is null");
  return depth_buffer_[screen_width_ * y + x];
}

void DepthBuffer::SetDepth(const int x, const int y, const float depth) {
  ASSERT_MSG(x >= 0 && x < screen_width_,
             "DepthBuffer::SetDepth Error : x coordinate out of range");
  ASSERT_MSG(x >= 0 && x < screen_height_,
             "DepthBuffer::SetDepth Error : y coordinate out of range");
  ASSERT_MSG(depth_buffer_ != nullptr,
             "DepthBuffer::SetDepth Error : depth buffer is null");
  depth_buffer_[screen_width_ * y + x] = depth;
}

const float* DepthBuffer::GetBuffer() const { return depth_buffer_.get(); }

void DepthBuffer::ImportExternalBuffer(std::unique_ptr<float[]> depth_buffer) {
  ASSERT_MSG(depth_buffer_ != nullptr,
             "DepthBuffer::ImportExternalBuffer Error : imported depth buffer "
             "is null");
  is_buffer_injected_ = true;
  depth_buffer_ = std::move(depth_buffer);
}
}  // namespace ho_renderer