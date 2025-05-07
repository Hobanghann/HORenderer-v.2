#include "graphics/resource/include/mesh.h"

#include "graphics/resource/include/model.h"

namespace ho_renderer {

Mesh::Mesh(Model* owner, const std::string& name,
           const std::vector<Vertex>& vertices,
           const std::vector<std::uint32_t>& indices,
           std::uint32_t material_index)
    : name_(name),
      vertices_(vertices),
      indices_(indices),
      material_index_(material_index),
      material_(owner->GetMaterial(material_index)),
      sphere_bounding_volume_(*this),
      aab_bounding_volume_(*this),
      owner_(owner) {}

Mesh::Mesh(Model* owner, const std::string& name,
           const std::vector<Vertex>& vertices,
           const std::vector<std::uint32_t>& indices,
           std::uint32_t material_index,
           const AABBoundingVolume& bounding_volume)
    : name_(name),
      vertices_(vertices),
      indices_(indices),
      material_index_(material_index),
      material_(owner->GetMaterial(material_index)),
      sphere_bounding_volume_(*this),
      aab_bounding_volume_(bounding_volume),
      owner_(owner) {}

Mesh::~Mesh() = default;

const std::string& Mesh::name() const { return name_; }

const std::vector<Vertex>& Mesh::vertices() const { return vertices_; }

const std::vector<std::uint32_t>& Mesh::indices() const { return indices_; }
const Material* Mesh::material() const { return owner_->GetMaterial(material_index_); }

const SphereBoundingVolume& Mesh::sphere_bounding_volume() const {
  return sphere_bounding_volume_;
}
const AABBoundingVolume& Mesh::aab_bounding_volume() const {
  return aab_bounding_volume_;
}

}  // namespace ho_renderer
