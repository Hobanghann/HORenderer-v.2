#include "rendering_pipeline/stages/include/pre_render.h"

#include "app/include/debug.h"
#include "rendering_pipeline/pipeline/include/resources_manager.h"

namespace ho_renderer {
PreRenderStage::PreRenderStage()
    : input_frame_buffer_(nullptr),
      input_transform_(nullptr),
      input_ambient_light_(nullptr),
      input_directional_light_(nullptr),
      input_point_lights_() {}
PreRenderStage::~PreRenderStage() = default;

PreRenderStage& PreRenderStage::SetInputFrameBuffer(FrameBuffer* frame_buffer) {
  input_frame_buffer_ = frame_buffer;
  return *this;
}
PreRenderStage& PreRenderStage::SetInputTransform(AffineTransform* transform) {
  input_transform_ = transform;
  return *this;
}
PreRenderStage& PreRenderStage::SetInputAmbientLight(AmbientLight* light) {
  input_ambient_light_ = light;
  return *this;
}
PreRenderStage& PreRenderStage::SetInputDirectionalLight(
    DirectionalLight* light) {
  input_directional_light_ = light;
  return *this;
}
PreRenderStage& PreRenderStage::SetInputPointLight(PointLight* light) {
  input_point_lights_.push_back(light);
  return *this;
}

PreRenderStage& PreRenderStage::ResetInputs() {
  input_frame_buffer_ = nullptr;
  input_transform_ = nullptr;
  input_ambient_light_ = nullptr;
  input_directional_light_ = nullptr;
  input_point_lights_.clear();
  return *this;
}

void PreRenderStage::PreRender() {
  if (input_frame_buffer_ == nullptr) {
#ifdef DEBUG
    DEBUG_MSG("input_fragment_ is null.")
    assert(false);
#endif
  }
  // reset frame buffer
  input_frame_buffer_->ResetBuffers();
  // transform ambient lights
  if (input_ambient_light_ != nullptr) {
  }
  // transform directional lights
  if (input_directional_light_ != nullptr) {
    const Vector4& light_direction =
        input_directional_light_->light_direction();
    input_directional_light_->set_transformed_direction(
        input_transform_->Transform(input_directional_light_->light_direction())
            .ToVector3());
  }
  // transform point lights
  if (input_point_lights_.size() != 0) {
    for (auto light_itr = input_point_lights_.begin();
         light_itr != input_point_lights_.end(); light_itr++) {
      PointLight* light = *light_itr;
      const Vector4& position = light->world_coordinate();
      light->set_transformed_coordinate(
          input_transform_->Transform(position).ToVector3());
    }
  }
}
}  // namespace ho_renderer