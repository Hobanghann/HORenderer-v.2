#include "rendering_pipeline/shaders/include/frame_writing_shader.h"

#include "app/include/debug.h"

namespace ho_renderer {
FrameWritingShader::FrameWritingShader() = default;
FrameWritingShader::~FrameWritingShader() = default;

void FrameWritingShader::WriteFragmentToFrameBuffer(const Fragment& fragment,
                                                    FrameBuffer& frame_buffer) {
  WriteColorToColorBuffer(fragment.color(), fragment.screen_coordinate(),
                          frame_buffer.GetColorBuffer());
  WriteDepthToDepthBuffer(fragment.interpolated_depth(),
                          fragment.screen_coordinate(),
                          frame_buffer.GetDepthBuffer());
}

void FrameWritingShader::WriteColorToColorBuffer(
    const LinearRGB& color, const Vector2& screen_coordinate,
    ColorBuffer& color_buffer) {
  color_buffer.SetColor(screen_coordinate.x(), screen_coordinate.y(),
                        color.ToARGB32());
}
void FrameWritingShader::WriteDepthToDepthBuffer(
    const float depth, const Vector2& screen_coordinate,
    DepthBuffer& depth_buffer) {
  depth_buffer.SetDepth(screen_coordinate.x(), screen_coordinate.y(), depth);
}
}  // namespace ho_renderer