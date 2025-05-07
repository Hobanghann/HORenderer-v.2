#ifndef _HORENDERER_SCISSOR_TESTER_H_
#define _HORENDERER_SCISSOR_TESTER_H_

#include "graphics/rendering_pipeline/pipeline_objects/include/fragment.h"

namespace ho_renderer {
class ScissorTester {
 public:
  ScissorTester();
  ScissorTester(const ScissorTester&) = delete;
  ScissorTester& operator=(const ScissorTester&) = delete;
  ~ScissorTester();

  bool IsInFrame(const Fragment& fragment, int screen_width,
                 int screen_height) const;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_SCISSOR_TESTER_H_