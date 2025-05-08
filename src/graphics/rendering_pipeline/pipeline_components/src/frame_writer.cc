#include "graphics/rendering_pipeline/pipeline_components/include/frame_writer.h"

#include "tools/include/debug.h"
namespace ho_renderer {
FrameWriter::FrameWriter() = default;
FrameWriter::~FrameWriter() = default;

void FrameWriter::WriteFragmentToFrameBuffer(const Fragment& fragment,
                                             FrameBuffer& frame_buffer) const {
  WriteColorToColorBuffer(fragment.color(), fragment.screen_coord(),
                          frame_buffer.GetColorBuffer());
  WriteDepthToDepthBuffer(fragment.depth(), fragment.screen_coord(),
                          frame_buffer.GetDepthBuffer());
}

void FrameWriter::WriteColorToColorBuffer(const LinearRGB& color,
                                          const Vector2& screen_coord,
                                          ColorBuffer* color_buffer) const {
  ASSERT_MSG(
      color_buffer != nullptr,
      "FrameWriter::WriteColorToColorBuffer Error : color buffer is null");
  if (color_buffer == nullptr) {
    return;
  }
  color_buffer->SetColor(screen_coord.x(), screen_coord.y(), color.ToBGRA32());
}
void FrameWriter::WriteDepthToDepthBuffer(const float depth,
                                          const Vector2& screen_coord,
                                          DepthBuffer* depth_buffer) const {
  if (depth_buffer == nullptr) {
    return;
  }
  ASSERT_MSG(
      depth_buffer != nullptr,
      "FrameWriter::WriteDepthToDepthBuffer Error : depth buffer is null");
  depth_buffer->SetDepth(screen_coord.x(), screen_coord.y(), depth);
}
}  // namespace ho_renderer