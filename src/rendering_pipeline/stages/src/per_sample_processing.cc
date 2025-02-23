#include "rendering_pipeline/stages/include/per_sample_processing.h"

#include "app/include/debug.h"

namespace ho_renderer {

PerSampleProcessing::PerSampleProcessing()
    : scissor_testing_shader_(new ScissorTestingShader()),
      depth_testing_shader_(new DepthTestingShader()),
      frame_writing_shader_(new FrameWritingShader()) {}
PerSampleProcessing::~PerSampleProcessing() = default;

PerSampleProcessing& PerSampleProcessing::SetInputFragment(
    const Fragment* fragment) {
  input_fragment_ = fragment;
  return *this;
}
PerSampleProcessing& PerSampleProcessing::SetInputPipelineSettings(
    const PipelineSettings* pipeline_settings) {
  input_pipeline_settings_ = pipeline_settings;
  return *this;
}
PerSampleProcessing& PerSampleProcessing::SetInputFrameBuffer(
    FrameBuffer* frame_buffer) {
  input_output_frame_buffer_ = frame_buffer;
  return *this;
}

PerSampleProcessing& PerSampleProcessing::ResetInputs() {
  input_fragment_ = nullptr;
  input_pipeline_settings_ = nullptr;
  input_output_frame_buffer_ = nullptr;
  return *this;
}

FrameBuffer* PerSampleProcessing::GetOutputFrameBuffer() const {
  if (input_output_frame_buffer_ == nullptr) {
#ifdef DEBUG
    DEBUG_MSG("output_frame_buffer_ is null.")
    assert(false);
#endif
  }
  return input_output_frame_buffer_;
}

PerSampleProcessing& PerSampleProcessing::ResetOutputs() {
  input_output_frame_buffer_ = nullptr;
  return *this;
}

void ho_renderer::PerSampleProcessing::Process() {
  if (input_fragment_ == nullptr) {
#ifdef DEBUG
    DEBUG_MSG("input_fragment_ is null.")
    assert(false);
#endif
  }
  if (input_pipeline_settings_ == nullptr) {
#ifdef DEBUG
    DEBUG_MSG("input_pipeline_settings_ is null.")
    assert(false);
#endif
  }
  if (input_output_frame_buffer_ == nullptr) {
#ifdef DEBUG
    DEBUG_MSG("input_frame_buffer_ is null.")
    assert(false);
#endif
  }
  // scissor test
  if (!scissor_testing_shader_->IsInFrame(
          *input_fragment_, input_pipeline_settings_->screen_width(),
          input_pipeline_settings_->screen_height())) {
    // discard this fragment
    return;
  }

  // depth test
  if (depth_testing_shader_->IsDeeper(
          *input_fragment_, input_output_frame_buffer_->GetDepthBuffer())) {
    // discard this fragment
    return;
  }
  // writing in frame buffer
  frame_writing_shader_->WriteFragmentToFrameBuffer(
      *input_fragment_, *input_output_frame_buffer_);
}
}  // namespace ho_renderer