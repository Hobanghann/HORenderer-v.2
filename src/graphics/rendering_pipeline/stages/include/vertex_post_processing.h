#ifndef _HORENDERER_VERTEX_POST_PROCESSING_H_
#define _HORENDERER_VERTEX_POST_PROCESSING_H_

// Respolsibility : define how pipeline_components work.

#include <vector>

#include "core/math/include/frustum.h"
#include "graphics/rendering_pipeline/pipeline_components/include/clipper.h"
#include "graphics/rendering_pipeline/pipeline_components/include/face_culler.h"
#include "graphics/rendering_pipeline/pipeline_components/include/frustum_culler.h"
#include "graphics/rendering_pipeline/pipeline_components/include/perspective_divider.h"
#include "graphics/rendering_pipeline/pipeline_components/include/primitive_assembler.h"
#include "graphics/rendering_pipeline/pipeline_components/include/viewport_transformer.h"
#include "graphics/rendering_pipeline/system/include/pipeline_settings.h"
#include "graphics/resource/include/mesh.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/primitive.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/transformed_vertex.h"

namespace ho_renderer {

class VertexPostProcessing {
 public:
  VertexPostProcessing();
  VertexPostProcessing(const VertexPostProcessing &) = delete;
  VertexPostProcessing &operator=(const VertexPostProcessing &) = delete;
  ~VertexPostProcessing();

  FrustumCullingResult CullMesh(const Mesh *mesh, const Frustum &frustum,
                                const PipelineSettings &settings) const;

  std::vector<std::unique_ptr<Primitive>> *AssemblePrimitives(
      std::vector<std::unique_ptr<Primitive>> *output_p_buffer,
      const std::vector<TransformedVertex> *vertex_buffer,
      const std::vector<std::uint32_t> &index_buffer, const Material *material,
      const PipelineSettings &settings) const;

  void ClipPrimitives(std::vector<std::unique_ptr<Primitive>> *p_buffer,
                      std::vector<TransformedVertex> *v_buffer,
                      const PipelineSettings &settings) const;

  std::vector<TransformedVertex> *PerspectiveDivideVertices(
      std::vector<TransformedVertex> *v_buffer) const;

  void CullBackfaces(std::vector<std::unique_ptr<Primitive>> *triangle_buffer,
                     std::vector<TransformedVertex> *v_buffer,
                     const PipelineSettings &settings) const;

  std::vector<TransformedVertex> *TransformNDCToViewport(
      std::vector<TransformedVertex> *v_buffer,
      const PipelineSettings &settings) const;

 private:
  // pipeline_components
  PrimitiveAssembler primitive_assembler_;
  FrustumCuller frustum_culler_;
  PerspectiveDivider perspective_divider_;
  FaceCuller face_culler_;
  Clipper clipper_;
  ViewportTransformer viewport_transformer_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_VERTEX_POST_PROCESSING_H_
