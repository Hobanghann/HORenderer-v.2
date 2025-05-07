#ifndef _HORENDERER_DEPTH_BUFFER_H_
#define _HORENDERER_DEPTH_BUFFER_H_

#include <memory>

namespace ho_renderer {
class DepthBuffer {
 public:
  DepthBuffer(const int screen_width, const int screen_height,
              const float depth_range_min, const float depth_range_max);
  ~DepthBuffer();
  DepthBuffer(const DepthBuffer&) = delete;
  DepthBuffer& operator=(const DepthBuffer&) = delete;
  void ResetBuffer();
  float GetDepth(const int x, const int y) const;
  void SetDepth(const int x, const int y, const float depth);
  const float* GetBuffer() const;
  void ImportExternalBuffer(std::unique_ptr<float[]> depth_buffer);

 private:
  int screen_width_;
  int screen_height_;
  std::unique_ptr<float[]> depth_buffer_;
  float depth_range_min_;
  float depth_range_max_;
  bool is_buffer_injected_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_DEPTHBUFFER_H_