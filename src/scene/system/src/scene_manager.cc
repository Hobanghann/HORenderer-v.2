#include "scene/system/include/scene_manager.h"

#include <algorithm>  // std::find_if
#include <stdexcept>  // std::out_of_range

namespace ho_renderer {

SceneManager::SceneManager() : main_scene_index_(-1) {}

SceneManager::~SceneManager() = default;

Scene* SceneManager::GetMainScene() {
  if (main_scene_index_ >= scenes_.size()) {
    return nullptr;
  }
  return scenes_[main_scene_index_].get();
}

bool SceneManager::AddScene(std::unique_ptr<Scene> scene) {
  if (!scene) {
    return false;
  }
  auto it = std::find_if(scenes_.begin(), scenes_.end(),
                         [&](const std::unique_ptr<Scene>& s) {
                           return s->name() == scene->name();
                         });
  if (it != scenes_.end()) {
    return false;
  }
  scenes_.push_back(std::move(scene));
  return true;
}

bool SceneManager::DeleteScene(const std::string& name) {
  if (GetMainScene() != nullptr || GetMainScene()->name() == name) {
    return false;
  }
  auto it = std::remove_if(scenes_.begin(), scenes_.end(),
                           [&](const std::unique_ptr<Scene>& scene) {
                             return scene->name() == name;
                           });

  if (it == scenes_.end()) {
    return false;
  }
  scenes_.erase(it, scenes_.end());
  return true;
}

bool SceneManager::DeleteScene(int index) {
  if (index < 0 || index >= scenes_.size() || main_scene_index_ == index) {
    return false;
  }
  scenes_.erase(scenes_.begin() + index);
  return true;
}

Scene* SceneManager::GetScene(const std::string& name) const {
  auto it = std::find_if(scenes_.begin(), scenes_.end(),
                         [&](const std::unique_ptr<Scene>& scene) {
                           return scene->name() == name;
                         });
  return (it != scenes_.end()) ? it->get() : nullptr;
}

Scene* SceneManager::GetScene(int index) const {
  if (index < 0 || index >= scenes_.size()) {
    return nullptr;
  }
  return scenes_[index].get();
}

bool SceneManager::SetMainScene(const std::string& name) {
  auto it = std::find_if(scenes_.begin(), scenes_.end(),
                         [&](const std::unique_ptr<Scene>& scene) {
                           return scene->name() == name;
                         });
  if (it == scenes_.end()) {
    return false;
  }
  main_scene_index_ = static_cast<int>(std::distance(scenes_.begin(), it));
  return true;
}

}  // namespace ho_renderer
