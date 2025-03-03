#include "engine/scene/include/scene_manager.h"

#include <cassert>
#include <string>

#include "app/include/debug.h"

namespace ho_renderer {
SceneManager::SceneManager() = default;
SceneManager::~SceneManager() {
  for (auto itr = scenes_.begin(); itr != scenes_.end(); itr++) {
    delete *itr;
  }
}

Scene* SceneManager::GetMainScene() { return scenes_[main_scene_index_]; }

void SceneManager::AddScene(Scene* scene) {
  for (auto scene_itr = scenes_.cbegin(); scene_itr != scenes_.cend();
       scene_itr++) {
    if ((*scene_itr)->name() == scene->name()) {
      return;
    }
  }
  scenes_.push_back(scene);
}
void SceneManager::DeleteScene(const std::string& name) {
  for (auto scene_itr = scenes_.begin(); scene_itr != scenes_.end();
       scene_itr++) {
    if ((*scene_itr)->name() == name) {
      delete *scene_itr;
      scenes_.erase(scene_itr);
      return;
    }
  }
}
void SceneManager::DeleteScene(const int index) {
  if (index < 0 || index >= scenes_.size()) {
    return;
  }
  scenes_.erase(scenes_.begin() + index);
}
Scene* SceneManager::GetScene(const std::string& name) const {
  for (auto scene_itr = scenes_.cbegin(); scene_itr != scenes_.cend();
       scene_itr++) {
    if ((*scene_itr)->name() == name) {
      return *scene_itr;
    }
  }
  // exception handling
  return nullptr;
}
Scene* SceneManager::GetScene(const int index) const {
  if (index < 0 || index >= scenes_.size()) {
    // exception handling
    return nullptr;
  }
  return scenes_[index];
}

void SceneManager::SetMainScene(const std::string& name) {
  std::uint32_t index = 0;
  for (auto scene_itr = scenes_.cbegin(); scene_itr != scenes_.cend();
       scene_itr++) {
    if ((*scene_itr)->name() == name) {
      main_scene_index_ = index;
      return;
    }
    index++;
  }
}
}  // namespace ho_renderer