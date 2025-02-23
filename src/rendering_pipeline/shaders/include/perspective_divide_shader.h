#ifndef _HORENDERER_RENDERINGPIPELINE_SHADERS_PERSPECTIVEDIVIDESHADER_H_
#define _HORENDERER_RENDERINGPIPELINE_SHADERS_PERSPECTIVEDIVIDESHADER_H_

#include "math/include/vector3.h"
#include "math/include/vector4.h"

namespace ho_renderer {
class PerspectiveDivideShader {
 public:
  PerspectiveDivideShader();
  PerspectiveDivideShader(const PerspectiveDivideShader&) = delete;
  PerspectiveDivideShader& operator=(const PerspectiveDivideShader&) = delete;
  ~PerspectiveDivideShader();

  Vector3 PerspectiveDivide(const Vector4& clip_coordinate) const;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_RENDERINGPIPELINE_SHADERS_PERSPECTIVEDIVIDESHADER_H_