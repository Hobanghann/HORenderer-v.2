#ifndef _HORENDERER_ENGINE_SCENE_SCENE_H_
#define _HORENDERER_ENGINE_SCENE_SCENE_H_

#include <memory>
#include <string>
#include <vector>

#include "asset/include/camera_object.h"
#include "asset/include/game_object.h"
#include "engine/input/include/input_listener.h"
#include "engine/light/include/ambient_light.h"
#include "engine/light/include/directional_light.h"
#include "engine/light/include/point_light.h"

namespace ho_renderer {
class Scene : public InputListener {
 public:
  Scene() = delete;
  Scene(const std::string& name);
  Scene(const Scene& scene) = delete;
  ~Scene();
  Scene& operator=(const Scene& scene) = delete;

  const std::string& name() const;

  CameraObject* GetMainCamera() const;
  AmbientLight* GetMainAmbientLight() const;
  DirectionalLight* GetMainDirectionalLight() const;

  void SetMainCamera(const std::string& name);
  void SetMainAmbientLight(const std::string& name);
  void SetMainDirectionalLight(const std::string& name);

  void AddGameObject(GameObject* game_object);
  void AddCameraObject(CameraObject* camera_object);
  void AddAmbientLight(AmbientLight* light);
  void AddDirectionalLight(DirectionalLight* light);
  void AddPointLight(PointLight* light);

  void DeleteGameObject(const std::string& name);
  void DeleteGameObject(const int index);
  void DeleteCameraObject(const std::string& name);
  void DeleteCameraObject(const int index);
  void DeleteAmbientLight(const std::string& name);
  void DeleteAmbientLight(const int index);
  void DeleteDirectionalLight(const std::string& name);
  void DeleteDirectionalLight(const int index);
  void DeletePointLight(const std::string& name);
  void DeletePointLight(const int index);

  GameObject* GetGameObject(const std::string& name) const;
  GameObject* GetGameObject(const int index) const;
  CameraObject* GetCameraObject(const std::string& name) const;
  CameraObject* GetCameraObject(const int index) const;
  AmbientLight* GetAmbientLight(const std::string& name) const;
  AmbientLight* GetAmbientLight(const int index) const;
  DirectionalLight* GetDirectionalLight(const std::string& name) const;
  DirectionalLight* GetDirectionalLight(const int index) const;
  PointLight* GetPointLight(const std::string& name) const;
  PointLight* GetPointLight(const int index) const;

  int GetGameObjectNum() const;
  int GetCameraObjectNum() const;
  int GetAmbientLightNum() const;
  int GetDirectionalLightNum() const;
  int GetPointLightNum() const;

  void Update(InputReceiver& input_receiver, const float delta_time) override;

 private:
  std::string name_;
  std::vector<GameObject*> game_objects_;
  std::vector<CameraObject*> camera_objects_;
  int main_camera_index_;
  std::vector<AmbientLight*> ambient_lights_;
  int main_ambient_light_index_;
  std::vector<DirectionalLight*> directional_lights_;
  int main_directional_light_index_;
  std::vector<PointLight*> point_lights_;
};
}  // namespace ho_renderer
#endif  // _HORENDERER_ENGINE_SCENE_SCENE_H_
