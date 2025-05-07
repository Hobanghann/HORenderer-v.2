#include "scene/system/include/scene.h"

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include "core/input/include/input_listener.h"
#include "scene/camera/include/camera.h"
#include "scene/light/include/ambient_light.h"
#include "scene/light/include/directional_light.h"
#include "scene/light/include/point_light.h"
#include "scene/object/include/game_object.h"

namespace ho_renderer {

Scene::Scene(const std::string& name)
    : name_(name),
      main_camera_index_(-1),
      main_ambient_light_index_(-1),
      main_directional_light_index_(-1) {}

Scene::~Scene() = default;

const std::string& Scene::name() const { return name_; }

Camera* Scene::GetMainCamera() const {
  if (main_camera_index_ < 0 ||
      main_camera_index_ >= static_cast<int>(cameras_.size())) {
    return nullptr;
  }
  return cameras_[main_camera_index_].get();
}

AmbientLight* Scene::GetMainAmbientLight() const {
  if (main_ambient_light_index_ < 0 ||
      main_ambient_light_index_ >= static_cast<int>(ambient_lights_.size())) {
    return nullptr;
  }
  return ambient_lights_[main_ambient_light_index_].get();
}

DirectionalLight* Scene::GetMainDirectionalLight() const {
  if (main_directional_light_index_ < 0 ||
      main_directional_light_index_ >=
          static_cast<int>(directional_lights_.size())) {
    return nullptr;
  }
  return directional_lights_[main_directional_light_index_].get();
}

bool Scene::SetMainCamera(const std::string& name) {
  auto it = std::find_if(cameras_.begin(), cameras_.end(),
                         [&](const std::unique_ptr<Camera>& camera) {
                           return camera->name() == name;
                         });
  if (it == cameras_.end()) {
    return false;
  }
  main_camera_index_ = static_cast<int>(std::distance(cameras_.begin(), it));
  return true;
}

bool Scene::SetMainAmbientLight(const std::string& name) {
  auto it = std::find_if(ambient_lights_.begin(), ambient_lights_.end(),
                         [&](const std::unique_ptr<AmbientLight>& light) {
                           return light->name() == name;
                         });
  if (it == ambient_lights_.end()) {
    return false;
  }
  main_ambient_light_index_ =
      static_cast<int>(std::distance(ambient_lights_.begin(), it));
  return true;
}

bool Scene::SetMainDirectionalLight(const std::string& name) {
  auto it = std::find_if(directional_lights_.begin(), directional_lights_.end(),
                         [&](const std::unique_ptr<DirectionalLight>& light) {
                           return light->name() == name;
                         });
  if (it == directional_lights_.end()) {
    return false;
  }
  main_directional_light_index_ =
      static_cast<int>(std::distance(directional_lights_.begin(), it));
  return true;
}

bool Scene::AddGameObject(std::unique_ptr<GameObject> game_object) {
  if (!game_object) return false;
  auto it = std::find_if(game_objects_.begin(), game_objects_.end(),
                         [&](const std::unique_ptr<GameObject>& obj) {
                           return obj->name() == game_object->name();
                         });
  if (it != game_objects_.end()) {
    return false;
  }
  game_objects_.emplace_back(std::move(game_object));
  return true;
}

bool Scene::AddCamera(std::unique_ptr<Camera> camera) {
  if (!camera) return false;
  auto it = std::find_if(cameras_.begin(), cameras_.end(),
                         [&](const std::unique_ptr<Camera>& cam) {
                           return cam->name() == camera->name();
                         });
  if (it != cameras_.end()) {
    return false;
  }
  cameras_.emplace_back(std::move(camera));
  return true;
}

bool Scene::AddAmbientLight(std::unique_ptr<AmbientLight> light) {
  if (!light) return false;
  auto it = std::find_if(ambient_lights_.begin(), ambient_lights_.end(),
                         [&](const std::unique_ptr<AmbientLight>& l) {
                           return l->name() == light->name();
                         });
  if (it != ambient_lights_.end()) {
    return false;
  }
  ambient_lights_.emplace_back(std::move(light));
  return true;
}

bool Scene::AddDirectionalLight(std::unique_ptr<DirectionalLight> light) {
  if (!light) return false;
  auto it = std::find_if(directional_lights_.begin(), directional_lights_.end(),
                         [&](const std::unique_ptr<DirectionalLight>& l) {
                           return l->name() == light->name();
                         });
  if (it != directional_lights_.end()) {
    return false;
  }
  directional_lights_.emplace_back(std::move(light));
  return true;
}

bool Scene::AddPointLight(std::unique_ptr<PointLight> light) {
  if (!light) return false;
  auto it = std::find_if(point_lights_.begin(), point_lights_.end(),
                         [&](const std::unique_ptr<PointLight>& p) {
                           return p->name() == light->name();
                         });
  if (it != point_lights_.end()) {
    return false;
  }
  point_lights_.emplace_back(std::move(light));
  return true;
}

bool Scene::DeleteGameObject(const std::string& name) {
  auto it = std::find_if(game_objects_.begin(), game_objects_.end(),
                         [&](const std::unique_ptr<GameObject>& obj) {
                           return obj->name() == name;
                         });
  if (it == game_objects_.end()) return false;
  game_objects_.erase(it);
  return true;
}
bool Scene::DeleteGameObject(int index) {
  if (index < 0 || index >= static_cast<int>(game_objects_.size()))
    return false;
  game_objects_.erase(game_objects_.begin() + index);
  return true;
}

bool Scene::DeleteCamera(const std::string& name) {
  auto it = std::find_if(
      cameras_.begin(), cameras_.end(),
      [&](const std::unique_ptr<Camera>& cam) { return cam->name() == name; });

  if (it == cameras_.end()) return false;

  int index = static_cast<int>(std::distance(cameras_.begin(), it));
  if (index == main_camera_index_) {
    return false;
  }
  cameras_.erase(it);
  return true;
}
bool Scene::DeleteCamera(int index) {
  if (index < 0 || index >= static_cast<int>(cameras_.size()) ||
      index == main_camera_index_)
    return false;
  cameras_.erase(cameras_.begin() + index);
  return true;
}

bool Scene::DeleteAmbientLight(const std::string& name) {
  auto it = std::find_if(ambient_lights_.begin(), ambient_lights_.end(),
                         [&](const std::unique_ptr<AmbientLight>& light) {
                           return light->name() == name;
                         });
  if (it == ambient_lights_.end()) return false;
  int index = static_cast<int>(std::distance(ambient_lights_.begin(), it));
  if (index == main_ambient_light_index_) {
    return false;
  }
  ambient_lights_.erase(it);
  return true;
}
bool Scene::DeleteAmbientLight(int index) {
  if (index < 0 || index >= static_cast<int>(ambient_lights_.size()) ||
      index == main_ambient_light_index_)
    return false;
  ambient_lights_.erase(ambient_lights_.begin() + index);
  return true;
}
bool Scene::DeleteDirectionalLight(const std::string& name) {
  auto it = std::find_if(directional_lights_.begin(), directional_lights_.end(),
                         [&](const std::unique_ptr<DirectionalLight>& light) {
                           return light->name() == name;
                         });
  if (it == directional_lights_.end()) return false;
  int index = static_cast<int>(std::distance(directional_lights_.begin(), it));
  if (index == main_directional_light_index_) {
    return false;
  }
  directional_lights_.erase(it);
  return true;
}
bool Scene::DeleteDirectionalLight(int index) {
  if (index < 0 || index >= static_cast<int>(directional_lights_.size()) ||
      index == main_directional_light_index_)
    return false;
  directional_lights_.erase(directional_lights_.begin() + index);
  return true;
}
bool Scene::DeletePointLight(const std::string& name) {
  auto it = std::find_if(point_lights_.begin(), point_lights_.end(),
                         [&](const std::unique_ptr<PointLight>& light) {
                           return light->name() == name;
                         });
  if (it == point_lights_.end()) return false;
  point_lights_.erase(it);
  return true;
}
bool Scene::DeletePointLight(int index) {
  if (index < 0 || index >= static_cast<int>(point_lights_.size()))
    return false;
  point_lights_.erase(point_lights_.begin() + index);
  return true;
}

GameObject* Scene::GetGameObject(const std::string& name) const {
  auto it = std::find_if(game_objects_.begin(), game_objects_.end(),
                         [&](const std::unique_ptr<GameObject>& obj) {
                           return obj->name() == name;
                         });
  return (it != game_objects_.end()) ? it->get() : nullptr;
}
GameObject* Scene::GetGameObject(const int index) const {
  if (index < 0 || index >= static_cast<int>(game_objects_.size()))
    return nullptr;
  return game_objects_[index].get();
}

Camera* Scene::GetCamera(const std::string& name) const {
  auto it = std::find_if(
      cameras_.begin(), cameras_.end(),
      [&](const std::unique_ptr<Camera>& cam) { return cam->name() == name; });
  return (it != cameras_.end()) ? it->get() : nullptr;
}
Camera* Scene::GetCamera(const int index) const {
  if (index < 0 || index >= static_cast<int>(cameras_.size())) return nullptr;
  return cameras_[index].get();
}
AmbientLight* Scene::GetAmbientLight(const std::string& name) const {
  auto it = std::find_if(ambient_lights_.begin(), ambient_lights_.end(),
                         [&](const std::unique_ptr<AmbientLight>& l) {
                           return l->name() == name;
                         });
  return (it != ambient_lights_.end()) ? it->get() : nullptr;
}
AmbientLight* Scene::GetAmbientLight(const int index) const {
  if (index < 0 || index >= static_cast<int>(ambient_lights_.size()))
    return nullptr;
  return ambient_lights_[index].get();
}
DirectionalLight* Scene::GetDirectionalLight(const std::string& name) const {
  auto it = std::find_if(directional_lights_.begin(), directional_lights_.end(),
                         [&](const std::unique_ptr<DirectionalLight>& l) {
                           return l->name() == name;
                         });
  return (it != directional_lights_.end()) ? it->get() : nullptr;
}
DirectionalLight* Scene::GetDirectionalLight(const int index) const {
  if (index < 0 || index >= static_cast<int>(directional_lights_.size()))
    return nullptr;
  return directional_lights_[index].get();
}
PointLight* Scene::GetPointLight(const std::string& name) const {
  auto it = std::find_if(
      point_lights_.begin(), point_lights_.end(),
      [&](const std::unique_ptr<PointLight>& l) { return l->name() == name; });
  return (it != point_lights_.end()) ? it->get() : nullptr;
}
PointLight* Scene::GetPointLight(const int index) const {
  if (index < 0 || index >= static_cast<int>(point_lights_.size()))
    return nullptr;
  return point_lights_[index].get();
}

int Scene::GetGameObjectsCount() const {
  return static_cast<int>(game_objects_.size());
}

int Scene::GetCamerasCount() const { return static_cast<int>(cameras_.size()); }

int Scene::GetAmbientLightsCount() const {
  return static_cast<int>(ambient_lights_.size());
}

int Scene::GetDirectionalLightsCount() const {
  return static_cast<int>(directional_lights_.size());
}

int Scene::GetPointLightsCount() const {
  return static_cast<int>(point_lights_.size());
}

void Scene::Update(InputReceiver& input_receiver, const float delta_time) {
  for (auto object_itr = game_objects_.begin();
       object_itr != game_objects_.end(); object_itr++) {
    (*object_itr)->Update(input_receiver, delta_time);
  }
  if (GetMainCamera() != nullptr) {
    GetMainCamera()->Update(input_receiver, delta_time);
  }
}
}  // namespace ho_renderer