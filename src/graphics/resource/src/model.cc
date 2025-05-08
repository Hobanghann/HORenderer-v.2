#include "graphics/resource/include/model.h"

#include "tools/include/debug.h"

namespace ho_renderer {
Model::Model(const std::string& name) : name_(name) {}
Model::Model(const std::string& name, std::vector<std::unique_ptr<Mesh>> meshes,
             std::vector<std::unique_ptr<Material>> materials,
             std::unique_ptr<ModelNode> root)
    : name_(name),
      meshes_(std::move(meshes)),
      materials_(std::move(materials)),
      root_(std::move(root)) {}
Model::~Model() = default;

const std::string& Model::name() const { return name_; }
const Mesh* Model::GetMesh(std::uint32_t index) const {
  ASSERT_MSG(index < meshes_.size(),
             "Model::GetMesh Error: index out of range");
  if (index >= meshes_.size()) {
    return nullptr;
  }
  return meshes_[index].get();
}
const Material* Model::GetMaterial(std::uint32_t index) const {
  ASSERT_MSG(index < materials_.size(),
             "Model::GetMaterial Error: index out of range");
  if (index >= materials_.size()) {
    return nullptr;
  }
  return materials_[index].get();
}
ModelNode* Model::root() const {
  ASSERT_MSG(root_ != nullptr, "Model::root Error: root node is null");
  return root_.get();
}

std::uint32_t Model::GetNumMeshes() const { return meshes_.size(); }
std::uint32_t Model::GetNumMaterials() const { return materials_.size(); }

const std::string& Model::parent_path() const { return parent_path_; }

void Model::set_parent_path(const std::string& path) { parent_path_ = path; }
void Model::set_meshes(std::vector<std::unique_ptr<Mesh>> meshes) {
  meshes_ = std::move(meshes);
}
void Model::set_materials(std::vector<std::unique_ptr<Material>> materials) {
  materials_ = std::move(materials);
}

void Model::set_root(std::unique_ptr<ModelNode> root) {
  root_ = std::move(root);
}
}  // namespace ho_renderer