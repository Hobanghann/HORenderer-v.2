#ifndef _HORENDERER_DEPTH_TESTER_H_
#define _HORENDERER_DEPTH_TESTER_H_

#include "graphics/rendering_pipeline/pipeline_objects/include/depth_buffer.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/fragment.h"

namespace ho_renderer {
class DepthTestingShader {
 public:
  DepthTestingShader();
  DepthTestingShader(const DepthTestingShader&) = delete;
  DepthTestingShader& operator=(const DepthTestingShader&) = delete;
  ~DepthTestingShader();

  bool IsDeeper(const Fragment& fragment,
                const DepthBuffer& depth_buffer) const;
  bool IsShallower(const Fragment& fragment,
                   const DepthBuffer& depth_buffer) const;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_DEPTH_TESTER_H_