#include "rendering_pipeline/stages/include/fragment_processing.h"

#include "app/include/debug.h"

namespace ho_renderer {
FragmentProcessing::FragmentProcessing()
    : fragment_shader_(new FragmentShader()) {}
FragmentProcessing::~FragmentProcessing() = default;

FragmentProcessing& FragmentProcessing::SetInputFragment(Fragment* fragment) {
  input_output_fragment_ = fragment;
  return *this;
}
FragmentProcessing& FragmentProcessing::SetInputPipelineSettings(
    PipelineSettings* pipeline_settings) {
  input_pipeline_settings_ = pipeline_settings;
  return *this;
}

FragmentProcessing& FragmentProcessing::ResetInputs() {
  input_output_fragment_ = nullptr;
  input_pipeline_settings_ = nullptr;
  return *this;
}

Fragment* FragmentProcessing::GetOutputFragment() const {
  if (input_output_fragment_ == nullptr) {
#ifdef DEBUG
    DEBUG_MSG("output_fragment_ is null.")
    assert(false);
#endif
  }
  return input_output_fragment_;
}

FragmentProcessing& FragmentProcessing::ResetOutputs() {
  input_output_fragment_ = nullptr;
  return *this;
}

void ho_renderer::FragmentProcessing::Process() {
  if (input_output_fragment_ == nullptr) {
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
  if (input_pipeline_settings_->rendering_mode() == kTEXTURE_MAPPING) {
  } else {
    fragment_shader_->ReadFragmentColorFromPrimitive(*input_output_fragment_);
  }
}
}  // namespace ho_renderer