#ifndef _HORENDERER_OBJECT_MODEL_H_
#define _HORENDERER_OBJECT_MODEL_H_

#include <string>
#include <vector>

#include "graphics/resource/include/aab_bounding_volume.h"
#include "graphics/resource/include/material.h"
#include "graphics/resource/include/sphere_bounding_volume.h"
#include "graphics/resource/include/vertex.h"

namespace ho_renderer {
class Model;
class Mesh {
 public:
  Mesh() = delete;
  Mesh(const Mesh&) = delete;
  Mesh(Model* owner, const std::string& name,
       const std::vector<Vertex>& vertices,
       const std::vector<std::uint32_t>& indices, std::uint32_t material_index);
  Mesh(Model* owner, const std::string& name,
       const std::vector<Vertex>& vertices,
       const std::vector<std::uint32_t>& indices, std::uint32_t material_index,
       const AABBoundingVolume& bounding_volume);
  Mesh& operator=(const Mesh&) = delete;
  ~Mesh();

  const std::string& name() const;
  const std::vector<Vertex>& vertices() const;
  const std::vector<std::uint32_t>& indices() const;
  const Material* material() const;
  const SphereBoundingVolume& sphere_bounding_volume() const;
  const AABBoundingVolume& aab_bounding_volume() const;

 private:
  std::string name_;
  std::vector<Vertex> vertices_;
  std::vector<std::uint32_t> indices_;
  std::uint32_t material_index_;
  const Material* material_;
  SphereBoundingVolume sphere_bounding_volume_;
  AABBoundingVolume aab_bounding_volume_;

  Model* owner_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_OBJECT_MODEL_H_