#ifndef _HORENDERER_FRAGMENT_SHADER_H_
#define _HORENDERER_FRAGMENT_SHADER_H_

#include "graphics/color/include/linear_rgb.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/fragment.h"
#include "graphics/rendering_pipeline/system/include/pipeline_settings.h"
#include "scene/light/include/ambient_light.h"
#include "scene/light/include/directional_light.h"
#include "scene/light/include/point_light.h"

namespace ho_renderer {
class FragmentShader {
 public:
  FragmentShader();
  FragmentShader(const FragmentShader&) = delete;
  FragmentShader& operator=(const FragmentShader&) = delete;
  ~FragmentShader();

  void SetFragmentColor(Fragment& fragment, const LinearRGB& rgb) const;

  LinearRGB ComputeAmbientLighting(const AmbientLight* light,
                                   const LinearRGB& surface_color) const;
  LinearRGB ComputeDiffuseLighting(const DirectionalLight* light,
                                   const LinearRGB& surface_color,
                                   const Vector3& normal) const;
  LinearRGB ComputeDiffuseLighting(const PointLight* light, float intensity,
                                   const LinearRGB& surface_color,
                                   const Vector3& normal,
                                   const Vector3& frag_to_light) const;
  LinearRGB ComputeSpecularLighting(const DirectionalLight* light,
                                    const LinearRGB& surface_color,
                                    const Vector3& frag_to_light,
                                    const Vector3& frag_to_camera,
                                    const Vector3& normal, float coefficient,
                                    float exponent) const;
  LinearRGB ComputeSpecularLighting(const PointLight* light, float intensity,
                                    const LinearRGB& surface_color,
                                    const Vector3& normal,
                                    const Vector3& frag_to_light,
                                    const Vector3& frag_to_camera,
                                    float coefficient, float exponent) const;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_FRAGMENT_SHADER_H_