#ifndef _HORENDERER_RENDERER_RENDERERSETTINGS_H_
#define _HORENDERER_RENDERER_RENDERERSETTINGS_H_

#define SCREEN_WIDTH = 1280
#define SCREEN_HEIGHT = 720

#include "core/input/include/input_listener.h"

namespace ho_renderer {
enum FrameRateMode { k30 = 0, k60, kVARIABLE };
class RendererSettings : public InputListener {
 public:
  RendererSettings(const int screen_width, const int screen_height);
  RendererSettings(const RendererSettings&) = delete;
  RendererSettings& operator=(const RendererSettings&) = delete;
  ~RendererSettings();

  const int screen_width() const;
  const int screen_height() const;
  const FrameRateMode frame_rate_mode() const;
  RendererSettings& set_screen_width(const int screen_width);
  RendererSettings& set_screen_height(const int screen_height);
  RendererSettings& set_frame_rate_mode(const FrameRateMode mode);

  void Update(InputReceiver& input_receiver, const float delta_time) override;

 private:
  int screen_width_;
  int screen_height_;
  FrameRateMode frame_rate_mode_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_RENDERER_RENDERERSETTINGS_H_