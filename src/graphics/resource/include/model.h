#ifndef _HORENDERER_MODEL_H_
#define _HORENDERER_MODEL_H_

#include <memory>
#include <string>
#include <vector>

#include "graphics/resource/include/material.h"
#include "graphics/resource/include/mesh.h"
#include "graphics/resource/include/model_node.h"

namespace ho_renderer {
class ModelLoader;
class Model {
  friend ModelLoader;

 public:
  Model() = delete;
  Model(const Model&) = delete;
  Model(const std::string& name);
  Model(const std::string& name, std::vector<std::unique_ptr<Mesh>> meshes,
        std::vector<std::unique_ptr<Material>> materials,
        std::unique_ptr<ModelNode> root);
  Model& operator=(const Model& mesh) = delete;
  ~Model();

  const std::string& name() const;
  const Mesh* GetMesh(std::uint32_t index) const;
  const Material* GetMaterial(std::uint32_t index) const;
  ModelNode* root() const;

  std::uint32_t GetNumMeshes() const;
  std::uint32_t GetNumMaterials() const;

 private:
  const std::string& parent_path() const;

  void set_parent_path(const std::string& path);
  void set_meshes(std::vector<std::unique_ptr<Mesh>> meshes);
  void set_materials(std::vector<std::unique_ptr<Material>> materials);
  void set_root(std::unique_ptr<ModelNode> root);

  std::string parent_path_;
  std::string name_;
  std::vector<std::unique_ptr<Mesh>> meshes_;
  std::vector<std::unique_ptr<Material>> materials_;
  std::unique_ptr<ModelNode> root_;
};
}  // namespace ho_renderer

#endif  //  _HORENDERER_MODEL_H_