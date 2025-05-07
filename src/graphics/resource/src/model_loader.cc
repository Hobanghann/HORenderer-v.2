#include "graphics/resource/include/model_loader.h"

#include <cstdlib>
#include <filesystem>
#include <memory>
#include <queue>
#include <string>
#include <vector>

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include "core/math/include/math_utils.h"
#include "graphics/resource/include/material_builder.h"
#include "graphics/resource/include/vertex.h"
#include "lib/include/stb_image_impl.h"
#include "scene/object/include/transform.h"

namespace ho_renderer {
ModelLoader::ModelLoader() = default;
ModelLoader::~ModelLoader() = default;

std::unique_ptr<Model> ModelLoader::Load(const std::string& name,
                                         const std::string& path) {
  Assimp::Importer importer;
  const aiScene* scene = importer.ReadFile(
      path.c_str(), aiProcess_JoinIdenticalVertices | aiProcess_Triangulate |
                        aiProcess_FlipUVs | aiProcess_GenSmoothNormals |
                        aiProcess_GenBoundingBoxes |
                        aiProcess_CalcTangentSpace);
  if (scene == nullptr) {
    printf("Assimp error: %s\n", importer.GetErrorString());
    return nullptr;
  }
  built_model_ = std::make_unique<Model>(name);
  built_model_->set_parent_path(
      std::filesystem::path(path).parent_path().string() + "/");
  std::vector<std::unique_ptr<Mesh>> meshes;
  for (int i = 0; i < scene->mNumMeshes; i++) {
    meshes.push_back(
        std::move(LoadMesh(scene->mMeshes[i], built_model_.get())));
  }
  built_model_->set_meshes(std::move(meshes));
  std::vector<std::unique_ptr<Material>> materials;
  for (int i = 0; i < scene->mNumMaterials; i++) {
    materials.push_back(
        std::move(LoadMaterial(scene->mMaterials[i], built_model_.get())));
  }
  built_model_->set_materials(std::move(materials));
  std::unique_ptr<ModelNode> root =
      std::move(LoadTree(scene->mRootNode, built_model_.get()));
  built_model_->set_root(std::move(root));
  return std::move(built_model_);
}

std::unique_ptr<Model> ModelLoader::LoadLeftHanded(const std::string& name,
                                                   const std::string& path) {
  Assimp::Importer importer;
  const aiScene* scene = importer.ReadFile(
      path.c_str(),
      aiProcess_JoinIdenticalVertices | aiProcess_Triangulate |
          aiProcess_GenSmoothNormals | aiProcess_GenBoundingBoxes |
          aiProcess_CalcTangentSpace | aiProcess_ConvertToLeftHanded);
  if (scene == nullptr) {
    printf("Assimp error: %s\n", importer.GetErrorString());
    return nullptr;
  }
  built_model_ = std::make_unique<Model>(name);
  built_model_->set_parent_path(
      std::filesystem::path(path).parent_path().string() + "/");
  std::vector<std::unique_ptr<Mesh>> meshes;
  for (int i = 0; i < scene->mNumMeshes; i++) {
    meshes.push_back(
        std::move(LoadMesh(scene->mMeshes[i], built_model_.get())));
  }
  built_model_->set_meshes(std::move(meshes));
  std::vector<std::unique_ptr<Material>> materials;
  for (int i = 0; i < scene->mNumMaterials; i++) {
    materials.push_back(
        std::move(LoadMaterial(scene->mMaterials[i], built_model_.get())));
  }
  built_model_->set_materials(std::move(materials));
  std::unique_ptr<ModelNode> root =
      std::move(LoadTree(scene->mRootNode, built_model_.get()));
  built_model_->set_root(std::move(root));
  return std::move(built_model_);
}

std::unique_ptr<Mesh> ModelLoader::LoadMesh(aiMesh* ai_mesh, Model* owner) {
  std::vector<Vertex> vertices;
  std::vector<std::uint32_t> indices;
  std::string mesh_name = ai_mesh->mName.C_Str();
  // load vertices
  for (int i = 0; i < ai_mesh->mNumVertices; i++) {
    Vector4 pos(ai_mesh->mVertices[i].x, ai_mesh->mVertices[i].y,
                ai_mesh->mVertices[i].z, 1.f);
    Vector3 tex_coord = Vector3(MathUtils::kFloatNaN, MathUtils::kFloatNaN,
                                MathUtils::kFloatNaN);
    if (ai_mesh->mTextureCoords[0]) {
      tex_coord = {ai_mesh->mTextureCoords[0][i].x,
                   ai_mesh->mTextureCoords[0][i].y,
                   ai_mesh->mTextureCoords[0][i].z};
    }
    Vector3 normal = Vector3(MathUtils::kFloatNaN, MathUtils::kFloatNaN,
                             MathUtils::kFloatNaN);
    if (ai_mesh->mNormals != nullptr) {
      normal = Vector3(ai_mesh->mNormals[i].x, ai_mesh->mNormals[i].y,
                       ai_mesh->mNormals[i].z)
                   .GetNormalized();
    }
    Vector3 tangent = Vector3(MathUtils::kFloatNaN, MathUtils::kFloatNaN,
                              MathUtils::kFloatNaN);
    if (ai_mesh->mTangents != nullptr) {
      tangent = Vector3(ai_mesh->mTangents[i].x, ai_mesh->mTangents[i].y,
                        ai_mesh->mTangents[i].z)
                    .GetNormalized();
    }
    Vector3 bitangent = Vector3(MathUtils::kFloatNaN, MathUtils::kFloatNaN,
                                MathUtils::kFloatNaN);
    if (ai_mesh->mBitangents != nullptr) {
      bitangent = Vector3(ai_mesh->mBitangents[i].x, ai_mesh->mBitangents[i].y,
                          ai_mesh->mBitangents[i].z)
                      .GetNormalized();
    }
    float handedness = 1.f;
    if (MathUtils::IsFloatNaN(normal.x()) &&
        MathUtils::IsFloatNaN(tangent.x()) &&
        MathUtils::IsFloatNaN(bitangent.x())) {
      handedness = (normal.Cross(tangent).Dot(bitangent) > 0) ? 1.f : -1.f;
    }
    vertices.emplace_back(pos, tex_coord, normal, tangent, handedness);
  }
  // load indices
  for (int i = 0; i < ai_mesh->mNumFaces; i++) {
    const aiFace& face = ai_mesh->mFaces[i];
    for (int j = 0; j < face.mNumIndices; j++) {
      indices.emplace_back(face.mIndices[j]);
    }
  }
  // load bounding volume
  const aiAABB& aabb = ai_mesh->mAABB;
  Vector3 max(aabb.mMax.x, aabb.mMax.y, aabb.mMax.z);
  Vector3 min(aabb.mMin.x, aabb.mMin.y, aabb.mMin.z);
  AABBoundingVolume(max, min);

  return std::make_unique<Mesh>(owner, mesh_name, vertices, indices,
                                ai_mesh->mMaterialIndex);
}

std::unique_ptr<Material> ModelLoader::LoadMaterial(aiMaterial* material,
                                                    Model* owner) {
  MaterialBuilder mat_builder;
  mat_builder.Reset();
  char name_buf[100];
  sprintf(name_buf, "Unnamed Material");
  std::string mat_name = std::string(name_buf);
  aiString ai_name;
  if (AI_SUCCESS == material->Get(AI_MATKEY_NAME, ai_name)) {
    mat_name = ai_name.C_Str();
  }
  mat_builder.set_name(mat_name);
  aiColor3D ambient(0.f, 0.f, 0.f);
  aiColor3D diffuse(0.f, 0.f, 0.f);
  aiColor3D specular(0.f, 0.f, 0.f);
  float specular_exponent = 0.0f;
  float specular_coefficient = 1.0f;
  float opacity = 0.0f;

  material->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
  material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
  material->Get(AI_MATKEY_COLOR_SPECULAR, specular);
  material->Get(AI_MATKEY_SHININESS, specular_exponent);
  material->Get(AI_MATKEY_SHININESS_STRENGTH, specular_coefficient);
  material->Get(AI_MATKEY_OPACITY, opacity);

  LinearRGB ambient_color(ambient.r, ambient.g, ambient.b);
  LinearRGB diffuse_color(diffuse.r, diffuse.g, diffuse.b);
  LinearRGB specular_color(specular.r, specular.g, specular.b);

  mat_builder.set_ambient_color(ambient_color)
      .set_diffuse_color(diffuse_color)
      .set_specular_color(specular_color)
      .set_specular_coefficient(specular_coefficient)
      .set_specular_exponent(specular_exponent);

  std::array<std::unique_ptr<Texture>, TextureType::Last> textures;
  for (int j = 0; j < TextureType::Last; j++) {
    textures[j] = nullptr;

    aiTextureType assimp_texture_type;
    switch (static_cast<TextureType>(j)) {
      case TextureType::Ambient:
        assimp_texture_type = aiTextureType_AMBIENT;
        break;
      case TextureType::Diffuse:
        assimp_texture_type = aiTextureType_DIFFUSE;
        break;
      case TextureType::Specular:
        assimp_texture_type = aiTextureType_SPECULAR;
        break;
      case TextureType::SpecularHighlight:
        assimp_texture_type = aiTextureType_SHININESS;
        break;
      case TextureType::Alpha:
        assimp_texture_type = aiTextureType_OPACITY;
        break;
      case TextureType::Displacement:
        assimp_texture_type = aiTextureType_DISPLACEMENT;
        break;
      case TextureType::Roughness:
        assimp_texture_type = aiTextureType_DIFFUSE_ROUGHNESS;
        break;
      case TextureType::Metallic:
        assimp_texture_type = aiTextureType_METALNESS;
        break;
      case TextureType::Sheen:
        assimp_texture_type = aiTextureType_SHEEN;
        break;
      case TextureType::Emmissive:
        assimp_texture_type = aiTextureType_EMISSIVE;
        break;
      case TextureType::Normal:
        if (material->GetTextureCount(aiTextureType_NORMALS) > 0) {
          assimp_texture_type = aiTextureType_NORMALS;
        } else {
          assimp_texture_type = aiTextureType_HEIGHT;
        }
        break;
      default:
        continue;
    }
    int num_tex = 0;
    if ((num_tex = material->GetTextureCount(assimp_texture_type)) > 0) {
      aiString texture_path;
      if (AI_SUCCESS ==
          material->GetTexture(assimp_texture_type, 0, &texture_path)) {
        std::string path = texture_path.C_Str();
        mat_builder.set_Texture(
            static_cast<TextureType>(j),
            std::move(LoadTexture(owner->parent_path_ + path)));
      }
    }
  }

  return mat_builder.Build(owner);
}
std::unique_ptr<ModelNode> ModelLoader::LoadTree(aiNode* root, Model* owner) {
  if (root == nullptr) {
    return nullptr;
  }
  std::vector<std::uint32_t> mesh_indices;
  for (int i = 0; i < root->mNumMeshes; i++) {
    mesh_indices.push_back(root->mMeshes[i]);
  }
  std::vector<std::unique_ptr<ModelNode>> childs;
  for (int i = 0; i < root->mNumChildren; i++) {
    childs.push_back(std::move(LoadTree(root->mChildren[i], owner)));
  }
  aiMatrix4x4 m_matrix = root->mTransformation;
  Transform transform;
  transform.set_world_coord(Vector3(m_matrix.d1, m_matrix.d2, m_matrix.d3))
      .set_world_right(Vector3(m_matrix.a1, m_matrix.a2, m_matrix.a3))
      .set_world_up(Vector3(m_matrix.b1, m_matrix.b2, m_matrix.b3))
      .set_world_forward(Vector3(m_matrix.c1, m_matrix.c2, m_matrix.c3))
      .set_world_scale(m_matrix.a1);

  std::unique_ptr<ModelNode> node = std::make_unique<ModelNode>(
      owner, root->mName.C_Str(), mesh_indices, std::move(childs), transform);
  for (int i = 0; i < node->NumChilds(); i++) {
    node->GetChild(i)->set_parent(node.get());
  }
  return std::move(node);
}

std::unique_ptr<Texture> ModelLoader::LoadTexture(const std::string& path) {
  int width;
  int height;
  int num_channel;
  std::uint32_t* texels = (std::uint32_t*)(stbi_load(path.c_str(), &width,
                                                     &height, &num_channel, 4));
  if (texels == nullptr) {
    printf("Failed to load image : %s\n", stbi_failure_reason());
  }
  return std::make_unique<Texture>(path, texels, width, height);
}
}  // namespace ho_renderer