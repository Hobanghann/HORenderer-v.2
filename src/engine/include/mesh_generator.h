#ifndef _HORENDERER_ASSET_MESH_GENERATOR_H_
#define _HORENDERER_ASSET_MESH_GENERATOR_H_

#include <cstdint>
#include <vector>

#include "asset/include/mesh.h"
#include "asset/include/vertex.h"

namespace ho_renderer {
class MeshGenerator {
 public:
  static const Mesh* GenerateSphere(const int latitude_num,
                                    const int longitude_num, const float radius,
                                    const std::uint32_t color_bit);
  static const Mesh* GenerateSphere(
      const int latitude_num, const int longitude_num, const float radius,
      const std::vector<std::uint32_t>& color_buffer);
  static const Mesh* GenerateBox(const float box_width, const float box_depth,
                                 const float box_height,
                                 const std::uint32_t color_bit);
  static const Mesh* GenerateBox(
      const float box_width, const float box_depth, const float box_height,
      const std::vector<std::uint32_t>& color_buffer);
  static const Mesh* GeneratePlane(const float plane_width,
                                   const float plane_height,
                                   const std::uint32_t color_bit);
  static const Mesh* GeneratePlane(
      const float plane_width, const float plane_height,
      const std::vector<std::uint32_t>& color_buffer);

 private:
};
}  // namespace ho_renderer

#endif