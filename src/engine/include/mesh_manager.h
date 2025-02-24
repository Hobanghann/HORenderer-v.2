#ifndef _HORENDERER_ENGINE_MESH_MANAGER_H_
#define _HORENDERER_ENGINE_MESH_MANAGER_H_

#include <string>
#include <vector>

#include "asset/include/mesh.h"

namespace ho_renderer {
class MeshManager {
 public:
  MeshManager();
  MeshManager(const MeshManager&) = delete;
  MeshManager& operator=(const MeshManager&) = delete;
  ~MeshManager();

  void AddMesh(Mesh* mesh);
  void DeleteMesh(const std::string& name);
  void DeleteMesh(const int index);
  const Mesh* GetMesh(const std::string& name) const;
  const Mesh* GetMesh(const int index) const;

 private:
  std::vector<Mesh*> meshes_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_ENGINE_MESH_MANAGER_H_