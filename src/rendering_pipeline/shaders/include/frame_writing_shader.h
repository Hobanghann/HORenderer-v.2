#ifndef _HORENDERER_RENDERINGPIPELINE_SHADERS_FRAME_WRITING_SHADER_H_
#define _HORENDERER_RENDERINGPIPELINE_SHADERS_FRAME_WRITING_SHADER_H_

#include <cstdint>

#include "math/include/vector2.h"
#include "rendering_pipeline/pipeline_objects/include/color_buffer.h"
#include "rendering_pipeline/pipeline_objects/include/depth_buffer.h"
#include "rendering_pipeline/pipeline_objects/include/fragment.h"
#include "rendering_pipeline/pipeline_objects/include/frame_buffer.h"

namespace ho_renderer {
class FrameWritingShader {
 public:
  FrameWritingShader();
  FrameWritingShader(const FrameWritingShader&) = delete;
  FrameWritingShader& operator=(const FrameWritingShader&) = delete;
  ~FrameWritingShader();

  void WriteFragmentToFrameBuffer(const Fragment& fragment,
                                  FrameBuffer& frame_buffer);

 private:
  void WriteColorToColorBuffer(const LinearRGB& color,
                               const Vector2& screen_coordinate,
                               ColorBuffer& color_buffer);
  void WriteDepthToDepthBuffer(const float depth,
                               const Vector2& screen_coordinate,
                               DepthBuffer& depth_buffer);
};
}  // namespace ho_renderer

#endif  // _HORENDERER_RENDERINGPIPELINE_SHADERS_FRAME_WRITING_SHADER_H_