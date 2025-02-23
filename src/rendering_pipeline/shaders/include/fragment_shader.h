#ifndef _HORENDERER_SHADERS_FRAGMENTSHADER_H_
#define _HORENDERER_SHADERS_FRAGMENTSHADER_H_

#include "rendering_pipeline/pipeline_objects/include/fragment.h"

namespace ho_renderer {
class FragmentShader {
 public:
  FragmentShader();
  FragmentShader(const FragmentShader&) = delete;
  FragmentShader& operator=(const FragmentShader&) = delete;
  ~FragmentShader();

  const FragmentShader& ReadFragmentColorFromPrimitive(
      Fragment& fragment) const;
  const FragmentShader& ReadFragmentColorFromTexture(Fragment& fragment) const;
};

}  // namespace ho_renderer

#endif  // _HORENDERER_SHADERS_FRAGMENTSHADER_H_