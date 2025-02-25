#include "engine/include/mesh_generator.h"

#include <cstdint>

#include "asset/include/vertex.h"
#include "math/include/math_utils.h"
#include "math/include/vector4.h"

namespace ho_renderer {
Mesh* MeshGenerator::GenerateSphere(const std::string& name,
                                    const int latitude_num,
                                    const int longitude_num, const float radius,
                                    const std::uint32_t color_bit) {
  std::vector<Vertex> vertex_buffer;
  std::vector<unsigned int> index_buffer;

  for (int lat = 0; lat <= latitude_num; lat++) {
    float alpha = lat * MathUtils::kPI / latitude_num;
    float sin_alpha = MathUtils::Sinf(alpha);
    float cos_alpha = MathUtils::Cosf(alpha);

    for (int lon = 0; lon <= longitude_num; lon++) {
      float beta = lon * 2.0f * MathUtils::kPI / longitude_num;
      float sin_beta = MathUtils::Sinf(beta);
      float cos_beta = MathUtils::Cosf(beta);

      float x = cos_beta * sin_alpha;
      float y = cos_alpha;
      float z = sin_beta * sin_alpha;

      vertex_buffer.emplace_back(
          Vector4(radius * x, radius * y, radius * z, 1.f));
    }
  }

  for (int lat = 0; lat < latitude_num; lat++) {
    for (int lon = 0; lon < longitude_num; lon++) {
      int first = (lat * (longitude_num + 1)) + lon;
      int second = first + longitude_num + 1;

      index_buffer.push_back(first);
      index_buffer.push_back(second);
      index_buffer.push_back(first + 1);

      index_buffer.push_back(second);
      index_buffer.push_back(second + 1);
      index_buffer.push_back(first + 1);
    }
  }
  std::vector<std::uint32_t> color_buffer(index_buffer.size() / 3.f, color_bit);
  return new Mesh(name, vertex_buffer, index_buffer, color_buffer,
                  PrimitiveType::kTRIANGLE);
}
Mesh* MeshGenerator::GenerateSphere(
    const std::string& name, const int latitude_num, const int longitude_num,
    const float radius, const std::vector<std::uint32_t>& color_buffer) {
  std::vector<Vertex> vertex_buffer;
  std::vector<unsigned int> index_buffer;

  for (int lat = 0; lat <= latitude_num; lat++) {
    float alpha = lat * MathUtils::kPI / latitude_num;
    float sin_alpha = MathUtils::Sinf(alpha);
    float cos_alpha = MathUtils::Cosf(alpha);

    for (int lon = 0; lon <= longitude_num; lon++) {
      float beta = lon * 2.0f * MathUtils::kPI / longitude_num;
      float sin_beta = MathUtils::Sinf(beta);
      float cos_beta = MathUtils::Cosf(beta);

      float x = cos_beta * sin_alpha;
      float y = cos_alpha;
      float z = sin_beta * sin_alpha;

      vertex_buffer.emplace_back(
          Vector4(radius * x, radius * y, radius * z, 1.f));
    }
  }

  for (int lat = 0; lat < latitude_num; lat++) {
    for (int lon = 0; lon < longitude_num; lon++) {
      int first = (lat * (longitude_num + 1)) + lon;
      int second = first + longitude_num + 1;

      index_buffer.push_back(first);
      index_buffer.push_back(second);
      index_buffer.push_back(first + 1);

      index_buffer.push_back(second);
      index_buffer.push_back(second + 1);
      index_buffer.push_back(first + 1);
    }
  }
  return new Mesh(name, vertex_buffer, index_buffer, color_buffer,
                  PrimitiveType::kTRIANGLE);
}
Mesh* MeshGenerator::GenerateBox(const std::string& name, const float box_width,
                                 const float box_depth, const float box_height,
                                 const std::uint32_t color_bit) {
  std::vector<Vertex> vertex_buffer;
  std::vector<unsigned int> index_buffer;

  float half_width = box_width * 0.5f;
  float half_depth = box_depth * 0.5f;
  float half_height = box_height * 0.5f;

  vertex_buffer.emplace_back(Vector4(half_width, half_height, half_depth, 1.f));
  vertex_buffer.emplace_back(
      Vector4(half_width, half_height, -half_depth, 1.f));
  vertex_buffer.emplace_back(
      Vector4(-half_width, half_height, -half_depth, 1.f));
  vertex_buffer.emplace_back(
      Vector4(-half_width, half_height, half_depth, 1.f));
  vertex_buffer.emplace_back(
      Vector4(half_width, -half_height, half_depth, 1.f));
  vertex_buffer.emplace_back(
      Vector4(half_width, -half_height, -half_depth, 1.f));
  vertex_buffer.emplace_back(
      Vector4(-half_width, -half_height, -half_depth, 1.f));
  vertex_buffer.emplace_back(
      Vector4(-half_width, -half_height, half_depth, 1.f));

  index_buffer = {0, 1, 2, 2, 3, 0, 0, 3, 7, 7, 4, 0, 0, 4, 5, 5, 1, 0,
                  1, 5, 6, 6, 2, 1, 2, 6, 7, 7, 3, 2, 4, 7, 6, 6, 5, 4};

  std::vector<std::uint32_t> color_buffer(index_buffer.size() / 3.f, color_bit);

  return new Mesh(name, vertex_buffer, index_buffer, color_buffer,
                  PrimitiveType::kTRIANGLE);
}
Mesh* MeshGenerator::GenerateBox(
    const std::string& name, const float box_width, const float box_depth,
    const float box_height, const std::vector<std::uint32_t>& color_buffer) {
  std::vector<Vertex> vertex_buffer;
  std::vector<unsigned int> index_buffer;

  float half_width = box_width * 0.5f;
  float half_depth = box_depth * 0.5f;
  float half_height = box_height * 0.5f;

  vertex_buffer.emplace_back(Vector4(half_width, half_height, half_depth, 1.f));
  vertex_buffer.emplace_back(
      Vector4(half_width, half_height, -half_depth, 1.f));
  vertex_buffer.emplace_back(
      Vector4(-half_width, half_height, -half_depth, 1.f));
  vertex_buffer.emplace_back(
      Vector4(-half_width, half_height, half_depth, 1.f));
  vertex_buffer.emplace_back(
      Vector4(half_width, -half_height, half_depth, 1.f));
  vertex_buffer.emplace_back(
      Vector4(half_width, -half_height, -half_depth, 1.f));
  vertex_buffer.emplace_back(
      Vector4(-half_width, -half_height, -half_depth, 1.f));
  vertex_buffer.emplace_back(
      Vector4(-half_width, -half_height, half_depth, 1.f));

  index_buffer = {0, 1, 2, 2, 3, 0, 0, 3, 7, 7, 4, 0, 0, 4, 5, 5, 1, 0,
                  1, 5, 6, 6, 2, 1, 2, 6, 7, 7, 3, 2, 4, 7, 6, 6, 5, 4};

  return new Mesh(name, vertex_buffer, index_buffer, color_buffer,
                  PrimitiveType::kTRIANGLE);
}
Mesh* MeshGenerator::GeneratePlane(const std::string& name,
                                   const float plane_width,
                                   const float plane_height,
                                   const std::uint32_t color_bit) {
  std::vector<Vertex> vertex_buffer;
  std::vector<unsigned int> index_buffer;

  float half_width = plane_width * 0.5f;
  float half_height = plane_height * 0.5f;

  vertex_buffer.emplace_back(Vector4(half_width, half_height, 0.f, 1.f));
  vertex_buffer.emplace_back(Vector4(half_width, -half_height, 0.f, 1.f));
  vertex_buffer.emplace_back(Vector4(-half_width, -half_height, 0.f, 1.f));
  vertex_buffer.emplace_back(Vector4(-half_width, half_height, 0.f, 1.f));

  index_buffer = {0, 3, 2, 2, 1, 0};

  std::vector<std::uint32_t> color_buffer(index_buffer.size() / 3.f, color_bit);

  return new Mesh(name, vertex_buffer, index_buffer, color_buffer,
                  PrimitiveType::kTRIANGLE);
}
Mesh* MeshGenerator::GeneratePlane(
    const std::string& name, const float plane_width, const float plane_height,
    const std::vector<std::uint32_t>& color_buffer) {
  std::vector<Vertex> vertex_buffer;
  std::vector<unsigned int> index_buffer;

  float half_width = plane_width * 0.5f;
  float half_height = plane_height * 0.5f;

  vertex_buffer.emplace_back(Vector4(half_width, half_height, 0.f, 1.f));
  vertex_buffer.emplace_back(Vector4(half_width, -half_height, 0.f, 1.f));
  vertex_buffer.emplace_back(Vector4(-half_width, -half_height, 0.f, 1.f));
  vertex_buffer.emplace_back(Vector4(-half_width, half_height, 0.f, 1.f));

  index_buffer = {0, 3, 2, 2, 1, 0};

  return new Mesh(name, vertex_buffer, index_buffer, color_buffer,
                  PrimitiveType::kTRIANGLE);
}

Mesh* MeshGenerator::GenerateLine(const std::string& name, const float length,
                                  const std::uint32_t color_bit) {
  std::vector<Vertex> vertex_buffer;
  std::vector<unsigned int> index_buffer;

  vertex_buffer.emplace_back(Vector4(length * 0.5f, 0.f, 0.f, 1.f));
  vertex_buffer.emplace_back(Vector4(-length * 0.5f, 0.f, 0.f, 1.f));

  index_buffer = {0, 1};

  std::vector<std::uint32_t> color_buffer(index_buffer.size() / 2.f, color_bit);

  return new Mesh(name, vertex_buffer, index_buffer, color_buffer,
                  PrimitiveType::kLINE);
}
}  // namespace ho_renderer