#include "rendering_pipeline/pipeline/include/pipeline_settings.h"

#include <cstdint>

#include "app/include/debug.h"
#include "math/include/vector2.h"

namespace ho_renderer {
PipelineSettings::PipelineSettings()
    : screen_width_(1280),
      screen_height_(720),
      depth_range_min_(0.f),
      depth_range_max_(1.f),
      background_color_(LinearRGB::kWHITE),
      viewport_position_({0.f, 0.f}),
      primitive_type_(PrimitiveType::kTRIANGLE),
      bounding_volume_mode_(BoundingVolumeMode::kSPHERE),
      is_sphere_mode_(true),
      interpolation_mode_(InterpolationMode::kPERSPECTIVE_CORRECT),
      is_affine_mode_(false),
      rendering_mode_(RenderingMode::kFILL),
      is_using_backface_culling_(true),
      is_using_diffuse_lighting_(true),
      is_using_specular_lighting_(true) {}
PipelineSettings::~PipelineSettings() = default;

const uint32_t PipelineSettings::screen_width() const { return screen_width_; }
const uint32_t PipelineSettings::screen_height() const {
  return screen_height_;
}
const float PipelineSettings::depth_range_min() const {
  return depth_range_min_;
}
const float PipelineSettings::depth_range_max() const {
  return depth_range_max_;
}
const LinearRGB& PipelineSettings::background_color() const {
  return background_color_;
}
const Vector2& PipelineSettings::viewport_position() const {
  return viewport_position_;
}
const PrimitiveType PipelineSettings::primitive_type() const {
  return primitive_type_;
}
const BoundingVolumeMode PipelineSettings::bounding_volume_mode() const {
  return bounding_volume_mode_;
}
const InterpolationMode PipelineSettings::interpolation_mode() const {
  return interpolation_mode_;
}
const RenderingMode PipelineSettings::rendering_mode() const {
  return rendering_mode_;
}
bool PipelineSettings::is_using_backface_culling() const {
  return is_using_backface_culling_;
}
bool PipelineSettings::is_using_diffuse_lighting() const {
  return is_using_diffuse_lighting_;
}
bool PipelineSettings::is_using_specular_lighting() const {
  return is_using_specular_lighting_;
}

PipelineSettings& PipelineSettings::set_screen_width(
    const uint32_t& screen_width) {
  screen_width_ = screen_width;
  return *this;
}
PipelineSettings& PipelineSettings::set_screen_height(
    const uint32_t& screen_height) {
  screen_height_ = screen_height;
  return *this;
}
PipelineSettings& PipelineSettings::set_depth_range_min(float depth_range_min) {
  depth_range_min_ = depth_range_min;
  return *this;
}
PipelineSettings& PipelineSettings::set_depth_range_max(float depth_range_max) {
  depth_range_max_ = depth_range_max;
  return *this;
}
PipelineSettings& PipelineSettings::set_background_color(
    const LinearRGB& background_color) {
  background_color_ = background_color;
  return *this;
}
PipelineSettings& PipelineSettings::set_viewport_position(
    const Vector2& viewport_position) {
  viewport_position_ = viewport_position;
  return *this;
}
PipelineSettings& PipelineSettings::set_primitive_type(PrimitiveType type) {
  primitive_type_ = type;
  return *this;
}
PipelineSettings& PipelineSettings::set_bounding_volume_mode(
    BoundingVolumeMode mode) {
  if (mode == kSPHERE) {
    is_sphere_mode_ = true;
  } else {
    is_sphere_mode_ = false;
  }
  bounding_volume_mode_ = mode;
  return *this;
}
PipelineSettings& PipelineSettings::set_interpolation_mode(
    InterpolationMode mode) {
  if (mode == kAFFINE) {
    is_affine_mode_ = true;
  } else {
    is_affine_mode_ = false;
  }
  interpolation_mode_ = mode;
  return *this;
}
PipelineSettings& PipelineSettings::set_rendering_mode(RenderingMode mode) {
  rendering_mode_ = mode;
  return *this;
}
PipelineSettings& PipelineSettings::set_is_using_backface_culling(bool arg) {
  is_using_backface_culling_ = arg;
  return *this;
}
PipelineSettings& PipelineSettings::set_is_using_diffuse_lighting(bool arg) {
  is_using_diffuse_lighting_ = arg;
  return *this;
}
PipelineSettings& PipelineSettings::set_is_using_specular_lighting(bool arg) {
  is_using_specular_lighting_ = arg;
  return *this;
}

void PipelineSettings::Update(InputReceiver& input_receiver,
                              const float delta_time) {
  if (input_receiver.IsPressed(InputKey::kKEY_F1)) {
    rendering_mode_ = RenderingMode::kWIRE_FRAME;
    input_receiver.UpdateKeyStatus(InputKey::kKEY_F1, false);
  }
  if (input_receiver.IsPressed(InputKey::kKEY_F2)) {
    rendering_mode_ = RenderingMode::kFILL;
    input_receiver.UpdateKeyStatus(InputKey::kKEY_F2, false);
  }
  if (input_receiver.IsPressed(InputKey::kKEY_F3)) {
    rendering_mode_ = RenderingMode::kTEXTURE_MAPPING;
    input_receiver.UpdateKeyStatus(InputKey::kKEY_F3, false);
  }
  if (input_receiver.IsPressed(InputKey::kKEY_F4)) {
    is_sphere_mode_ = !is_sphere_mode_;
    if (is_sphere_mode_) {
      bounding_volume_mode_ = kSPHERE;
    } else {
      bounding_volume_mode_ = kAABB;
    }
    input_receiver.UpdateKeyStatus(InputKey::kKEY_F4, false);
  }
  if (input_receiver.IsPressed(InputKey::kKEY_F5)) {
    is_affine_mode_ = !is_affine_mode_;
    if (is_affine_mode_) {
      interpolation_mode_ = kAFFINE;
    } else {
      interpolation_mode_ = kPERSPECTIVE_CORRECT;
    }
    input_receiver.UpdateKeyStatus(InputKey::kKEY_F5, false);
  }
  if (input_receiver.IsPressed(InputKey::kKEY_F6)) {
    is_using_backface_culling_ = !is_using_backface_culling_;
    input_receiver.UpdateKeyStatus(InputKey::kKEY_F6, false);
  }
  if (input_receiver.IsPressed(InputKey::kKEY_F7)) {
    is_using_diffuse_lighting_ = !is_using_diffuse_lighting_;
    input_receiver.UpdateKeyStatus(InputKey::kKEY_F7, false);
  }
  if (input_receiver.IsPressed(InputKey::kKEY_F8)) {
    is_using_specular_lighting_ = !is_using_specular_lighting_;
    input_receiver.UpdateKeyStatus(InputKey::kKEY_F8, false);
  }
}
}  // namespace ho_renderer