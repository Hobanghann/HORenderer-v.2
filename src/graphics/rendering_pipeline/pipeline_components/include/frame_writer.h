#ifndef _HORENDERER_FRAME_WRITER_H_
#define _HORENDERER_FRAME_WRITER_H_

#include <cstdint>

#include "core/math/include/vector2.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/color_buffer.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/depth_buffer.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/fragment.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/frame_buffer.h"

namespace ho_renderer {
class FrameWriter {
 public:
  FrameWriter();
  FrameWriter(const FrameWriter&) = delete;
  FrameWriter& operator=(const FrameWriter&) = delete;
  ~FrameWriter();

  void WriteFragmentToFrameBuffer(const Fragment& fragment,
                                  FrameBuffer& frame_buffer) const;

 private:
  void WriteColorToColorBuffer(const LinearRGB& color,
                               const Vector2& screen_coord,
                               ColorBuffer* color_buffer) const;
  void WriteDepthToDepthBuffer(const float depth, const Vector2& screen_coord,
                               DepthBuffer* depth_buffer) const;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_FRAME_WRITER_H_