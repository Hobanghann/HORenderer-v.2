#ifndef _HORENDERER_FRAGMENT_PROCESSING_H_
#define _HORENDERER_FRAGMENT_PROCESSING_H_

#include <cstdint>
#include <memory>
#include <vector>

#include "graphics/rendering_pipeline/pipeline_components/include/fragment_shader.h"
#include "graphics/rendering_pipeline/system/include/pipeline_settings.h"
#include "scene/light/include/ambient_light.h"
#include "scene/light/include/directional_light.h"
#include "scene/light/include/point_light.h"
#include "scene/system/include/scene.h"

namespace ho_renderer {
class FragmentProcessing {
 public:
  FragmentProcessing();
  ~FragmentProcessing();

  Fragment& Shading(Fragment& fragment, const AmbientLight* a_light,
                    const DirectionalLight* d_light,
                    const std::vector<PointLight*>& p_lights,
                    const PipelineSettings& settings) const;

 private:
  FragmentShader fragment_shader_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_FRAGMENT_PROCESSING_H_