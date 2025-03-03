#ifndef _HORENDERER_SHADERS_FRAGMENTSHADER_H_
#define _HORENDERER_SHADERS_FRAGMENTSHADER_H_

#include "engine/color/include/linear_rgb.h"
#include "engine/light/include/ambient_light.h"
#include "engine/light/include/directional_light.h"
#include "engine/light/include/point_light.h"
#include "rendering_pipeline/pipeline_objects/include/fragment.h"

namespace ho_renderer {
class FragmentShader {
 public:
  FragmentShader();
  FragmentShader(const FragmentShader&) = delete;
  FragmentShader& operator=(const FragmentShader&) = delete;
  ~FragmentShader();

  void SetFragmentColor(Fragment& fragment, const LinearRGB& rgb) const;

  const LinearRGB& GetPrimitiveColor(Fragment& fragment) const;
  const LinearRGB& GetTextureColor(Fragment& fragment) const;

  const LinearRGB& ComputeAmbientLighting(const AmbientLight& light) const;
  const LinearRGB& ComputeDiffuseLighting(Fragment& fragment,
                                          const DirectionalLight& light) const;
  const LinearRGB& ComputeDiffuseLighting(Fragment& fragment,
                                          const PointLight& light) const;
  const LinearRGB& ComputeDiffuseLighting(Fragment& fragment,
                                          const PointLight& light,
                                          const float intensity) const;
  const LinearRGB& ComputeSpecularLighting(Fragment& fragment,
                                           const PointLight& light) const;
  const LinearRGB& ComputeSpecularLighting(Fragment& fragment,
                                           const PointLight& light,
                                           const float intensity) const;
};

}  // namespace ho_renderer

#endif  // _HORENDERER_SHADERS_FRAGMENTSHADER_H_