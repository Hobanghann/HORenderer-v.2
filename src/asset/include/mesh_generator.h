#ifndef _HORENDERER_ASSET_MESH_GENERATOR_H_
#define _HORENDERER_ASSET_MESH_GENERATOR_H_

#include <cstdint>
#include <string>

#include "asset/include/mesh.h"
#include "asset/include/vertex.h"

namespace ho_renderer {
class MeshGenerator {
 public:
  static Mesh* GenerateSphere(const std::string& name, const int latitude_num,
                              const int longitude_num, const float radius,
                              const LinearRGB& color);
  static Mesh* GenerateSphere(const std::string& name, const int latitude_num,
                              const int longitude_num, const float radius,
                              const std::vector<LinearRGB>& color_buffer);
  static Mesh* GenerateBox(const std::string& name, const float box_width,
                           const float box_depth, const float box_height,
                           const LinearRGB& color);
  static Mesh* GenerateBox(const std::string& name, const float box_width,
                           const float box_depth, const float box_height,
                           const std::vector<LinearRGB>& color_buffer);
  static Mesh* GeneratePlane(const std::string& name, const float plane_width,
                             const float plane_height, const LinearRGB& color);
  static Mesh* GeneratePlane(const std::string& name, const float plane_width,
                             const float plane_height,
                             const std::vector<LinearRGB>& color_buffer);
  static Mesh* GenerateLine(const std::string& name, const float length,
                            const LinearRGB& color);

 private:
};
}  // namespace ho_renderer

#endif