#ifndef _HORENDERER_COLOR_BUFFER_H_
#define _HORENDERER_COLOR_BUFFER_H_

#include <cstdint>
#include <memory>

namespace ho_renderer {
class ColorBuffer {
 public:
  ColorBuffer(const int screen_width, const int screen_height,
              std::uint32_t background_color_bit);
  ColorBuffer(const ColorBuffer&) = delete;
  ColorBuffer& operator=(const ColorBuffer&) = delete;
  ~ColorBuffer();

  void ResetBuffer();
  std::uint32_t GetColor(const int x, const int y) const;
  void SetColor(const int x, const int y, const std::uint32_t color_bit);
  const uint32_t* GetBuffer() const;
  void ImportExternalBuffer(std::unique_ptr<std::uint32_t[]> color_buffer);

 private:
  std::unique_ptr<std::uint32_t[]> color_buffer_;
  int screen_width_;
  int screen_height_;
  std::uint32_t background_color_bit_;
  bool is_buffer_injected_;
};
}  // namespace ho_renderer
#endif  // _HORENDERER_COLOR_BUFFER_H_