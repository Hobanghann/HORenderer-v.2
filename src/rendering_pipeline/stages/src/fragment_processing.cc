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
FragmentProcessing& FragmentProcessing::SetInputAmbientLight(
    AmbientLight* light) {
  input_ambient_light_ = light;
  return *this;
}
FragmentProcessing& FragmentProcessing::SetInputDirectionalLight(
    DirectionalLight* light) {
  input_directional_light_ = light;
  return *this;
}
FragmentProcessing& FragmentProcessing::SetInputPointLight(PointLight* light) {
  input_point_lights_.push_back(light);
  return *this;
}

FragmentProcessing& FragmentProcessing::ResetInputs() {
  input_output_fragment_ = nullptr;
  input_pipeline_settings_ = nullptr;
  input_ambient_light_ = nullptr;
  input_directional_light_ = nullptr;
  input_point_lights_.clear();
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
  LinearRGB default_color;
  LinearRGB ambient_light;
  LinearRGB diffuse_light;
  LinearRGB specular_light;

  default_color = fragment_shader_->GetPrimitiveColor(*input_output_fragment_);

  if (input_ambient_light_ != nullptr) {
    ambient_light =
        fragment_shader_->ComputeAmbientLighting(*input_ambient_light_);
  }
  if (input_pipeline_settings_->primitive_type() == kTRIANGLE) {
    if (input_directional_light_ != nullptr) {
      if (input_pipeline_settings_->is_using_diffuse_lighting()) {
        diffuse_light += fragment_shader_->ComputeDiffuseLighting(
            *input_output_fragment_, *input_directional_light_);
      }
    }
    for (auto light = input_point_lights_.cbegin();
         light != input_point_lights_.cend(); light++) {
      float intensity =
          (*light)->GetIntensityAt(input_output_fragment_->view_coordinate());
      if (input_pipeline_settings_->is_using_diffuse_lighting()) {
        diffuse_light += fragment_shader_->ComputeDiffuseLighting(
            *input_output_fragment_, **light, intensity);
      }
      if (input_pipeline_settings_->is_using_specular_lighting()) {
        specular_light += fragment_shader_->ComputeSpecularLighting(
            *input_output_fragment_, **light, intensity);
      }
    }
  }

  LinearRGB final_color =
      (ambient_light + diffuse_light + specular_light) * default_color;
  fragment_shader_->SetFragmentColor(*input_output_fragment_, final_color);
}
}  // namespace ho_renderer