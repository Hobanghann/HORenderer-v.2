#include "rendering_pipeline/shaders/include/primitive_assembly_shader.h"

#include <vector>

#include "app/include/debug.h"
#include "rendering_pipeline/pipeline/include/resources_manager.h"
#include "rendering_pipeline/pipeline_objects/include/line.h"
#include "rendering_pipeline/pipeline_objects/include/point.h"
#include "rendering_pipeline/pipeline_objects/include/primitive.h"
#include "rendering_pipeline/pipeline_objects/include/triangle.h"

namespace ho_renderer {
PrimitiveAssemblyShader::PrimitiveAssemblyShader() = default;
PrimitiveAssemblyShader::~PrimitiveAssemblyShader() = default;

std::vector<Primitive*>*
ho_renderer::PrimitiveAssemblyShader::AssembleTexturedPoint(
    const std::vector<uint32_t>& index_buffer) {
  std::vector<Primitive*>* primitive_buffer =
      ResourcesManager::GetClearPrimitiveBuffer();
  for (int i = 0; i < index_buffer.size(); i += 1) {
    primitive_buffer->push_back(new Point(index_buffer[i]));
  }
  return primitive_buffer;
}
std::vector<Primitive*>*
ho_renderer::PrimitiveAssemblyShader::AssembleTexturedLine(
    const std::vector<uint32_t>& index_buffer) {
  std::vector<Primitive*>* primitive_buffer =
      ResourcesManager::GetClearPrimitiveBuffer();
  for (int i = 0; i < index_buffer.size(); i += 2) {
    primitive_buffer->push_back(new Line(index_buffer[i], index_buffer[i + 1]));
  }
  return primitive_buffer;
}
std::vector<Primitive*>*
ho_renderer::PrimitiveAssemblyShader::AssembleTexturedTriangle(
    const std::vector<uint32_t>& index_buffer,
    const std::vector<Vector3>& view_coordinate_buffer) {
  std::vector<Primitive*>* primitive_buffer =
      ResourcesManager::GetClearPrimitiveBuffer();
  for (int i = 0; i < index_buffer.size(); i += 3) {
    const Vector3& i0_to_i1 = view_coordinate_buffer[index_buffer[i]] -
                              view_coordinate_buffer[index_buffer[i + 1]];
    const Vector3& i0_to_i2 = view_coordinate_buffer[index_buffer[i]] -
                              view_coordinate_buffer[index_buffer[i + 2]];
    Triangle* new_triangle =
        new Triangle(index_buffer[i], index_buffer[i + 1], index_buffer[i + 2],
                     i0_to_i1.Cross(i0_to_i2).GetNormalized());
    new_triangle->set_specular_reflection_coefficient(1.f).set_shininess(100.f);
    primitive_buffer->push_back(new_triangle);
  }
  return primitive_buffer;
}

std::vector<Primitive*>*
ho_renderer::PrimitiveAssemblyShader::AssembleColoredPoint(
    const std::vector<uint32_t>& index_buffer,
    const std::vector<LinearRGB>& primitive_color_buffer) {
  std::vector<Primitive*>* primitive_buffer =
      ResourcesManager::GetClearPrimitiveBuffer();
  int index_primitive = 0;
  for (int i = 0; i < index_buffer.size(); i += 1) {
    primitive_buffer->push_back(
        new Point(index_buffer[i], primitive_color_buffer[index_primitive]));
    index_primitive++;
  }
  return primitive_buffer;
}
std::vector<Primitive*>*
ho_renderer::PrimitiveAssemblyShader::AssembleColoredLine(
    const std::vector<uint32_t>& index_buffer,
    const std::vector<LinearRGB>& primitive_color_buffer) {
  std::vector<Primitive*>* primitive_buffer =
      ResourcesManager::GetClearPrimitiveBuffer();
  int index_primitive = 0;
  for (int i = 0; i < index_buffer.size(); i += 2) {
    primitive_buffer->push_back(
        new Line(index_buffer[i], index_buffer[i + 1],
                 primitive_color_buffer[index_primitive]));
    index_primitive++;
  }
  return primitive_buffer;
}
std::vector<Primitive*>*
ho_renderer::PrimitiveAssemblyShader::AssembleColoredTriangle(
    const std::vector<uint32_t>& index_buffer,
    const std::vector<Vector3>& view_coordinate_buffer,
    const std::vector<LinearRGB>& primitive_color_buffer) {
  std::vector<Primitive*>* primitive_buffer =
      ResourcesManager::GetClearPrimitiveBuffer();
  int index_primitive = 0;
  for (int i = 0; i < index_buffer.size(); i += 3) {
    const Vector3& i0_to_i1 = view_coordinate_buffer[index_buffer[i]] -
                              view_coordinate_buffer[index_buffer[i + 1]];
    const Vector3& i0_to_i2 = view_coordinate_buffer[index_buffer[i]] -
                              view_coordinate_buffer[index_buffer[i + 2]];
    Triangle* new_triangle =
        new Triangle(index_buffer[i], index_buffer[i + 1], index_buffer[i + 2],
                     i0_to_i1.Cross(i0_to_i2).GetNormalized(),
                     primitive_color_buffer[index_primitive]);
    new_triangle->set_specular_reflection_coefficient(1.f).set_shininess(100.f);
    primitive_buffer->push_back(new_triangle);
    index_primitive++;
  }
  return primitive_buffer;
}

}  // namespace ho_renderer
