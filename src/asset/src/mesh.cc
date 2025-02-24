#include "asset/include/mesh.h"

#include <vector>

#include "app/include/debug.h"
#include "asset/include/vertex.h"
#include "engine/include/srgb.h"
#include "math/include/vector3.h"
#include "rendering_pipeline/pipeline/include/pipeline_settings.h"

namespace ho_renderer {

Mesh::Mesh(const std::vector<Vertex>& vertex_buffer,
           const std::vector<std::uint32_t>& index_buffer,
           const PrimitiveType primitive_type)
    : vertex_buffer_(vertex_buffer),
      index_buffer_(index_buffer),
      sphere_bounding_volume_(*this),
      aab_bounding_volume_(*this),
      primitive_type_(primitive_type) {}

Mesh::Mesh(const std::vector<Vertex>& vertex_buffer,
           const std::vector<std::uint32_t>& index_buffer,
           const std::vector<std::uint32_t>& primitive_color_buffer,
           const PrimitiveType primitive_type)
    : vertex_buffer_(vertex_buffer),
      index_buffer_(index_buffer),
      primitive_color_buffer_(primitive_color_buffer),
      sphere_bounding_volume_(*this),
      aab_bounding_volume_(*this),
      primitive_type_(primitive_type) {}
Mesh::Mesh(const Mesh& mesh) = default;
Mesh& Mesh::operator=(const Mesh& mesh) = default;
Mesh::~Mesh() = default;

const std::vector<Vertex>& Mesh::vertex_buffer() const {
  return vertex_buffer_;
}
const std::vector<std::uint32_t>& Mesh::index_buffer() const {
  return index_buffer_;
}
const std::vector<std::uint32_t>& Mesh::primitive_color_buffer() const {
  return primitive_color_buffer_;
}
const SphereBoundingVolume& Mesh::sphere_bounding_volume() const {
  return sphere_bounding_volume_;
}
const AABBoundingVolume& Mesh::aab_bounding_volume() const {
  return aab_bounding_volume_;
}
const PrimitiveType Mesh::primitive_type() const { return primitive_type_; }
}  // namespace ho_renderer