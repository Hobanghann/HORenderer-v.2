#ifndef _HORENDERER_SCENE_MANAGER_H_
#define _HORENDERER_SCENE_MANAGER_H_

#include <memory>
#include <string>
#include <vector>

#include "scene/system/include/scene.h"

namespace ho_renderer {
class SceneManager {
 public:
  SceneManager();
  SceneManager(const SceneManager&) = delete;
  SceneManager& operator=(const SceneManager&) = delete;
  ~SceneManager();

  Scene* GetMainScene();

  bool AddScene(std::unique_ptr<Scene> scene);
  bool DeleteScene(const std::string& name);
  bool DeleteScene(int index);
  Scene* GetScene(const std::string& name) const;
  Scene* GetScene(int index) const;

  bool SetMainScene(const std::string& name);

 private:
  std::vector<std::unique_ptr<Scene>> scenes_;
  int main_scene_index_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_SCENE_MANAGER_H_