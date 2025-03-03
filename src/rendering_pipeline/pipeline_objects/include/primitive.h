#ifndef _HORENDERER_RENDERINGPIPELINE_PIPELINEOBJECTS_PRIMITIVE_
#define _HORENDERER_RENDERINGPIPELINE_PIPELINEOBJECTS_PRIMITIVE_

#include <cstdint>

#include "engine/color/include/linear_rgb.h"

namespace ho_renderer {
class Primitive {
 public:
  Primitive();
  Primitive(bool is_outof_frustum);
  Primitive(bool is_outof_frustum, const LinearRGB& color);
  Primitive(const Primitive&);
  Primitive& operator=(const Primitive&);
  virtual ~Primitive();

  Primitive& set_is_outof_frustum(bool arg);
  Primitive& set_color(const LinearRGB& color);

  const bool is_outof_frustum() const;
  const LinearRGB& color() const;

 private:
  bool is_outof_frustum_;
  LinearRGB color_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_RENDERINGPIPELINE_PIPELINEOBJECTS_PRIMITIVE_