#include "rendering_pipeline/shaders/include/scissor_testing_shader.h"

#include "app/include/debug.h"

namespace ho_renderer {
ScissorTestingShader::ScissorTestingShader() = default;
ScissorTestingShader::~ScissorTestingShader() = default;

bool ScissorTestingShader::IsInFrame(const Fragment& fragment, int screen_width,
                                     int screen_height) {
  return !(fragment.screen_coordinate().x() < 0.f ||
           fragment.screen_coordinate().x() > (screen_width - 1) ||
           fragment.screen_coordinate().y() < 0.f ||
           fragment.screen_coordinate().y() > (screen_height - 1));
}
}  // namespace ho_renderer