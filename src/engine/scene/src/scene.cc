#include "engine/scene/include/scene.h"

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
  for (auto itr = ambient_lights_.begin(); itr != ambient_lights_.end();
       itr++) {
    delete *itr;
  }
  for (auto itr = directional_lights_.begin(); itr != directional_lights_.end();
       itr++) {
    delete *itr;
  }
  for (auto itr = point_lights_.begin(); itr != point_lights_.end(); itr++) {
    delete *itr;
  }
}

const std::string& Scene::name() const { return name_; }

CameraObject* Scene::GetMainCamera() const {
  return camera_objects_[main_camera_index_];
}
AmbientLight* Scene::GetMainAmbientLight() const {
  return ambient_lights_[main_ambient_light_index_];
}
DirectionalLight* Scene::GetMainDirectionalLight() const {
  return directional_lights_[main_directional_light_index_];
}

void Scene::SetMainCamera(const std::string& name) {
  int index = 0;
  for (auto object_itr = camera_objects_.cbegin();
       object_itr != camera_objects_.cend(); object_itr++) {
    if ((*object_itr)->name() == name) {
      main_camera_index_ = index;
      return;
    }
    index++;
  }
}
void Scene::SetMainAmbientLight(const std::string& name) {
  int index = 0;
  for (auto light_itr = ambient_lights_.cbegin();
       light_itr != ambient_lights_.cend(); light_itr++) {
    if ((*light_itr)->name() == name) {
      main_ambient_light_index_ = index;
      return;
    }
    index++;
  }
}
void Scene::SetMainDirectionalLight(const std::string& name) {
  int index = 0;
  for (auto light_itr = directional_lights_.cbegin();
       light_itr != directional_lights_.cend(); light_itr++) {
    if ((*light_itr)->name() == name) {
      main_directional_light_index_ = index;
      return;
    }
    index++;
  }
}

void Scene::AddGameObject(GameObject* game_object) {
  for (auto object_itr = game_objects_.cbegin();
       object_itr != game_objects_.cend(); object_itr++) {
    if ((*object_itr)->name() == game_object->name()) {
      return;
    }
  }
  game_objects_.push_back(game_object);
}
void Scene::AddCameraObject(CameraObject* camera_object) {
  for (auto object_itr = camera_objects_.cbegin();
       object_itr != camera_objects_.cend(); object_itr++) {
    if ((*object_itr)->name() == camera_object->name()) {
      return;
    }
  }
  camera_objects_.push_back(camera_object);
}
void Scene::AddAmbientLight(AmbientLight* light) {
  for (auto light_itr = ambient_lights_.cbegin();
       light_itr != ambient_lights_.cend(); light_itr++) {
    if ((*light_itr)->name() == light->name()) {
      return;
    }
  }
  ambient_lights_.push_back(light);
}
void Scene::AddDirectionalLight(DirectionalLight* light) {
  for (auto light_itr = directional_lights_.cbegin();
       light_itr != directional_lights_.cend(); light_itr++) {
    if ((*light_itr)->name() == light->name()) {
      return;
    }
  }
  directional_lights_.push_back(light);
}
void Scene::AddPointLight(PointLight* light) {
  for (auto light_itr = point_lights_.cbegin();
       light_itr != point_lights_.cend(); light_itr++) {
    if ((*light_itr)->name() == light->name()) {
      return;
    }
  }
  point_lights_.push_back(light);
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
    return;
  }
  delete *(game_objects_.begin() + index);
  game_objects_.erase(game_objects_.begin() + index);
}

void Scene::DeleteCameraObject(const std::string& name) {
  for (auto object_itr = camera_objects_.begin();
       object_itr != camera_objects_.end(); object_itr++) {
    if ((*object_itr)->name() == name) {
      delete *object_itr;
      camera_objects_.erase(object_itr);
      return;
    }
  }
}
void Scene::DeleteCameraObject(const int index) {
  if (index < 0 || index >= camera_objects_.size()) {
    return;
  }
  delete *(game_objects_.begin() + index);
  camera_objects_.erase(camera_objects_.begin() + index);
}
void Scene::DeleteAmbientLight(const std::string& name) {
  for (auto light_itr = ambient_lights_.begin();
       light_itr != ambient_lights_.end(); light_itr++) {
    if ((*light_itr)->name() == name) {
      delete *light_itr;
      ambient_lights_.erase(light_itr);
      return;
    }
  }
}
void Scene::DeleteAmbientLight(const int index) {
  if (index < 0 || index >= ambient_lights_.size()) {
    return;
  }
  delete *(ambient_lights_.begin() + index);
  ambient_lights_.erase(ambient_lights_.begin() + index);
}
void Scene::DeleteDirectionalLight(const std::string& name) {
  for (auto light_itr = directional_lights_.begin();
       light_itr != directional_lights_.end(); light_itr++) {
    if ((*light_itr)->name() == name) {
      delete *light_itr;
      directional_lights_.erase(light_itr);
      return;
    }
  }
}
void Scene::DeleteDirectionalLight(const int index) {
  if (index < 0 || index >= directional_lights_.size()) {
    return;
  }
  delete *(directional_lights_.begin() + index);
  directional_lights_.erase(directional_lights_.begin() + index);
}
void Scene::DeletePointLight(const std::string& name) {
  for (auto light_itr = point_lights_.begin(); light_itr != point_lights_.end();
       light_itr++) {
    if ((*light_itr)->name() == name) {
      delete *light_itr;
      point_lights_.erase(light_itr);
      return;
    }
  }
}
void Scene::DeletePointLight(const int index) {
  if (index < 0 || index >= point_lights_.size()) {
    return;
  }
  delete *(point_lights_.begin() + index);
  point_lights_.erase(point_lights_.begin() + index);
}

GameObject* Scene::GetGameObject(const std::string& name) const {
  for (auto object_itr = game_objects_.begin();
       object_itr != game_objects_.end(); object_itr++) {
    if ((*object_itr)->name() == name) {
      return *object_itr;
    }
  }
  // exception handling
  return nullptr;
}
GameObject* Scene::GetGameObject(const int index) const {
  if (index < 0 || index >= game_objects_.size()) {
    // exception handling
    return nullptr;
  }
  return game_objects_[index];
}

CameraObject* Scene::GetCameraObject(const std::string& name) const {
  for (auto object_itr = camera_objects_.begin();
       object_itr != camera_objects_.end(); object_itr++) {
    if ((*object_itr)->name() == name) {
      return *object_itr;
    }
  }
  // exception handling
  return nullptr;
}
CameraObject* Scene::GetCameraObject(const int index) const {
  if (index < 0 || index >= camera_objects_.size()) {
    // exception handling
    return nullptr;
  }
  return camera_objects_[index];
}
AmbientLight* Scene::GetAmbientLight(const std::string& name) const {
  for (auto light_itr = ambient_lights_.cbegin();
       light_itr != ambient_lights_.cend(); light_itr++) {
    if ((*light_itr)->name() == name) {
      return *light_itr;
    }
  }
  // exception handling
  return nullptr;
}
AmbientLight* Scene::GetAmbientLight(const int index) const {
  if (index < 0 || index >= ambient_lights_.size()) {
    // exception handling
    return nullptr;
  }
  return ambient_lights_[index];
}
DirectionalLight* Scene::GetDirectionalLight(const std::string& name) const {
  for (auto light_itr = directional_lights_.begin();
       light_itr != directional_lights_.end(); light_itr++) {
    if ((*light_itr)->name() == name) {
      return *light_itr;
    }
  }
  // exception handling
  return nullptr;
}
DirectionalLight* Scene::GetDirectionalLight(const int index) const {
  if (index < 0 || index >= directional_lights_.size()) {
    // exception handling
    return nullptr;
  }
  return directional_lights_[index];
}
PointLight* Scene::GetPointLight(const std::string& name) const {
  for (auto light_itr = point_lights_.begin(); light_itr != point_lights_.end();
       light_itr++) {
    if ((*light_itr)->name() == name) {
      return *light_itr;
    }
  }
  // exception handling
  return nullptr;
}
PointLight* Scene::GetPointLight(const int index) const {
  if (index < 0 || index >= point_lights_.size()) {
    // exception handling
    return nullptr;
  }
  return point_lights_[index];
}

int Scene::GetGameObjectNum() const { return game_objects_.size(); }
int Scene::GetCameraObjectNum() const { return camera_objects_.size(); }
int Scene::GetAmbientLightNum() const { return ambient_lights_.size(); }
int Scene::GetDirectionalLightNum() const { return directional_lights_.size(); }
int Scene::GetPointLightNum() const { return point_lights_.size(); }

void Scene::Update(InputReceiver& input_receiver, const float delta_time) {
  GetMainCamera()->Update(input_receiver, delta_time);
  for (auto object_itr = game_objects_.begin();
       object_itr != game_objects_.end(); object_itr++) {
    (*object_itr)->Update(input_receiver, delta_time);
  }
  for (auto light_itr = ambient_lights_.begin();
       light_itr != ambient_lights_.end(); light_itr++) {
    (*light_itr)->Update(input_receiver, delta_time);
  }
  for (auto light_itr = directional_lights_.begin();
       light_itr != directional_lights_.end(); light_itr++) {
    (*light_itr)->Update(input_receiver, delta_time);
  }
  for (auto light_itr = point_lights_.begin(); light_itr != point_lights_.end();
       light_itr++) {
    (*light_itr)->Update(input_receiver, delta_time);
  }
}
}  // namespace ho_renderer