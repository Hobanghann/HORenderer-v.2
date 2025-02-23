#ifndef _HORENDERER_ENGINE_SCENE_MANAGER_H_
#define _HORENDERER_ENGINE_SCENE_MANAGER_H_

#include <memory>
#include <string>
#include <vector>

#include "asset/include/scene.h"

namespace ho_renderer {
class SceneManager {
 public:
  SceneManager();
  SceneManager(const SceneManager&) = delete;
  SceneManager& operator=(const SceneManager&) = delete;
  ~SceneManager();

  const Scene& main_scene() const;

  void AddScene(Scene* scene);
  void DeleteScene(const std::string& name);
  void DeleteScene(const int index);
  const Scene& GetScene(const std::string& name) const;
  const Scene& GetScene(const int index) const;

  void SetMainScene(const std::string& name);

 private:
  std::vector<std::shared_ptr<Scene>> scenes_;
  std::shared_ptr<Scene> main_scene_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_ENGINE_SCENE_MANAGER_H_