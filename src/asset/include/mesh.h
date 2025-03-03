#ifndef _HORENDERER_ASSET_MESH_H_
#define _HORENDERER_ASSET_MESH_H_

#include <cstdint>
#include <string>
#include <vector>

#include "asset/include/aab_bounding_volume.h"
#include "asset/include/sphere_bounding_volume.h"
#include "asset/include/vertex.h"
#include "engine/color/include/linear_rgb.h"
#include "rendering_pipeline/pipeline/include/pipeline_settings.h"

namespace ho_renderer {
class Mesh {
 public:
  Mesh() = delete;
  Mesh(const std::string& name, const std::vector<Vertex>& vertex_buffer,
       const std::vector<std::uint32_t>& index_buffer,
       const PrimitiveType ptimitive_type);
  Mesh(const std::string& name, const std::vector<Vertex>& vertex_buffer,
       const std::vector<std::uint32_t>& index_buffer,
       const std::vector<LinearRGB>& primitive_color_buffer,
       const PrimitiveType ptimitive_type);
  Mesh(const Mesh& mesh);
  Mesh& operator=(const Mesh& mesh);
  ~Mesh();

  const std::string& name() const;
  const std::vector<Vertex>& vertex_buffer() const;
  const std::vector<std::uint32_t>& index_buffer() const;
  const std::vector<LinearRGB>& primitive_color_buffer() const;
  const SphereBoundingVolume& sphere_bounding_volume() const;
  const AABBoundingVolume& aab_bounding_volume() const;
  const PrimitiveType primitive_type() const;

 private:
  std::string name_;
  std::vector<Vertex> vertex_buffer_;
  std::vector<std::uint32_t> index_buffer_;
  std::vector<LinearRGB> primitive_color_buffer_;
  SphereBoundingVolume sphere_bounding_volume_;
  AABBoundingVolume aab_bounding_volume_;
  PrimitiveType primitive_type_;
};
}  // namespace ho_renderer
#endif  // _HORENDERER_ASSET_MESH_H_