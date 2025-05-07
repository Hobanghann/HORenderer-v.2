#ifndef _HORENDERER_PER_SAMPLE_PROCESSING_H_
#define _HORENDERER_PER_SAMPLE_PROCESSING_H_

#include <memory>

#include "graphics/rendering_pipeline/pipeline_components/include/depth_tester.h"
#include "graphics/rendering_pipeline/pipeline_components/include/frame_writer.h"
#include "graphics/rendering_pipeline/pipeline_components/include/scissor_tester.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/fragment.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/frame_buffer.h"
#include "graphics/rendering_pipeline/system/include/pipeline_settings.h"

namespace ho_renderer {
class PerSampleProcessing {
 public:
  PerSampleProcessing();
  PerSampleProcessing(const PerSampleProcessing&) = delete;
  PerSampleProcessing& operator=(const PerSampleProcessing) = delete;
  ~PerSampleProcessing();

  bool ScissorTesting(const Fragment& fragment, int viewport_width,
                      int viewport_height) const;

  bool DepthTesting(const Fragment& fragment,
                    const DepthBuffer* depth_buffer) const;

  void WriteFragment(const Fragment& fragment, FrameBuffer& frame_buffer) const;

 private:
  // pipeline_components
  ScissorTester scissor_tester_;
  DepthTestingShader depth_tester_;
  FrameWriter frame_writer_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_PER_SAMPLE_PROCESSING_H_