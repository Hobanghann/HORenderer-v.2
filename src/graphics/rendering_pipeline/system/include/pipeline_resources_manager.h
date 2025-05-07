#ifndef _HORENDERER_PIPELINE_RESOURCES_MANAGER_H_
#define _HORENDERER_PIPELINE_RESOURCES_MANAGER_H_

#include <cstdint>
#include <memory>
#include <vector>

#include "graphics/rendering_pipeline/pipeline_objects/include/fragment.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/primitive.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/transformed_vertex.h"

namespace ho_renderer {
class PipelineResourcesManager {
 public:
  PipelineResourcesManager();
  PipelineResourcesManager(const PipelineResourcesManager &) = delete;
  PipelineResourcesManager &operator=(const PipelineResourcesManager &) =
      delete;
  ~PipelineResourcesManager();

  std::vector<TransformedVertex> *GetClearVertexBuffer();
  std::vector<std::unique_ptr<Primitive>> *GetClearPrimitiveBuffer();
  std::vector<Fragment> *GetClearFragmentBuffer();

  PipelineResourcesManager &ReturnVertexBuffer(
      std::vector<TransformedVertex> *buffer);
  PipelineResourcesManager &ReturnPrimitiveBuffer(
      std::vector<std::unique_ptr<Primitive>> *buffer);
  PipelineResourcesManager &ReturnFragmentBuffer(std::vector<Fragment> *buffer);

 private:
  template <typename T>
  std::vector<T> *GetClearBuffer(
      std::vector<std::unique_ptr<std::vector<T>>> &buffers,
      std::vector<bool> &usage_flags);

  template <typename T>
  PipelineResourcesManager &ReturnBuffer(
      std::vector<std::unique_ptr<std::vector<T>>> &buffers,
      std::vector<bool> &usage_flags, std::vector<T> *buffer);

  std::vector<std::unique_ptr<std::vector<TransformedVertex>>> vertex_buffers_;
  std::vector<bool> vertex_buffer_used_;
  std::vector<std::unique_ptr<std::vector<std::unique_ptr<Primitive>>>>
      primitive_buffers_;
  std::vector<bool> primitive_buffer_used_;
  std::vector<std::unique_ptr<std::vector<Fragment>>> fragment_buffers_;
  std::vector<bool> fragment_buffer_used_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_PIPELINE_RESOURCES_MANAGER_H_