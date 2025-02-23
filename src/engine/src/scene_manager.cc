#include "engine/include/scene_manager.h"

#include <cassert>
#include <string>

#include "app/include/debug.h"

namespace ho_renderer {
SceneManager::SceneManager() = default;
SceneManager::~SceneManager() = default;

const Scene& SceneManager::main_scene() const { return *main_scene_; }

void SceneManager::AddScene(Scene* scene) {
  for (auto scene_itr = scenes_.cbegin(); scene_itr != scenes_.cend();
       scene_itr++) {
    if ((*scene_itr)->name() == scene->name()) {
    }
  }
  scenes_.push_back(std::unique_ptr<Scene>(scene));
}
void SceneManager::DeleteScene(const std::string& name) {
  for (auto scene_itr = scenes_.begin(); scene_itr != scenes_.end();
       scene_itr++) {
    if ((*scene_itr)->name() == name) {
      scenes_.erase(scene_itr);
      return;
    }
  }
}
void SceneManager::DeleteScene(const int index) {
  if (index < 0 || index >= scenes_.size()) {
  }
  scenes_.erase(scenes_.begin() + index);
}
const Scene& SceneManager::GetScene(const std::string& name) const {
  for (auto scene_itr = scenes_.cbegin(); scene_itr != scenes_.cend();
       scene_itr++) {
    if ((*scene_itr)->name() == name) {
      return **scene_itr;
    }
  }
}
const Scene& SceneManager::GetScene(const int index) const {
  if (index < 0 || index >= scenes_.size()) {
  }
  return *(scenes_[index]);
}

void SceneManager::SetMainScene(const std::string& name) {
  for (auto scene_itr = scenes_.cbegin(); scene_itr != scenes_.cend();
       scene_itr++) {
    if ((*scene_itr)->name() == name) {
      main_scene_ = *scene_itr;
      return;
    }
  }
}
}  // namespace ho_renderer