#include "engine/include/mesh_manager.h"

namespace ho_renderer {
MeshManager::MeshManager() = default;
MeshManager::~MeshManager() {
  for (auto itr = meshes_.begin(); itr != meshes_.end(); itr++) {
    delete *itr;
  }
}

void MeshManager::AddMesh(Mesh* mesh) { meshes_.push_back(mesh); }
void MeshManager::DeleteMesh(const std::string& name) {
  for (auto mesh_itr = meshes_.begin(); mesh_itr != meshes_.end(); mesh_itr++) {
    if ((*mesh_itr)->name() == name) {
      meshes_.erase(mesh_itr);
      return;
    }
  }
}
void MeshManager::DeleteMesh(const int index) {
  if (index < 0 || index >= meshes_.size()) {
  }
  meshes_.erase(meshes_.begin() + index);
}
const Mesh* MeshManager::GetMesh(const std::string& name) const {
  for (auto mesh_itr = meshes_.cbegin(); mesh_itr != meshes_.cend();
       mesh_itr++) {
    if ((*mesh_itr)->name() == name) {
      return *mesh_itr;
    }
  }
}
const Mesh* MeshManager::GetMesh(const int index) const {
  if (index < 0 || index >= meshes_.size()) {
  }
  return meshes_[index];
}

}  // namespace ho_renderer