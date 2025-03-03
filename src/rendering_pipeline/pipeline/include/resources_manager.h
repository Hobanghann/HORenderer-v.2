#ifndef _HORENDERER_RENDERINGPIPELINE_PIPELINE_RESOURCES_MANAGER_H_
#define _HORENDERER_RENDERINGPIPELINE_PIPELINE_RESOURCES_MANAGER_H_

#include <cstdint>
#include <memory>
#include <vector>

#include "asset/include/vertex.h"
#include "engine/color/include/linear_rgb.h"
#include "engine/light/include/point_light.h"
#include "math/include/affine_transform.h"
#include "math/include/vector3.h"
#include "rendering_pipeline/pipeline_objects/include/fragment.h"
#include "rendering_pipeline/pipeline_objects/include/primitive.h"
#include "rendering_pipeline/pipeline_objects/include/render_object_state.h"

namespace ho_renderer {
class ResourcesManager {
 public:
  ResourcesManager() = delete;
  ResourcesManager(const ResourcesManager &) = delete;
  ResourcesManager &operator=(const ResourcesManager &) = delete;
  ~ResourcesManager() = delete;

  static std::vector<Vertex> *GetClearVertexBuffer();
  static std::vector<std::uint32_t> *GetClearIndexBuffer();
  static std::vector<Vector3> *GetClearViewCoordinateBuffer();
  static std::vector<Vector3> *GetClearNDCBuffer();
  static std::vector<Vector3> *GetClearViewportNDCBuffer();
  static std::vector<Primitive *> *GetClearPrimitiveBuffer();
  static std::vector<Fragment> *GetClearFragmentBuffer();
  static std::vector<LinearRGB> *GetClearColorBuffer();
  static RenderObjectState *GetClearRenderObjectState();

 private:
  static std::unique_ptr<std::vector<Vertex>> vertex_buffer_;
  static std::unique_ptr<std::vector<std::uint32_t>> index_buffer_;
  static std::unique_ptr<std::vector<Vector3>> view_coordinate_buffer_;
  static std::unique_ptr<std::vector<Vector3>> ndc_buffer_;
  static std::unique_ptr<std::vector<Vector3>> viewport_ndc_buffer_;
  static std::unique_ptr<std::vector<Primitive *>> primitive_buffer_;
  static std::unique_ptr<std::vector<Fragment>> fragment_buffer_;
  static std::unique_ptr<std::vector<LinearRGB>> color_buffer_;
  static std::unique_ptr<RenderObjectState> render_object_state_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_RENDERINGPIPELINE_PIPELINE_RESOURCES_MANAGER_H_