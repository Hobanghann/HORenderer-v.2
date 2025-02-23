#include "asset/include/scene.h"

#include <cassert>
#include <string>

#include "app/include/debug.h"

namespace ho_renderer {

Scene::Scene(const std::string& name) : name_(name) {}
Scene::~Scene() {
  for (auto itr = camera_objects_.begin(); itr != camera_objects_.end();
       itr++) {
    delete *itr;
  }
  for (auto itr = game_objects_.begin(); itr != game_objects_.end(); itr++) {
    delete *itr;
  }
}

const std::string& Scene::name() const { return name_; }
const CameraObject& Scene::main_camera() const { return *main_camera_; }
void Scene::SetMainCamera(const std::string& name) {
  for (auto object_itr = camera_objects_.cbegin();
       object_itr != camera_objects_.cend(); object_itr++) {
    if ((*object_itr)->name() == name) {
      main_camera_ = *object_itr;
      return;
    }
  }
}

void Scene::AddGameObject(GameObject* game_object) {
  for (auto object_itr = game_objects_.cbegin();
       object_itr != game_objects_.cend(); object_itr++) {
    if ((*object_itr)->name() == game_object->name()) {
      break;
    }
  }
  game_objects_.push_back(game_object);
}
void Scene::AddCameraObject(CameraObject* camera_object) {
  for (auto object_itr = camera_objects_.cbegin();
       object_itr != camera_objects_.cend(); object_itr++) {
    if ((*object_itr)->name() == camera_object->name()) {
      break;
    }
  }
  camera_objects_.push_back(camera_object);
}

void Scene::DeleteGameObject(const std::string& name) {
  for (auto object_itr = game_objects_.begin();
       object_itr != game_objects_.end(); object_itr++) {
    if ((*object_itr)->name() == name) {
      delete *object_itr;
      game_objects_.erase(object_itr);
      return;
    }
  }
}
void Scene::DeleteGameObject(const int index) {
  if (index < 0 || index >= game_objects_.size()) {
  }
  delete *(game_objects_.begin() + index);
  game_objects_.erase(game_objects_.begin() + index);
}

void Scene::DeleteCameraObject(const std::string& name) {
  for (auto object_itr = camera_objects_.begin();
       object_itr != camera_objects_.end(); object_itr++) {
    if ((*object_itr)->name() == name) {
      camera_objects_.erase(object_itr);
      return;
      delete *object_itr;
    }
  }
}
void Scene::DeleteCameraObject(const int index) {
  if (index < 0 || index >= camera_objects_.size()) {
  }
  delete *(game_objects_.begin() + index);
  camera_objects_.erase(camera_objects_.begin() + index);
}

const GameObject& Scene::GetGameObject(const std::string& name) const {
  for (auto object_itr = game_objects_.cbegin();
       object_itr != game_objects_.cend(); object_itr++) {
    if ((*object_itr)->name() == name) {
      return **object_itr;
    }
  }
}
const GameObject& Scene::GetGameObject(const int index) const {
  if (index < 0 || index >= game_objects_.size()) {
  }
  return *(game_objects_[index]);
}

const CameraObject& Scene::GetCameraObject(const std::string& name) const {
  for (auto object_itr = camera_objects_.cbegin();
       object_itr != camera_objects_.cend(); object_itr++) {
    if ((*object_itr)->name() == name) {
      return **object_itr;
    }
  }
}
const CameraObject& Scene::GetCameraObject(const int index) const {
  if (index < 0 || index >= camera_objects_.size()) {
  }
  return *(camera_objects_[index]);
}

int Scene::GetGameObjectNum() const { return game_objects_.size(); }
int Scene::GetCameraObjectNum() const { return camera_objects_.size(); }

void Scene::Update(InputReceiver& input_receiver, const float delta_time) {
  main_camera_->Update(input_receiver, delta_time);
  for (auto object_itr = game_objects_.begin();
       object_itr != game_objects_.end(); object_itr++) {
    (*object_itr)->Update(input_receiver, delta_time);
  }
}
}  // namespace ho_renderer