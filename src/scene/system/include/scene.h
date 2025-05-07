#ifndef _HORENDERER_SCENE_H_
#define _HORENDERER_SCENE_H_

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
class Scene : public InputListener {
 public:
  Scene() = delete;
  Scene(const std::string& name);
  Scene(const Scene& scene) = delete;
  Scene& operator=(const Scene& scene) = delete;
  ~Scene();

  const std::string& name() const;

  Camera* GetMainCamera() const;
  AmbientLight* GetMainAmbientLight() const;
  DirectionalLight* GetMainDirectionalLight() const;

  bool SetMainCamera(const std::string& name);
  bool SetMainAmbientLight(const std::string& name);
  bool SetMainDirectionalLight(const std::string& name);

  bool AddGameObject(std::unique_ptr<GameObject> game_object);
  bool AddCamera(std::unique_ptr<Camera> camera);
  bool AddAmbientLight(std::unique_ptr<AmbientLight> light);
  bool AddDirectionalLight(std::unique_ptr<DirectionalLight> light);
  bool AddPointLight(std::unique_ptr<PointLight> light);

  bool DeleteGameObject(const std::string& name);
  bool DeleteGameObject(int index);
  bool DeleteCamera(const std::string& name);
  bool DeleteCamera(int index);
  bool DeleteAmbientLight(const std::string& name);
  bool DeleteAmbientLight(int index);
  bool DeleteDirectionalLight(const std::string& name);
  bool DeleteDirectionalLight(int index);
  bool DeletePointLight(const std::string& name);
  bool DeletePointLight(int index);

  GameObject* GetGameObject(const std::string& name) const;
  GameObject* GetGameObject(int index) const;
  Camera* GetCamera(const std::string& name) const;
  Camera* GetCamera(int index) const;
  AmbientLight* GetAmbientLight(const std::string& name) const;
  AmbientLight* GetAmbientLight(int index) const;
  DirectionalLight* GetDirectionalLight(const std::string& name) const;
  DirectionalLight* GetDirectionalLight(int index) const;
  PointLight* GetPointLight(const std::string& name) const;
  PointLight* GetPointLight(int index) const;

  int GetGameObjectsCount() const;
  int GetCamerasCount() const;
  int GetAmbientLightsCount() const;
  int GetDirectionalLightsCount() const;
  int GetPointLightsCount() const;

  void Update(InputReceiver& input_receiver, float delta_time) override;

 private:
  std::string name_;
  std::vector<std::unique_ptr<GameObject>> game_objects_;
  std::vector<std::unique_ptr<Camera>> cameras_;
  int main_camera_index_;
  std::vector<std::unique_ptr<AmbientLight>> ambient_lights_;
  int main_ambient_light_index_;
  std::vector<std::unique_ptr<DirectionalLight>> directional_lights_;
  int main_directional_light_index_;
  std::vector<std::unique_ptr<PointLight>> point_lights_;
};
}  // namespace ho_renderer
#endif  // _HORENDERER_SCENE_H_
