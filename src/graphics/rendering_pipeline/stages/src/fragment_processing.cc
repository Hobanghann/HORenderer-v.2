#include "graphics/rendering_pipeline/stages/include/fragment_processing.h"

#include "graphics/rendering_pipeline/pipeline_objects/include/line.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/point.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/primitive.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/triangle.h"
namespace ho_renderer {
FragmentProcessing::FragmentProcessing() = default;
FragmentProcessing::~FragmentProcessing() = default;

Fragment& FragmentProcessing::Shading(Fragment& frag,
                                      const AmbientLight* a_light,
                                      const DirectionalLight* d_light,
                                      const std::vector<PointLight*>& p_lights,
                                      const PipelineSettings& settings) const {
  const Material* material = frag.source()->material();
  LinearRGB ambient_color = settings.default_ambient_color();
  LinearRGB diffuse_color = settings.default_diffuse_color();
  LinearRGB specular_color = settings.default_specular_color();
  float coefficient = settings.default_specular_coefficient();
  float exponent = settings.default_specular_exponent();
  float opacity = settings.default_opacity();

  if (material != nullptr) {
    diffuse_color = material->diffuse_color();
    specular_color = material->specular_color();
    coefficient = material->specular_coefficient();
    exponent = material->specular_exponent();
    opacity = material->opaque();
  }

  Vector3 frag_pos;
  Vector3 frag_normal;
  Vector3 frag_to_camera;
  Vector3 d_frag_to_light;
  std::vector<Vector3> p_frag_to_lights;
  std::vector<float> p_intensities;

  LinearRGB ambient_light;
  LinearRGB diffuse_light;
  LinearRGB specular_light;

  switch (settings.primitive_type()) {
    case kPoint:
    case kLine:
      frag.set_color(diffuse_color);
      return frag;
      break;
    case kTriangle:
      switch (settings.rendering_mode()) {
        case kWireFrame:
          frag.set_color(diffuse_color);
          return frag;
          break;
        case kFill:
          break;
        case kTextureMapping:
          const Vector3 uv = frag.uv_coord();
          if (material->GetTexture(Ambient) != nullptr) {
            ambient_color =
                material->GetTexture(Ambient)->GetTexel(uv.x(), uv.y());
          }
          if (material->GetTexture(Diffuse) != nullptr) {
            diffuse_color =
                material->GetTexture(Diffuse)->GetTexel(uv.x(), uv.y());
          }
           if (material->GetTexture(Specular) != nullptr) {
            specular_color =
                material->GetTexture(Specular)->GetTexel(uv.x(), uv.y());
          }
          if (material->GetTexture(SpecularHighlight) != nullptr) {
            exponent = material->GetTexture(SpecularHighlight)
                           ->GetTexel(uv.x(), uv.y())
                           .red() *
                       1.f;
          }
          if (material->GetTexture(Alpha) != nullptr) {
            opacity =
                material->GetTexture(Alpha)->GetTexel(uv.x(), uv.y()).red();
          }
          if (material->GetTexture(Normal) != nullptr) {
            Vector3 bitangent =
                frag.handedness() *
                (frag.fragment_normal().Cross(frag.tangent())).GetNormalized();
            LinearTransform tbn(
                Matrix3x3(frag.tangent().GetNormalized(), bitangent,
                          frag.fragment_normal().GetNormalized()));
            Vector3 normal =
                material->GetTexture(Normal)->GetVector(uv.x(), uv.y());
            frag_normal = tbn.Transform(normal);
          }
          break;
      }

      if (material->GetTexture(Normal) == nullptr) {
        switch (settings.shading_mode()) {
          case kFlat:
            frag_pos = static_cast<const Triangle*>(frag.source())->center();
            frag_normal = static_cast<const Triangle*>(frag.source())
                              ->normal()
                              .GetNormalized();

            break;
          case kPhong:
            frag_pos = frag.view_coord();
            frag_normal = frag.fragment_normal().GetNormalized();
        }
        break;
      }
  }

  frag_to_camera = -frag_pos.GetNormalized();
  d_frag_to_light = -d_light->transformed_direction().GetNormalized();
  for (auto p : p_lights) {
    p_frag_to_lights.emplace_back(
        (p->transformed_coord() - frag_pos).GetNormalized());
    p_intensities.emplace_back(p->GetIntensityAt(frag_pos));
  }

  if (settings.is_using_ambient_lighting()) {
    ambient_light =
        fragment_shader_.ComputeAmbientLighting(a_light, ambient_color);
  }
  if (settings.is_using_diffuse_lighting()) {
    diffuse_light += fragment_shader_.ComputeDiffuseLighting(
        d_light, diffuse_color, frag_normal);
  }
  if (settings.is_using_specular_lighting()) {
    specular_light += fragment_shader_.ComputeSpecularLighting(
        d_light, specular_color, d_frag_to_light, frag_to_camera, frag_normal,
        coefficient, exponent);
  }
  for (int i = 0; i < p_lights.size(); i++) {
    if (settings.is_using_diffuse_lighting()) {
      diffuse_light += fragment_shader_.ComputeDiffuseLighting(
          p_lights[i], p_intensities[i], diffuse_color, frag_normal,
          p_frag_to_lights[i]);
    }
    if (settings.is_using_specular_lighting()) {
      specular_light += fragment_shader_.ComputeSpecularLighting(
          p_lights[i], p_intensities[i], specular_color, p_frag_to_lights[i],
          frag_to_camera, frag_normal, coefficient, exponent);
    }
  }

  LinearRGB final_color = ambient_light + diffuse_light + specular_light;
  final_color.set_alpha(opacity);
  fragment_shader_.SetFragmentColor(frag, final_color);

  return frag;
}

}  // namespace ho_renderer