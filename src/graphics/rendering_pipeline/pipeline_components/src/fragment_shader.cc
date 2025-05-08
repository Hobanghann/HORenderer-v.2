#include "graphics/rendering_pipeline/pipeline_components/include/fragment_shader.h"

#include "core/math/include/math_utils.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/line.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/point.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/triangle.h"
#include "tools/include/debug.h"

namespace ho_renderer {
FragmentShader::FragmentShader() = default;
FragmentShader::~FragmentShader() = default;

void FragmentShader::SetFragmentColor(Fragment& fragment,
                                      const LinearRGB& rgb) const {
  fragment.set_color(rgb);
}

LinearRGB FragmentShader::ComputeAmbientLighting(
    const AmbientLight* light, const LinearRGB& surface_color) const {
  ASSERT_MSG(
      light != nullptr,
      "FragmentShader::ComputeAmbientLighting Error : ambient light is null");
  return light->light_color() * light->light_intensity() * surface_color;
}
LinearRGB FragmentShader::ComputeDiffuseLighting(const DirectionalLight* light,
                                                 const LinearRGB& surface_color,
                                                 const Vector3& normal) const {
  ASSERT_MSG(light != nullptr,
             "FragmentShader::ComputeDiffuseLighting Error : directional light "
             "is null");
  return light->light_color() * light->light_intensity() *
         MathUtils::Maxf(0.f, normal.Dot(-light->transformed_direction())) *
         surface_color;
}
LinearRGB FragmentShader::ComputeDiffuseLighting(
    const PointLight* light, float intensity, const LinearRGB& surface_color,
    const Vector3& normal, const Vector3& frag_to_light) const {
  ASSERT_MSG(
      light != nullptr,
      "FragmentShader::ComputeDiffuseLighting Error : point light is null");
  return light->light_color() * intensity *
         MathUtils::Maxf(0.f, normal.Dot(frag_to_light)) * surface_color;
}
LinearRGB FragmentShader::ComputeSpecularLighting(
    const DirectionalLight* light, const LinearRGB& surface_color,
    const Vector3& frag_to_light, const Vector3& frag_to_camera,
    const Vector3& normal, float coefficient, float exponent) const {
  ASSERT_MSG(light != nullptr,
             "FragmentShader::ComputeSpecularLighting Error : directional "
             "light is null");
  Vector3 half_vector = (frag_to_light + frag_to_camera).GetNormalized();
  return coefficient * light->light_color() * light->light_intensity() *
         MathUtils::FastPow(MathUtils::Maxf(0.f, half_vector.Dot(normal)),
                            exponent) *
         surface_color;
}
LinearRGB FragmentShader::ComputeSpecularLighting(
    const PointLight* light, float intensity, const LinearRGB& surface_color,
    const Vector3& normal, const Vector3& frag_to_light,
    const Vector3& frag_to_camera, float coefficient, float exponent) const {
  ASSERT_MSG(
      light != nullptr,
      "FragmentShader::ComputeSpecularLighting Error : point light is null");
  Vector3 half_vector = (frag_to_light + frag_to_camera).GetNormalized();
  return coefficient * intensity * light->light_color() *
         MathUtils::FastPow(MathUtils::Maxf(0.f, half_vector.Dot(normal)),
                            exponent) *
         surface_color;
}
}  // namespace ho_renderer