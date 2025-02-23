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

std::vector<Primitive*>* ho_renderer::PrimitiveAssemblyShader::AssemblePoint(
    const std::vector<uint32_t>& index_buffer) {
  std::vector<Primitive*>* primitive_buffer =
      ResourcesManager::AllocatePrimitiveBuffer();
  for (int i = 0; i < index_buffer.size(); i += 1) {
    primitive_buffer->push_back(new Point(index_buffer[i]));
  }
  return primitive_buffer;
}
std::vector<Primitive*>* ho_renderer::PrimitiveAssemblyShader::AssembleLine(
    const std::vector<uint32_t>& index_buffer) {
  std::vector<Primitive*>* primitive_buffer =
      ResourcesManager::AllocatePrimitiveBuffer();
  for (int i = 0; i < index_buffer.size(); i += 2) {
    primitive_buffer->push_back(new Line(index_buffer[i], index_buffer[i + 1]));
  }
  return primitive_buffer;
}
std::vector<Primitive*>* ho_renderer::PrimitiveAssemblyShader::AssembleTriangle(
    const std::vector<uint32_t>& index_buffer) {
  std::vector<Primitive*>* primitive_buffer =
      ResourcesManager::AllocatePrimitiveBuffer();
  for (int i = 0; i < index_buffer.size(); i += 3) {
    primitive_buffer->push_back(new Triangle(
        index_buffer[i], index_buffer[i + 1], index_buffer[i + 2]));
  }
  return primitive_buffer;
}

std::vector<Primitive*>*
ho_renderer::PrimitiveAssemblyShader::AssembleFilledPoint(
    const std::vector<uint32_t>& index_buffer,
    const std::vector<uint32_t>& primitive_color_buffer) {
  std::vector<Primitive*>* primitive_buffer =
      ResourcesManager::AllocatePrimitiveBuffer();
  int index_primitive = 0;
  for (int i = 0; i < index_buffer.size(); i += 1) {
    primitive_buffer->push_back(
        new Point(index_buffer[i], primitive_color_buffer[index_primitive]));
    index_primitive++;
  }
  return primitive_buffer;
}
std::vector<Primitive*>*
ho_renderer::PrimitiveAssemblyShader::AssembleFilledLine(
    const std::vector<uint32_t>& index_buffer,
    const std::vector<uint32_t>& primitive_color_buffer) {
  std::vector<Primitive*>* primitive_buffer =
      ResourcesManager::AllocatePrimitiveBuffer();
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
ho_renderer::PrimitiveAssemblyShader::AssembleFilledTriangle(
    const std::vector<uint32_t>& index_buffer,
    const std::vector<uint32_t>& primitive_color_buffer) {
  std::vector<Primitive*>* primitive_buffer =
      ResourcesManager::AllocatePrimitiveBuffer();
  int index_primitive = 0;
  for (int i = 0; i < index_buffer.size(); i += 3) {
    primitive_buffer->push_back(
        new Triangle(index_buffer[i], index_buffer[i + 1], index_buffer[i + 2],
                     primitive_color_buffer[index_primitive]));
    index_primitive++;
  }
  return primitive_buffer;
}

}  // namespace ho_renderer
