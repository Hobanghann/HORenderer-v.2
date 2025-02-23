#ifndef _HORENDERER_ENGINE_FRAME_BUFFER_H_
#define _HORENDERER_ENGINE_FRAME_BUFFER_H_

#include <memory>

#include "rendering_pipeline/pipeline_objects/include/color_buffer.h"
#include "rendering_pipeline/pipeline_objects/include/depth_buffer.h"

namespace ho_renderer {
class FrameBuffer {
 public:
  FrameBuffer();
  FrameBuffer(const FrameBuffer&) = delete;
  FrameBuffer& operator=(const FrameBuffer&) = delete;
  ~FrameBuffer();

  FrameBuffer& CreateColorBuffer(const int screen_width,
                                 const int screen_height,
                                 std::uint32_t background_color_bit);
  FrameBuffer& CreateDepthBuffer(const int screen_width,
                                 const int screen_height,
                                 const float depth_range_min,
                                 const float depth_range_max);

  ColorBuffer& GetColorBuffer() const;
  DepthBuffer& GetDepthBuffer() const;

  FrameBuffer& ChangeColorBuffer(const int screen_width,
                                 const int screen_height,
                                 std::uint32_t background_color_bit);
  FrameBuffer& ChangeDepthBuffer(const int screen_width,
                                 const int screen_height,
                                 const float depth_range_min,
                                 const float depth_range_max);

  void ResetBuffers();

 private:
  std::unique_ptr<ColorBuffer> color_buffer_;
  std::unique_ptr<DepthBuffer> depth_buffer_;
};

}  // namespace ho_renderer

#endif  // _HORENDERER_ENGINE_FRAME_BUFFER_H_