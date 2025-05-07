#ifndef _HORENDERER_MODEL_LOADER_H_
#define _HORENDERER_MODEL_LOADER_H_

#include <string>

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include "graphics/resource/include/model.h"

namespace ho_renderer {
class ModelLoader {
 public:
  ModelLoader();
  ModelLoader(const ModelLoader& loader) = delete;
  ModelLoader& operator=(const ModelLoader& loader) = delete;
  ~ModelLoader();

  std::unique_ptr<Model> Load(const std::string& name, const std::string& path);
  std::unique_ptr<Model> LoadLeftHanded(const std::string& name,
                                        const std::string& path);

 private:
  std::unique_ptr<Mesh> LoadMesh(aiMesh* ai_mesh, Model* owner);
  std::unique_ptr<Material> LoadMaterial(aiMaterial* material, Model* owner);
  std::unique_ptr<ModelNode> LoadTree(aiNode* root, Model* owner);
  std::unique_ptr<Texture> LoadTexture(const std::string& path);

  std::unique_ptr<Model> built_model_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_MODEL_LOADER_H_