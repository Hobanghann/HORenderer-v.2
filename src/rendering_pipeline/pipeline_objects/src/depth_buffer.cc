#include "rendering_pipeline/pipeline_objects/include/depth_buffer.h"

#include <cassert>
#include <string>

#include "app/include/debug.h"
#include "math/include/math_utils.h"

namespace ho_renderer {

ho_renderer::DepthBuffer::DepthBuffer(const int screen_width,
                                      const int screen_height,
                                      const float depth_range_min,
                                      const float depth_range_max)
    : screen_width_(screen_width),
      screen_height_(screen_height),
      depth_range_min_(depth_range_min),
      depth_range_max_(depth_range_max),
      is_buffer_injected_(false) {
  depth_buffer_ = new float[screen_width * screen_height];
}

ho_renderer::DepthBuffer::~DepthBuffer() {
  if (!is_buffer_injected_) {
    delete[] depth_buffer_;
  }
}

void ho_renderer::DepthBuffer::ResetBuffer() {
  for (int i = 0; i < screen_height_ * screen_width_; i++) {
    depth_buffer_[i] = MathUtils::kFLOAT_MAX;
  }
}

float DepthBuffer::GetDepth(const int x, const int y) const {
  return depth_buffer_[screen_width_ * y + x];
}

void DepthBuffer::SetDepth(const int x, const int y, const float depth) {
  depth_buffer_[screen_width_ * y + x] = depth;
}

const float* DepthBuffer::GetBuffer() const { return depth_buffer_; }

void DepthBuffer::InjectExternalBuffer(float* depth_buffer) {
  is_buffer_injected_ = true;
  delete depth_buffer_;
  depth_buffer_ = depth_buffer;
}
}  // namespace ho_renderer