#ifndef _HORENDERER_ENGINE_SCENE_SCENE_MANAGER_H_
#define _HORENDERER_ENGINE_SCENE_SCENE_MANAGER_H_

#include <cstdint>
#include <string>
#include <vector>

#include "engine/scene/include/scene.h"

namespace ho_renderer {
class SceneManager {
 public:
  SceneManager();
  SceneManager(const SceneManager&) = delete;
  SceneManager& operator=(const SceneManager&) = delete;
  ~SceneManager();

  Scene* GetMainScene();

  void AddScene(Scene* scene);
  void DeleteScene(const std::string& name);
  void DeleteScene(const int index);
  Scene* GetScene(const std::string& name) const;
  Scene* GetScene(const int index) const;

  void SetMainScene(const std::string& name);

 private:
  std::vector<Scene*> scenes_;
  std::uint32_t main_scene_index_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_ENGINE_SCENE_SCENE_MANAGER_H_