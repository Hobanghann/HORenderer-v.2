#include "scene/system/include/scene_manager.h"

#include <algorithm>
#include <stdexcept>

#include "tools/include/debug.h"

namespace ho_renderer {

SceneManager::SceneManager() : main_scene_index_(-1) {}

SceneManager::~SceneManager() = default;

Scene* SceneManager::GetMainScene() {
  ASSERT_MSG(main_scene_index_ >= 0 &&
                 main_scene_index_ < static_cast<int>(scenes_.size()),
             "SceneManager::GetMainScene Error: main scene index is invalid");
  if (main_scene_index_ < 0 || main_scene_index_ >= scenes_.size()) {
    return nullptr;
  }
  return scenes_[main_scene_index_].get();
}

bool SceneManager::AddScene(std::unique_ptr<Scene> scene) {
  ASSERT_MSG(scene != nullptr,
             "SceneManager::AddScene Error: scene must not be null");
  if (!scene) {
    return false;
  }
  auto it = std::find_if(scenes_.begin(), scenes_.end(),
                         [&](const std::unique_ptr<Scene>& s) {
                           return s->name() == scene->name();
                         });
  ASSERT_MSG(
      it == scenes_.end(),
      "SceneManager::AddScene Error: scene with same name already exists");
  if (it != scenes_.end()) {
    return false;
  }
  scenes_.push_back(std::move(scene));
  return true;
}

bool SceneManager::DeleteScene(const std::string& name) {
  ASSERT_MSG(GetMainScene() == nullptr && GetMainScene()->name() != name,
             "SceneManager::DeleteScene Error: cannot delete the main scene");
  if (GetMainScene() != nullptr || GetMainScene()->name() == name) {
    return false;
  }
  auto it = std::remove_if(scenes_.begin(), scenes_.end(),
                           [&](const std::unique_ptr<Scene>& scene) {
                             return scene->name() == name;
                           });
  ASSERT_MSG(
      it != scenes_.end(),
      "SceneManager::DeleteScene Error: no scene with given name exists");

  if (it == scenes_.end()) {
    return false;
  }
  scenes_.erase(it, scenes_.end());
  return true;
}

bool SceneManager::DeleteScene(int index) {
  ASSERT_MSG(index >= 0 && index < static_cast<int>(scenes_.size()),
             "SceneManager::DeleteScene Error: index out of range");
  ASSERT_MSG(index != main_scene_index_,
             "SceneManager::DeleteScene Error: cannot delete main scene");
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
  ASSERT_MSG(
      it != scenes_.end(),
      "SceneManager::GetScene Error: scene with given name does not exist");
  return (it != scenes_.end()) ? it->get() : nullptr;
}

Scene* SceneManager::GetScene(int index) const {
  ASSERT_MSG(index >= 0 && index < static_cast<int>(scenes_.size()),
             "SceneManager::GetScene Error: index out of range");
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
  ASSERT_MSG(
      it != scenes_.end(),
      "SceneManager::SetMainScene Error: scene with given name not found");

  if (it == scenes_.end()) {
    return false;
  }
  main_scene_index_ = static_cast<int>(std::distance(scenes_.begin(), it));
  return true;
}

}  // namespace ho_renderer
