#include "asset/include/mesh.h"

#include <vector>

#include "app/include/debug.h"
#include "asset/include/vertex.h"
#include "engine/include/srgb.h"
#include "math/include/vector3.h"
#include "rendering_pipeline/pipeline/include/pipeline_settings.h"

namespace ho_renderer {

const Mesh Mesh::kBOX = Mesh(
    std::vector<Vertex>{Vector3(1.f, 1.f, 1.f).ToHomogeneousCoordinate(),
                        Vector3(1.f, 1.f, -1.f).ToHomogeneousCoordinate(),
                        Vector3(-1.f, 1.f, -1.f).ToHomogeneousCoordinate(),
                        Vector3(-1.f, 1.f, 1.f).ToHomogeneousCoordinate(),
                        Vector3(1.f, -1.f, 1.f).ToHomogeneousCoordinate(),
                        Vector3(1.f, -1.f, -1.f).ToHomogeneousCoordinate(),
                        Vector3(-1.f, -1.f, -1.f).ToHomogeneousCoordinate(),
                        Vector3(-1.f, -1.f, 1.f).ToHomogeneousCoordinate()},
    std::vector<std::uint32_t>{0, 1, 2, 2, 3, 0, 0, 3, 7, 7, 4, 0,
                               0, 4, 5, 5, 1, 0, 1, 5, 6, 6, 2, 1,
                               2, 6, 7, 7, 3, 2, 4, 7, 6, 6, 5, 4},
    std::vector<std::uint32_t>{
        SRGB::GetLinearBlue(), SRGB::GetLinearBlue(), SRGB::GetLinearGreen(),
        SRGB::GetLinearGreen(), SRGB::GetLinearYellow(),
        SRGB::GetLinearYellow(), SRGB::GetLinearRed(), SRGB::GetLinearRed(),
        SRGB::GetLinearPurple(), SRGB::GetLinearPurple(),
        SRGB::GetLinearOrange(), SRGB::GetLinearOrange()},
    PrimitiveType::kTRIANGLE);

const Mesh Mesh::kBLACK_BOX = Mesh(
    std::vector<Vertex>{Vector3(1.f, 1.f, 1.f).ToHomogeneousCoordinate(),
                        Vector3(1.f, 1.f, -1.f).ToHomogeneousCoordinate(),
                        Vector3(-1.f, 1.f, -1.f).ToHomogeneousCoordinate(),
                        Vector3(-1.f, 1.f, 1.f).ToHomogeneousCoordinate(),
                        Vector3(1.f, -1.f, 1.f).ToHomogeneousCoordinate(),
                        Vector3(1.f, -1.f, -1.f).ToHomogeneousCoordinate(),
                        Vector3(-1.f, -1.f, -1.f).ToHomogeneousCoordinate(),
                        Vector3(-1.f, -1.f, 1.f).ToHomogeneousCoordinate()},
    std::vector<std::uint32_t>{0, 1, 2, 2, 3, 0, 0, 3, 7, 7, 4, 0,
                               0, 4, 5, 5, 1, 0, 1, 5, 6, 6, 2, 1,
                               2, 6, 7, 7, 3, 2, 4, 7, 6, 6, 5, 4},
    std::vector<std::uint32_t>{
        SRGB::GetLinearBlack(), SRGB::GetLinearBlack(), SRGB::GetLinearBlack(),
        SRGB::GetLinearBlack(), SRGB::GetLinearBlack(), SRGB::GetLinearBlack(),
        SRGB::GetLinearBlack(), SRGB::GetLinearBlack(), SRGB::GetLinearBlack(),
        SRGB::GetLinearBlack(), SRGB::GetLinearBlack(), SRGB::GetLinearBlack()},
    PrimitiveType::kTRIANGLE);

const Mesh Mesh::kLINE = Mesh(
    std::vector<Vertex>{
        Vector3(1.f, 1.f, 0.f).ToHomogeneousCoordinate(),
        Vector3(-1.f, -1.f, 0.f).ToHomogeneousCoordinate(),
    },
    std::vector<std::uint32_t>{0, 1},
    std::vector<std::uint32_t>{SRGB::GetLinearBlue()}, PrimitiveType::kLINE);

const Mesh Mesh::kTRIANGLE =
    Mesh(std::vector<Vertex>{Vector3(1.f, 1.f, 1.f).ToHomogeneousCoordinate(),
                             Vector3(-1.f, -1.f, 1.f).ToHomogeneousCoordinate(),
                             Vector3(1.f, -1.f, 1.f).ToHomogeneousCoordinate()},
         std::vector<std::uint32_t>{0, 1, 2},
         std::vector<std::uint32_t>{SRGB::GetLinearBlue()},
         PrimitiveType::kTRIANGLE);

const Mesh Mesh::kPLANE = Mesh(
    std::vector<Vertex>{Vector3(1.f, 1.f, 0.f).ToHomogeneousCoordinate(),
                        Vector3(1.f, -1.f, 0.f).ToHomogeneousCoordinate(),
                        Vector3(-1.f, -1.f, 0.f).ToHomogeneousCoordinate(),
                        Vector3(-1.f, 1.f, 0.f).ToHomogeneousCoordinate()},
    std::vector<std::uint32_t>{0, 3, 2, 2, 1, 0},
    std::vector<std::uint32_t>{SRGB::GetLinearBlack(), SRGB::GetLinearBlack()},
    PrimitiveType::kTRIANGLE);

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