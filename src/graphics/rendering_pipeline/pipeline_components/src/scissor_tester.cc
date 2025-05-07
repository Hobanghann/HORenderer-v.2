#include "graphics/rendering_pipeline/pipeline_components/include/scissor_tester.h"

namespace ho_renderer {
ScissorTester::ScissorTester() = default;
ScissorTester::~ScissorTester() = default;

bool ScissorTester::IsInFrame(const Fragment& fragment, int screen_width,
                              int screen_height) const {
  return !(fragment.screen_coord().x() < 0.f ||
           fragment.screen_coord().x() > (screen_width - 1) ||
           fragment.screen_coord().y() < 0.f ||
           fragment.screen_coord().y() > (screen_height - 1));
}
}  // namespace ho_renderer