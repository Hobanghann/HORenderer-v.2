#include "renderer/include/renderer_settings.h"

#include "tools/include/debug.h"

namespace ho_renderer {

RendererSettings::RendererSettings(const int screen_width,
                                   const int screen_height)
    : screen_width_(screen_width),
      screen_height_(screen_height),
      frame_rate_mode_(FrameRateMode::kVARIABLE) {
  ASSERT_MSG(screen_width_ != 0.f || screen_height_ != 0.f,
             "Cannot Initialize Renderer : screen width, height must be bigger "
             "than zero.");
}
RendererSettings::~RendererSettings() = default;

const int RendererSettings::screen_width() const { return screen_width_; }
const int RendererSettings::screen_height() const { return screen_height_; }
const FrameRateMode RendererSettings::frame_rate_mode() const {
  return frame_rate_mode_;
}

RendererSettings& RendererSettings::set_screen_width(const int screen_width) {
  screen_width_ = screen_width;
  return *this;
}
RendererSettings& RendererSettings::set_screen_height(const int screen_height) {
  screen_height_ = screen_height;
  return *this;
}
RendererSettings& RendererSettings::set_frame_rate_mode(
    const FrameRateMode mode) {
  frame_rate_mode_ = mode;
  return *this;
}

void RendererSettings::Update(InputReceiver& input_receiver,
                              const float delta_time) {
  if (input_receiver.IsPressed(Input::kKEY_F1)) {
    frame_rate_mode_ = FrameRateMode::k30;
    input_receiver.UpdateKeyStatus(Input::kKEY_F1, false);
  }
  if (input_receiver.IsPressed(Input::kKEY_F2)) {
    frame_rate_mode_ = FrameRateMode::k60;
    input_receiver.UpdateKeyStatus(Input::kKEY_F2, false);
  }
  if (input_receiver.IsPressed(Input::kKEY_F3)) {
    frame_rate_mode_ = FrameRateMode::kVARIABLE;
    input_receiver.UpdateKeyStatus(Input::kKEY_F3, false);
  }
}
}  // namespace ho_renderer