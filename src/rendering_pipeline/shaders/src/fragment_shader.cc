#include "rendering_pipeline/shaders/include/fragment_shader.h"

#include "app/include/debug.h"
#include "math/include/math_utils.h"
#include "rendering_pipeline/pipeline_objects/include/line.h"
#include "rendering_pipeline/pipeline_objects/include/point.h"
#include "rendering_pipeline/pipeline_objects/include/triangle.h"

namespace ho_renderer {
FragmentShader::FragmentShader() = default;
FragmentShader::~FragmentShader() = default;

void FragmentShader::SetFragmentColor(Fragment& fragment,
                                      const LinearRGB& rgb) const {
  fragment.set_color(rgb);
}

const LinearRGB& FragmentShader::GetPrimitiveColor(Fragment& fragment) const {
  LinearRGB read_rgb;
  switch (fragment.belonging_primitive_type()) {
    case kPOINT:
      read_rgb =
          static_cast<const Point&>(fragment.belonging_primitive()).color();
      break;
    case kLINE:
      read_rgb =
          static_cast<const Line&>(fragment.belonging_primitive()).color();
      break;
    case kTRIANGLE:
      read_rgb =
          static_cast<const Triangle&>(fragment.belonging_primitive()).color();
      break;
  }
  return read_rgb;
}

const LinearRGB& FragmentShader::ComputeAmbientLighting(
    const AmbientLight& light) const {
  return light.light_intensity() * light.light_color();
}
const LinearRGB& FragmentShader::ComputeDiffuseLighting(
    Fragment& fragment, const DirectionalLight& light) const {
  Vector3 normal_vector =
      (static_cast<const Triangle&>(fragment.belonging_primitive()))
          .normal_vector();
  return light.light_intensity() *
         MathUtils::Maxf(
             0.f, normal_vector.Dot(-1.f * light.transformed_direction())) *
         light.light_color();
}
const LinearRGB& FragmentShader::ComputeDiffuseLighting(
    Fragment& fragment, const PointLight& light) const {
  Vector3 frag_to_light =
      (light.transformed_coordinate() - fragment.view_coordinate())
          .GetNormalized();
  Vector3 normal_vector =
      (static_cast<const Triangle&>(fragment.belonging_primitive()))
          .normal_vector();
  return light.GetIntensityAt(fragment.view_coordinate()) *
         MathUtils::Maxf(0.f, normal_vector.Dot(frag_to_light)) *
         light.light_color();
}
const LinearRGB& FragmentShader::ComputeDiffuseLighting(
    Fragment& fragment, const PointLight& light, const float intensity) const {
  Vector3 frag_to_light =
      (light.transformed_coordinate() - fragment.view_coordinate())
          .GetNormalized();
  Vector3 normal_vector =
      (static_cast<const Triangle&>(fragment.belonging_primitive()))
          .normal_vector();
  return intensity * MathUtils::Maxf(0.f, normal_vector.Dot(frag_to_light)) *
         light.light_color();
}
const LinearRGB& FragmentShader::ComputeSpecularLighting(
    Fragment& fragment, const PointLight& light) const {
  Vector3 frag_to_light =
      (light.transformed_coordinate() - fragment.view_coordinate());
  Vector3 frag_to_view = -1.f * fragment.view_coordinate();
  Vector3 half_vector = (frag_to_light + frag_to_view).GetNormalized();
  Vector3 normal_vector =
      (static_cast<const Triangle&>(fragment.belonging_primitive()))
          .normal_vector();
  float coefficient =
      (static_cast<const Triangle&>(fragment.belonging_primitive()))
          .specular_reflection_coefficient();
  float shininess =
      (static_cast<const Triangle&>(fragment.belonging_primitive()))
          .shininess();
  return coefficient * light.GetIntensityAt(fragment.view_coordinate()) *
         MathUtils::Pow(MathUtils::Maxf(0.f, half_vector.Dot(normal_vector)),
                        shininess) *
         light.light_color();
}
const LinearRGB& FragmentShader::ComputeSpecularLighting(
    Fragment& fragment, const PointLight& light, const float intensity) const {
  Vector3 frag_to_light =
      (light.transformed_coordinate() - fragment.view_coordinate());
  Vector3 frag_to_view = -1.f * fragment.view_coordinate();
  Vector3 half_vector = (frag_to_light + frag_to_view).GetNormalized();
  Vector3 normal_vector =
      (static_cast<const Triangle&>(fragment.belonging_primitive()))
          .normal_vector();
  float coefficient =
      (static_cast<const Triangle&>(fragment.belonging_primitive()))
          .specular_reflection_coefficient();
  float shininess =
      (static_cast<const Triangle&>(fragment.belonging_primitive()))
          .shininess();
  return intensity *
         MathUtils::Pow(MathUtils::Maxf(0.f, half_vector.Dot(normal_vector)),
                        shininess) *
         light.light_color();
}
}  // namespace ho_renderer