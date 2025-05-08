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
#include "tools/include/debug.h"

namespace ho_renderer {

Scene::Scene(const std::string& name)
    : name_(name),
      main_camera_index_(-1),
      main_ambient_light_index_(-1),
      main_directional_light_index_(-1) {}

Scene::~Scene() = default;

const std::string& Scene::name() const { return name_; }

Camera* Scene::GetMainCamera() const {
  ASSERT_MSG(main_camera_index_ >= 0 &&
                 main_camera_index_ < static_cast<int>(cameras_.size()),
             "Scene::GetMainCamera Error : main_camera_index_ is invalid (out "
             "of range)");
  if (main_camera_index_ < 0 ||
      main_camera_index_ >= static_cast<int>(cameras_.size())) {
    return nullptr;
  }
  return cameras_[main_camera_index_].get();
}

AmbientLight* Scene::GetMainAmbientLight() const {
  ASSERT_MSG(
      main_ambient_light_index_ >= 0 &&
          main_ambient_light_index_ < static_cast<int>(ambient_lights_.size()),
      "Scene::GetMainAmbientLight Error : main_ambient_light_index_ is invalid "
      "(out of range)");
  if (main_ambient_light_index_ < 0 ||
      main_ambient_light_index_ >= static_cast<int>(ambient_lights_.size())) {
    return nullptr;
  }
  return ambient_lights_[main_ambient_light_index_].get();
}

DirectionalLight* Scene::GetMainDirectionalLight() const {
  ASSERT_MSG(main_directional_light_index_ >= 0 &&
                 main_directional_light_index_ <
                     static_cast<int>(directional_lights_.size()),
             "Scene::GetMainDirectionalLight : main_directional_light_index_ "
             "is invalid "
             "(out of range)");
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
  ASSERT_MSG(it != cameras_.end(),
             "Scene::SetMainCamera Error : no camera with given name exists in "
             "the scene");
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
  ASSERT_MSG(
      it != ambient_lights_.end(),
      "Scene::SetMainAmbientLight Error : no ambient lights with given name "
      "exists in the scene");
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
  ASSERT_MSG(it != directional_lights_.end(),
             "Scene::SetMainDirectionalLight Error : no directional lights "
             "with given name exists in the scene");
  if (it == directional_lights_.end()) {
    return false;
  }
  main_directional_light_index_ =
      static_cast<int>(std::distance(directional_lights_.begin(), it));
  return true;
}

bool Scene::AddGameObject(std::unique_ptr<GameObject> game_object) {
  ASSERT_MSG(game_object != nullptr,
             "Scene::AddGameObject Error : game_object must not be null");
  if (!game_object) return false;
  auto it = std::find_if(game_objects_.begin(), game_objects_.end(),
                         [&](const std::unique_ptr<GameObject>& obj) {
                           return obj->name() == game_object->name();
                         });
  ASSERT_MSG(it == game_objects_.end(),
             "Scene::AddGameObject Error : game object with same name already "
             "exists in the scene");
  if (it != game_objects_.end()) {
    return false;
  }
  game_objects_.emplace_back(std::move(game_object));
  return true;
}

bool Scene::AddCamera(std::unique_ptr<Camera> camera) {
  ASSERT_MSG(camera != nullptr,
             "Scene::AddCamera Error: camera must not be null");
  if (!camera) return false;
  auto it = std::find_if(cameras_.begin(), cameras_.end(),
                         [&](const std::unique_ptr<Camera>& cam) {
                           return cam->name() == camera->name();
                         });
  ASSERT_MSG(
      it == cameras_.end(),
      "Scene::AddCamera Error: camera with same name already exists in scene");
  if (it != cameras_.end()) {
    return false;
  }
  cameras_.emplace_back(std::move(camera));
  return true;
}

bool Scene::AddAmbientLight(std::unique_ptr<AmbientLight> light) {
  ASSERT_MSG(light != nullptr,
             "Scene::AddAmbientLight Error: light must not be null");
  if (!light) return false;
  auto it = std::find_if(ambient_lights_.begin(), ambient_lights_.end(),
                         [&](const std::unique_ptr<AmbientLight>& l) {
                           return l->name() == light->name();
                         });
  ASSERT_MSG(it == ambient_lights_.end(),
             "Scene::AddAmbientLight Error: light with same name already "
             "exists in scene");
  if (it != ambient_lights_.end()) {
    return false;
  }
  ambient_lights_.emplace_back(std::move(light));
  return true;
}

bool Scene::AddDirectionalLight(std::unique_ptr<DirectionalLight> light) {
  ASSERT_MSG(light != nullptr,
             "Scene::AddDirectionalLight Error: light must not be null");
  if (!light) return false;
  auto it = std::find_if(directional_lights_.begin(), directional_lights_.end(),
                         [&](const std::unique_ptr<DirectionalLight>& l) {
                           return l->name() == light->name();
                         });
  ASSERT_MSG(it == directional_lights_.end(),
             "Scene::AddDirectionalLight Error: light with same name already "
             "exists in scene");
  if (it != directional_lights_.end()) {
    return false;
  }
  directional_lights_.emplace_back(std::move(light));
  return true;
}

bool Scene::AddPointLight(std::unique_ptr<PointLight> light) {
  ASSERT_MSG(light != nullptr,
             "Scene::AddPointLight Error: light must not be null");
  if (!light) return false;
  auto it = std::find_if(point_lights_.begin(), point_lights_.end(),
                         [&](const std::unique_ptr<PointLight>& p) {
                           return p->name() == light->name();
                         });
  ASSERT_MSG(it == point_lights_.end(),
             "Scene::AddPointLight Error: light with same name already exists "
             "in scene");
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
  ASSERT_MSG(it != game_objects_.end(),
             "Scene::DeleteGameObject Error: object with given name does not "
             "exist in the scene");
  if (it == game_objects_.end()) return false;
  game_objects_.erase(it);
  return true;
}
bool Scene::DeleteGameObject(int index) {
  ASSERT_MSG(index >= 0 && index < static_cast<int>(game_objects_.size()),
             "Scene::DeleteGameObject Error: index out of range");
  if (index < 0 || index >= static_cast<int>(game_objects_.size()))
    return false;
  game_objects_.erase(game_objects_.begin() + index);
  return true;
}

bool Scene::DeleteCamera(const std::string& name) {
  auto it = std::find_if(
      cameras_.begin(), cameras_.end(),
      [&](const std::unique_ptr<Camera>& cam) { return cam->name() == name; });
  ASSERT_MSG(it != cameras_.end(),
             "Scene::DeleteCamera Error: camera with given name does not exist "
             "in the scene");
  if (it == cameras_.end()) return false;

  int index = static_cast<int>(std::distance(cameras_.begin(), it));
  ASSERT_MSG(index != main_camera_index_,
             "Scene::DeleteCamera Error: cannot delete main camera");
  if (index == main_camera_index_) {
    return false;
  }
  cameras_.erase(it);
  return true;
}
bool Scene::DeleteCamera(int index) {
  ASSERT_MSG(index >= 0 && index < static_cast<int>(cameras_.size()),
             "Scene::DeleteCamera Error: index out of range");
  ASSERT_MSG(index != main_camera_index_,
             "Scene::DeleteCamera Error: cannot delete main camera");
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
  ASSERT_MSG(it != ambient_lights_.end(),
             "Scene::DeleteAmbientLight Error: light with given name does not "
             "exist in the scene");
  if (it == ambient_lights_.end()) return false;
  int index = static_cast<int>(std::distance(ambient_lights_.begin(), it));
  ASSERT_MSG(
      index != main_ambient_light_index_,
      "Scene::DeleteAmbientLight Error: cannot delete main ambient light");
  if (index == main_ambient_light_index_) {
    return false;
  }
  ambient_lights_.erase(it);
  return true;
}
bool Scene::DeleteAmbientLight(int index) {
  ASSERT_MSG(index >= 0 && index < static_cast<int>(ambient_lights_.size()),
             "Scene::DeleteAmbientLight Error: index out of range");
  ASSERT_MSG(
      index != main_ambient_light_index_,
      "Scene::DeleteAmbientLight Error: cannot delete main ambient light");
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
  ASSERT_MSG(it != directional_lights_.end(),
             "Scene::DeleteDirectionalLight Error: light with given name does "
             "not exist in the scene");
  if (it == directional_lights_.end()) return false;
  int index = static_cast<int>(std::distance(directional_lights_.begin(), it));
  ASSERT_MSG(index != main_directional_light_index_,
             "Scene::DeleteDirectionalLight Error: cannot delete main "
             "directional light");
  if (index == main_directional_light_index_) {
    return false;
  }
  directional_lights_.erase(it);
  return true;
}
bool Scene::DeleteDirectionalLight(int index) {
  ASSERT_MSG(index >= 0 && index < static_cast<int>(directional_lights_.size()),
             "Scene::DeleteDirectionalLight Error: index out of range");
  ASSERT_MSG(index != main_directional_light_index_,
             "Scene::DeleteDirectionalLight Error: cannot delete main "
             "directional light");
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
  ASSERT_MSG(it != point_lights_.end(),
             "Scene::DeletePointLight Error: light with given name does not "
             "exist in the scene");
  if (it == point_lights_.end()) return false;
  point_lights_.erase(it);
  return true;
}
bool Scene::DeletePointLight(int index) {
  ASSERT_MSG(index >= 0 && index < static_cast<int>(point_lights_.size()),
             "Scene::DeletePointLight Error: index out of range");
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
  ASSERT_MSG(it != game_objects_.end(),
             "Scene::GetGameObject Error: object with given name does not "
             "exist in the scene");
  return (it != game_objects_.end()) ? it->get() : nullptr;
}
GameObject* Scene::GetGameObject(const int index) const {
  ASSERT_MSG(index >= 0 && index < static_cast<int>(game_objects_.size()),
             "Scene::GetGameObject Error: index out of range");
  if (index < 0 || index >= static_cast<int>(game_objects_.size()))
    return nullptr;
  return game_objects_[index].get();
}

Camera* Scene::GetCamera(const std::string& name) const {
  auto it = std::find_if(
      cameras_.begin(), cameras_.end(),
      [&](const std::unique_ptr<Camera>& cam) { return cam->name() == name; });
  ASSERT_MSG(it != cameras_.end(),
             "Scene::GetCamera Error: camera with given name does not exist in "
             "the scene");
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
  ASSERT_MSG(it != ambient_lights_.end(),
             "Scene::GetAmbientLight Error: light with given name does not "
             "exist in the scene");
  return (it != ambient_lights_.end()) ? it->get() : nullptr;
}
AmbientLight* Scene::GetAmbientLight(const int index) const {
  ASSERT_MSG(index >= 0 && index < static_cast<int>(ambient_lights_.size()),
             "Scene::GetAmbientLight Error: index out of range");
  if (index < 0 || index >= static_cast<int>(ambient_lights_.size()))
    return nullptr;
  return ambient_lights_[index].get();
}
DirectionalLight* Scene::GetDirectionalLight(const std::string& name) const {
  auto it = std::find_if(directional_lights_.begin(), directional_lights_.end(),
                         [&](const std::unique_ptr<DirectionalLight>& l) {
                           return l->name() == name;
                         });
  ASSERT_MSG(it != directional_lights_.end(),
             "Scene::GetDirectionalLight Error: light with given name does not "
             "exist in the scene");
  return (it != directional_lights_.end()) ? it->get() : nullptr;
}
DirectionalLight* Scene::GetDirectionalLight(const int index) const {
  ASSERT_MSG(index >= 0 && index < static_cast<int>(directional_lights_.size()),
             "Scene::GetDirectionalLight Error: index out of range");
  if (index < 0 || index >= static_cast<int>(directional_lights_.size()))
    return nullptr;
  return directional_lights_[index].get();
}
PointLight* Scene::GetPointLight(const std::string& name) const {
  auto it = std::find_if(
      point_lights_.begin(), point_lights_.end(),
      [&](const std::unique_ptr<PointLight>& l) { return l->name() == name; });
  ASSERT_MSG(it != point_lights_.end(),
             "Scene::GetPointLight Error: light with given name does not exist "
             "in the scene");
  return (it != point_lights_.end()) ? it->get() : nullptr;
}
PointLight* Scene::GetPointLight(const int index) const {
  ASSERT_MSG(index >= 0 && index < static_cast<int>(point_lights_.size()),
             "Scene::GetPointLight Error: index out of range");
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