#ifndef _HORENDERER_RENDERINGPIPELINE_PIPELINE_RESOURCES_MANAGER_H_
#define _HORENDERER_RENDERINGPIPELINE_PIPELINE_RESOURCES_MANAGER_H_

#include <cstdint>
#include <vector>

#include "asset/include/vertex.h"
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

  static std::vector<Vertex> *AllocateVertexBuffer();
  static std::vector<std::uint32_t> *AllocateIndexBuffer();
  static std::vector<Vector3> *AllocateCoordinateBuffer();
  static std::vector<Primitive *> *AllocatePrimitiveBuffer();
  static std::vector<Fragment> *AllocateFragmentBuffer();
  static std::vector<std::uint32_t> *AllocateColorBuffer();
  static RenderObjectState *AllocateRenderObjectState();

  static void DeallocateVertexBuffer();
  static void DeallocateIndexBuffer();
  static void DeallocateCoordinateBuffer();
  static void DeallocatePrimitiveBuffer();
  static void DeallocateFragmentBuffer();
  static void DeallocateColorBuffer();
  static void DeallocateRenderObjectState();

  static void DeallocateAll();

 private:
  static std::vector<Vertex> *vertex_buffer_;
  static std::vector<std::uint32_t> *index_buffer_;
  static std::vector<Vector3> *coordinate_buffer_;
  static std::vector<Primitive *> *primitive_buffer_;
  static std::vector<Fragment> *fragment_buffer_;
  static std::vector<std::uint32_t> *color_buffer_;
  static RenderObjectState *render_object_state_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_RENDERINGPIPELINE_PIPELINE_RESOURCES_MANAGER_H_