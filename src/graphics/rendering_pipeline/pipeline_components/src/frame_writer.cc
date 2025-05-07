#include "graphics/rendering_pipeline/pipeline_components/include/frame_writer.h"

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
  color_buffer->SetColor(screen_coord.x(), screen_coord.y(), color.ToBGRA32());
}
void FrameWriter::WriteDepthToDepthBuffer(const float depth,
                                          const Vector2& screen_coord,
                                          DepthBuffer* depth_buffer) const {
  depth_buffer->SetDepth(screen_coord.x(), screen_coord.y(), depth);
}
}  // namespace ho_renderer