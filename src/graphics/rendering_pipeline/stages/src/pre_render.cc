#include "graphics/rendering_pipeline/stages/include/pre_render.h"

#include "Scene/light/include/ambient_light.h"
#include "Scene/light/include/directional_light.h"
#include "Scene/light/include/point_light.h"
#include "core/math/include/affine_transform.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/frame_buffer.h"
#include "tools/include/debug.h"

namespace ho_renderer {
PreRenderStage::PreRenderStage() = default;
PreRenderStage::~PreRenderStage() = default;

void PreRenderStage::ResetFrameBuffer(FrameBuffer& buffer) const {
  buffer.ResetBuffers();
}
void PreRenderStage::TransformDirectionalLightToView(
    DirectionalLight* light, const AffineTransform& v_transform) const {
  if (light == nullptr) {
    return;
  }
  light->set_transformed_direction(
      v_transform.Transform(Vector4(light->light_direction()))
          .ToVector3()
          .GetNormalized());
}
void PreRenderStage::TransformPointLightToView(
    PointLight* light, const AffineTransform& v_transform) const {
  if (light == nullptr) {
    return;
  }
  light->set_transformed_coord(
      v_transform.Transform(light->world_coord()).ToVector3().GetNormalized());
}
}  // namespace ho_renderer