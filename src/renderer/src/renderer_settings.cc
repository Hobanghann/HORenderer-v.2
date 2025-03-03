#include "renderer/include/renderer_settings.h"

#include "app/include/debug.h"

namespace ho_renderer {

RendererSettings::RendererSettings()
    : frame_rate_mode_(FrameRateMode::kVARIABLE) {}
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
  if (input_receiver.IsPressed(InputKey::kKEY_F9)) {
    frame_rate_mode_ = FrameRateMode::k30;
    input_receiver.UpdateKeyStatus(InputKey::kKEY_F9, false);
  }
  if (input_receiver.IsPressed(InputKey::kKEY_F10)) {
    frame_rate_mode_ = FrameRateMode::k60;
    input_receiver.UpdateKeyStatus(InputKey::kKEY_F10, false);
  }
  if (input_receiver.IsPressed(InputKey::kKEY_F11)) {
    frame_rate_mode_ = FrameRateMode::kVARIABLE;
    input_receiver.UpdateKeyStatus(InputKey::kKEY_F11, false);
  }
}
}  // namespace ho_renderer