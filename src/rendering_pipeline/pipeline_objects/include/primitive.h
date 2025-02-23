#ifndef _HORENDERER_RENDERINGPIPELINE_PIPELINEOBJECTS_PRIMITIVE_
#define _HORENDERER_RENDERINGPIPELINE_PIPELINEOBJECTS_PRIMITIVE_

#include <cstdint>

namespace ho_renderer {
class Primitive {
 public:
  Primitive();
  Primitive(bool is_outof_frustum);
  Primitive(bool is_outof_frustum, std::uint32_t color_bit);
  Primitive(const Primitive&);
  Primitive& operator=(const Primitive&);
  virtual ~Primitive();

  Primitive& set_is_outof_frustum(bool arg);
  Primitive& set_color_bit(std::uint32_t color_bit);

  const bool is_outof_frustum() const;
  const std::uint32_t color_bit() const;

 private:
  bool is_outof_frustum_;
  std::uint32_t color_bit_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_RENDERINGPIPELINE_PIPELINEOBJECTS_PRIMITIVE_