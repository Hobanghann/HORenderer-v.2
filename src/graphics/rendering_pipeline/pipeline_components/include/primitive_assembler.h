#ifndef _HORENDERER_PRIMITIVE_ASSEMBLER_H_
#define _HORENDERER_PRIMITIVE_ASSEMBLER_H_

// Responsibility : After read index buffer, assemble index to primitive.
//                  If there is remain index in index buffer, ignore.
#include <cstdint>
#include <memory>
#include <vector>

#include "graphics/rendering_pipeline/pipeline_objects/include/primitive.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/transformed_vertex.h"
#include "graphics/rendering_pipeline/system/include/pipeline_enum.h"

namespace ho_renderer {
class PrimitiveAssembler {
 public:
  PrimitiveAssembler();
  PrimitiveAssembler(const PrimitiveAssembler&) = delete;
  PrimitiveAssembler& operator=(const PrimitiveAssembler&) = delete;
  ~PrimitiveAssembler();

  std::vector<std::unique_ptr<Primitive>>* AssemblePoint(
      std::vector<std::unique_ptr<Primitive>>* output_p_buffer,
      const std::vector<TransformedVertex>* v_buffer,
      const std::vector<std::uint32_t>& i_buffer,
      const Material* material) const;
  std::vector<std::unique_ptr<Primitive>>* AssembleLine(
      std::vector<std::unique_ptr<Primitive>>* output_p_buffer,
      const std::vector<TransformedVertex>* v_buffer,
      const std::vector<std::uint32_t>& i_buffer,
      const Material* material) const;
  std::vector<std::unique_ptr<Primitive>>* AssembleTriangle(
      std::vector<std::unique_ptr<Primitive>>* output_p_buffer,
      const std::vector<TransformedVertex>* v_buffer,
      const std::vector<std::uint32_t>& i_buffer, const Material* material,
      IndexOrder order) const;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_PRIMITIVE_ASSEMBLER_H_