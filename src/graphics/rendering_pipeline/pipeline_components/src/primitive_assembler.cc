#include "graphics/rendering_pipeline/pipeline_components/include/primitive_assembler.h"

#include <cstdint>
#include <vector>

#include "core/math/include/vector3.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/line.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/point.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/primitive.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/transformed_vertex.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/triangle.h"
#include "graphics/rendering_pipeline/system/include/pipeline_enum.h"
#include "tools/include/debug.h"

namespace ho_renderer {
PrimitiveAssembler::PrimitiveAssembler() = default;
PrimitiveAssembler::~PrimitiveAssembler() = default;

std::vector<std::unique_ptr<Primitive>>* PrimitiveAssembler::AssemblePoint(
    std::vector<std::unique_ptr<Primitive>>* output_p_buffer,
    const std::vector<TransformedVertex>* v_buffer,
    const std::vector<std::uint32_t>& i_buffer,
    const Material* material) const {
  ASSERT_MSG(output_p_buffer != nullptr,
             "PrimitiveAssembler::AssemblePoint Error : output primitive "
             "buffer is null");
  ASSERT_MSG(v_buffer != nullptr,
             "PrimitiveAssembler::AssemblePoint Error : vertex buffer is null");
  if (output_p_buffer == nullptr || v_buffer == nullptr) {
    return nullptr;
  }
  for (auto itr = i_buffer.cbegin(); itr != i_buffer.cend(); itr++) {
    output_p_buffer->push_back(std::make_unique<Point>(material, *itr));
  }
  return output_p_buffer;
}
std::vector<std::unique_ptr<Primitive>>* PrimitiveAssembler::AssembleLine(
    std::vector<std::unique_ptr<Primitive>>* output_p_buffer,
    const std::vector<TransformedVertex>* v_buffer,
    const std::vector<std::uint32_t>& i_buffer,
    const Material* material) const {
  ASSERT_MSG(output_p_buffer != nullptr,
             "PrimitiveAssembler::AssembleLine Error : output primitive "
             "buffer is null");
  ASSERT_MSG(v_buffer != nullptr,
             "PrimitiveAssembler::AssembleLine Error : vertex buffer is null");
  ASSERT_MSG(material != nullptr,
             "PrimitiveAssembler::AssembleLine Error : material is null");
  if (output_p_buffer == nullptr || v_buffer == nullptr ||
      material == nullptr) {
    return nullptr;
  }
  for (auto itr = i_buffer.cbegin(); itr != i_buffer.cend(); itr += 2) {
    output_p_buffer->push_back(
        std::make_unique<Line>(material, *itr, *(itr + 1)));
  }
  return output_p_buffer;
}

std::vector<std::unique_ptr<Primitive>>* PrimitiveAssembler::AssembleTriangle(
    std::vector<std::unique_ptr<Primitive>>* output_p_buffer,
    const std::vector<TransformedVertex>* v_buffer,
    const std::vector<std::uint32_t>& i_buffer, const Material* material,
    IndexOrder order) const {
  ASSERT_MSG(output_p_buffer != nullptr,
             "PrimitiveAssembler::AssembleTriangle Error : output primitive "
             "buffer is null");
  ASSERT_MSG(
      v_buffer != nullptr,
      "PrimitiveAssembler::AssembleTriangle Error : vertex buffer is null");
  ASSERT_MSG(material != nullptr,
             "PrimitiveAssembler::AssembleTriangle Error : material is null");
  if (output_p_buffer == nullptr || v_buffer == nullptr ||
      material == nullptr) {
    return nullptr;
  }
  for (auto itr = i_buffer.cbegin(); itr != i_buffer.cend(); itr += 3) {
    Vector3 v_0_to_1 =
        (*v_buffer)[*(itr + 1)].view_coord() - (*v_buffer)[*itr].view_coord();
    Vector3 v_0_to_2 =
        (*v_buffer)[*(itr + 2)].view_coord() - (*v_buffer)[*itr].view_coord();
    Vector3 normal;
    switch (order) {
      case kClockWise:
        normal = v_0_to_2.Cross(v_0_to_1);
        break;
      case kCounterClockWise:
        normal = v_0_to_1.Cross(v_0_to_2);
        break;
    }
    Vector3 center = 0.33f * ((*v_buffer)[*itr].view_coord() +
                              (*v_buffer)[*(itr + 1)].view_coord() +
                              (*v_buffer)[*(itr + 2)].view_coord());
    output_p_buffer->push_back(std::make_unique<Triangle>(
        material, *itr, *(itr + 1), *(itr + 2), normal, center));
  }
  return output_p_buffer;
}
}  // namespace ho_renderer
