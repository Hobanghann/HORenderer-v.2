#include "rendering_pipeline/shaders/include/perspective_divide_shader.h"

#include "app/include/debug.h"
#include "math/include/math_utils.h"
#include "math/include/vector4.h"

namespace ho_renderer {

PerspectiveDivideShader::PerspectiveDivideShader() = default;
PerspectiveDivideShader::~PerspectiveDivideShader() = default;

Vector3 PerspectiveDivideShader::PerspectiveDivide(
    const Vector4& clip_coordinate) const {
  return clip_coordinate.ToCartesianCoordinate();
}
}  // namespace ho_renderer
