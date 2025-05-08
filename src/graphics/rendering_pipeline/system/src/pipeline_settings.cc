#include "graphics/rendering_pipeline/system/include/pipeline_settings.h"

#include <cstdint>

#include "core/input/include/input_listener.h"
#include "core/math/include/math_utils.h"
#include "core/math/include/vector2.h"
#include "graphics/color/include/linear_rgb.h"
#include "graphics/rendering_pipeline/system/include/pipeline_enum.h"
#include "tools/include/debug.h"

namespace ho_renderer {
PipelineSettings::PipelineSettings(int viewport_width, int viewport_height)
    : index_order_(kCounterClockWise),
      viewport_width_(viewport_width),
      viewport_height_(viewport_height),
      depth_range_min_(0.f),
      depth_range_max_(1.f),
      background_color_(LinearRGB::kLIGHT_GRAY),
      viewport_position_({0.f, 0.f}),
      primitive_type_(kTriangle),
      bounding_volume_mode_(kAABB),
      interpolation_mode_(kPerspectiveCorrection),
      rendering_mode_(kFill),
      shading_mode_(kFlat),
      is_using_backface_culling_(true),
      is_using_ambient_lighting_(true),
      is_using_diffuse_lighting_(true),
      is_using_specular_lighting_(true),
      default_ambient_color_(LinearRGB::kDARK_GRAY),
      default_diffuse_color_(LinearRGB::kGRAY),
      default_specular_color_(LinearRGB::kWHITE),
      default_specular_coefficient_(0.5f),
      default_specular_exponent_(8.f),
      default_opacity_(1.f) {
  ASSERT_MSG(viewport_width_ > 0 && viewport_height_ > 0,
             "PipelineSettings::PipelineSettings Error : viewport width, "
             "height must be bigger than zero");
  ASSERT_MSG(MathUtils::IsGreater(depth_range_max_, depth_range_min_),
             "PipelineSettings::PipelineSettings Error : depth range min must "
             "be less than depth range max");
  ASSERT_MSG(MathUtils::IsNotEqual(depth_range_min_, depth_range_max_),
             "PipelineSettings::PipelineSettings Error : depth range size must "
             "be bigger than zero");
}
PipelineSettings::~PipelineSettings() = default;

IndexOrder PipelineSettings::index_order() const { return index_order_; }
int PipelineSettings::viewport_width() const { return viewport_width_; }
int PipelineSettings::viewport_height() const { return viewport_height_; }
float PipelineSettings::depth_range_min() const { return depth_range_min_; }
float PipelineSettings::depth_range_max() const { return depth_range_max_; }
const LinearRGB& PipelineSettings::background_color() const {
  return background_color_;
}
const Vector2& PipelineSettings::viewport_position() const {
  return viewport_position_;
}
PrimitiveType PipelineSettings::primitive_type() const {
  return primitive_type_;
}
BoundingVolumeMode PipelineSettings::bounding_volume_mode() const {
  return bounding_volume_mode_;
}
InterpolationMode PipelineSettings::interpolation_mode() const {
  return interpolation_mode_;
}
RenderingMode PipelineSettings::rendering_mode() const {
  return rendering_mode_;
}
ShadingMode PipelineSettings::shading_mode() const { return shading_mode_; }
bool PipelineSettings::is_using_backface_culling() const {
  return is_using_backface_culling_;
}
bool PipelineSettings::is_using_ambient_lighting() const {
  return is_using_ambient_lighting_;
}
bool PipelineSettings::is_using_diffuse_lighting() const {
  return is_using_diffuse_lighting_;
}
bool PipelineSettings::is_using_specular_lighting() const {
  return is_using_specular_lighting_;
}
const LinearRGB& PipelineSettings::default_ambient_color() const {
  return default_ambient_color_;
}
const LinearRGB& PipelineSettings::default_diffuse_color() const {
  return default_diffuse_color_;
}
const LinearRGB& PipelineSettings::default_specular_color() const {
  return default_specular_color_;
}
float PipelineSettings::default_specular_coefficient() const {
  return default_specular_coefficient_;
}
float PipelineSettings::default_specular_exponent() const {
  return default_specular_exponent_;
}
float PipelineSettings::default_opacity() const { return default_opacity_; }

PipelineSettings& PipelineSettings::set_index_order(IndexOrder index_order) {
  index_order_ = index_order;
  return *this;
}
PipelineSettings& PipelineSettings::set_viewport_width(int viewport_width) {
  viewport_width_ = viewport_width;
  return *this;
}
PipelineSettings& PipelineSettings::set_viewport_height(int viewport_height) {
  viewport_height_ = viewport_height;
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
  bounding_volume_mode_ = mode;
  return *this;
}
PipelineSettings& PipelineSettings::set_interpolation_mode(
    InterpolationMode mode) {
  interpolation_mode_ = mode;
  return *this;
}
PipelineSettings& PipelineSettings::set_rendering_mode(RenderingMode mode) {
  rendering_mode_ = mode;
  return *this;
}
PipelineSettings& PipelineSettings::set_shading_mode(ShadingMode mode) {
  shading_mode_ = mode;
  return *this;
}
PipelineSettings& PipelineSettings::set_is_using_backface_culling(bool arg) {
  is_using_backface_culling_ = arg;
  return *this;
}
PipelineSettings& PipelineSettings::set_is_using_ambient_lighting(bool arg) {
  is_using_ambient_lighting_ = arg;
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
PipelineSettings& PipelineSettings::set_default_ambient_color(
    const LinearRGB& color) {
  default_ambient_color_ = color;
  return *this;
}
PipelineSettings& PipelineSettings::set_default_diffuse_color(
    const LinearRGB& color) {
  default_diffuse_color_ = color;
  return *this;
}
PipelineSettings& PipelineSettings::set_default_specular_color(
    const LinearRGB& color) {
  default_specular_color_ = color;
  return *this;
}
PipelineSettings& PipelineSettings::set_default_specular_coefficient(
    float coefficient) {
  default_specular_coefficient_ = coefficient;
  return *this;
}
PipelineSettings& PipelineSettings::set_default_specular_exponent(float exp) {
  default_specular_exponent_ = exp;
  return *this;
}
PipelineSettings& PipelineSettings::set_default_opacity(float opacity) {
  default_opacity_ = opacity;
  return *this;
}

void PipelineSettings::Update(InputReceiver& input_receiver, float delta_time) {
  if (input_receiver.IsPressed(Input::kKEY_NUM_1)) {
    rendering_mode_ = RenderingMode::kWireFrame;
    input_receiver.UpdateKeyStatus(Input::kKEY_NUM_1, false);
  }
  if (input_receiver.IsPressed(Input::kKEY_NUM_2)) {
    rendering_mode_ = RenderingMode::kFill;
    input_receiver.UpdateKeyStatus(Input::kKEY_NUM_2, false);
  }
  if (input_receiver.IsPressed(Input::kKEY_NUM_3)) {
    rendering_mode_ = RenderingMode::kTextureMapping;
    input_receiver.UpdateKeyStatus(Input::kKEY_NUM_3, false);
  }
  if (input_receiver.IsPressed(Input::kKEY_NUM_4)) {
    shading_mode_ = static_cast<ShadingMode>((shading_mode_ + 1) % 2);
    input_receiver.UpdateKeyStatus(Input::kKEY_NUM_4, false);
  }
  if (input_receiver.IsPressed(Input::kKEY_NUM_5)) {
    bounding_volume_mode_ =
        static_cast<BoundingVolumeMode>((bounding_volume_mode_ + 1) % 2);
    input_receiver.UpdateKeyStatus(Input::kKEY_NUM_5, false);
  }
  if (input_receiver.IsPressed(Input::kKEY_NUM_6)) {
    interpolation_mode_ =
        static_cast<InterpolationMode>((interpolation_mode_ + 1) % 2);
    input_receiver.UpdateKeyStatus(Input::kKEY_NUM_6, false);
  }
  if (input_receiver.IsPressed(Input::kKEY_NUM_7)) {
    is_using_backface_culling_ = !is_using_backface_culling_;
    input_receiver.UpdateKeyStatus(Input::kKEY_NUM_7, false);
  }
  if (input_receiver.IsPressed(Input::kKEY_NUM_8)) {
    is_using_ambient_lighting_ = !is_using_ambient_lighting_;
    input_receiver.UpdateKeyStatus(Input::kKEY_NUM_8, false);
  }
  if (input_receiver.IsPressed(Input::kKEY_NUM_9)) {
    is_using_diffuse_lighting_ = !is_using_diffuse_lighting_;
    input_receiver.UpdateKeyStatus(Input::kKEY_NUM_9, false);
  }
  if (input_receiver.IsPressed(Input::kKEY_NUM_0)) {
    is_using_specular_lighting_ = !is_using_specular_lighting_;
    input_receiver.UpdateKeyStatus(Input::kKEY_NUM_0, false);
  }
}
}  // namespace ho_renderer