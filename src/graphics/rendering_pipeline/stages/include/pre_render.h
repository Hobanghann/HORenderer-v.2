#ifndef _HORENDERER_PRE_RENDER_H_
#define _HORENDERER_PRE_RENDER_H_

#include "Scene/light/include/ambient_light.h"
#include "Scene/light/include/directional_light.h"
#include "Scene/light/include/point_light.h"
#include "graphics/rendering_pipeline/pipeline_components/include/vertex_shader.h"
#include "core/math/include/affine_transform.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/frame_buffer.h"

namespace ho_renderer {
class PreRenderStage {
 public:
  PreRenderStage();
  PreRenderStage(const PreRenderStage& stage) = delete;
  PreRenderStage& operator=(const PreRenderStage&) = delete;
  ~PreRenderStage();

  void ResetFrameBuffer(FrameBuffer& buffer) const;
  void TransformDirectionalLightToView(
      DirectionalLight* light, const AffineTransform& v_transform) const;
  void TransformPointLightToView(PointLight* light,
                                 const AffineTransform& v_transform) const;

 private:
};
}  // namespace ho_renderer

#endif  // _HORENDERER_PRE_RENDER_H_