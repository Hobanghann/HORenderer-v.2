#include "graphics/rendering_pipeline/stages/include/rasterization.h"

#include "graphics/rendering_pipeline/pipeline_components/include/depth_tester.h"

namespace ho_renderer {
Rasterization::Rasterization() = default;
Rasterization::~Rasterization() = default;

std::vector<Fragment> *Rasterization::Rasterize(
    std::vector<Fragment> *output_buffer, const Primitive *primitive,
    std::vector<TransformedVertex> *v_buffer, FrameBuffer &frame_buffer,
    const PipelineSettings &settings) {
  switch (settings.primitive_type()) {
    case kPoint:
      rasterizer_.RasterizePoint(output_buffer, v_buffer,
                                 static_cast<const Point *>(primitive),
                                 frame_buffer.GetDepthBuffer());
      break;
    case kLine:
      switch (settings.interpolation_mode()) {
        case kAffine:
          rasterizer_.RasterizeLineAffine(output_buffer, v_buffer,
                                          static_cast<const Line *>(primitive),
                                          frame_buffer.GetDepthBuffer());
          break;
        case kPerspectiveCorrection:
          rasterizer_.RasterizeLinePerspective(
              output_buffer, v_buffer, static_cast<const Line *>(primitive),
              frame_buffer.GetDepthBuffer());
          break;
      }
      break;
    case kTriangle:
      switch (settings.interpolation_mode()) {
        case kAffine:
          switch (settings.rendering_mode()) {
            case kWireFrame:
              rasterizer_.RasterizeWireTriangleAffine(
                  output_buffer, v_buffer,
                  static_cast<const Triangle *>(primitive),
                  frame_buffer.GetDepthBuffer());
              break;
            default:
              rasterizer_.EdgeFunctionRasterizeTriangleAffine(
                  output_buffer, v_buffer,
                  static_cast<const Triangle *>(primitive),
                  frame_buffer.GetDepthBuffer());
              break;
          }
          break;
        case kPerspectiveCorrection:
          switch (settings.rendering_mode()) {
            case kWireFrame:
              rasterizer_.RasterizeWireTrianglePerspective(
                  output_buffer, v_buffer,
                  static_cast<const Triangle *>(primitive),
                  frame_buffer.GetDepthBuffer());
              break;
            default:
              rasterizer_.EdgeFunctionRasterizeTrianglePerspective(
                  output_buffer, v_buffer,
                  static_cast<const Triangle *>(primitive),
                  frame_buffer.GetDepthBuffer());
              break;
          }
          break;
      }
      break;
  }
  return output_buffer;
}
}  // namespace ho_renderer