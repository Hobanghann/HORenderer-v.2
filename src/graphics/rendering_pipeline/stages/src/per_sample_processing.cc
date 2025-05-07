#include "graphics/rendering_pipeline/stages/include/per_sample_processing.h"

namespace ho_renderer {

PerSampleProcessing::PerSampleProcessing() = default;
PerSampleProcessing::~PerSampleProcessing() = default;

bool PerSampleProcessing::ScissorTesting(const Fragment& fragment,
                                         int viewport_width,
                                         int viewport_height) const {
  return scissor_tester_.IsInFrame(fragment, viewport_width, viewport_height);
}

bool PerSampleProcessing::DepthTesting(const Fragment& fragment,
                                       const DepthBuffer* depth_buffer) const {
  return depth_tester_.IsDeeper(fragment, *depth_buffer);
}

void PerSampleProcessing::WriteFragment(const Fragment& fragment,
                                        FrameBuffer& frame_buffer) const {
  frame_writer_.WriteFragmentToFrameBuffer(fragment, frame_buffer);
}

}  // namespace ho_renderer