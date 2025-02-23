#ifndef _HORENDERER_ASSET_SCENE_H_
#define _HORENDERER_ASSET_SCENE_H_

#include <memory>
#include <string>
#include <vector>

#include "asset/include/camera_object.h"
#include "asset/include/game_object.h"
#include "engine/include/input_listener.h"

namespace ho_renderer {
class Scene : public InputListener {
 public:
  Scene() = delete;
  Scene(const std::string& name);
  Scene(const Scene& scene) = delete;
  ~Scene();
  Scene& operator=(const Scene& scene) = delete;

  const std::string& name() const;
  const CameraObject& main_camera() const;
  void SetMainCamera(const std::string& name);

  void AddGameObject(GameObject* game_object);
  void AddCameraObject(CameraObject* camera_object);

  void DeleteGameObject(const std::string& name);
  void DeleteGameObject(const int index);
  void DeleteCameraObject(const std::string& name);
  void DeleteCameraObject(const int index);

  const GameObject& GetGameObject(const std::string& name) const;
  const GameObject& GetGameObject(const int index) const;
  const CameraObject& GetCameraObject(const std::string& name) const;
  const CameraObject& GetCameraObject(const int index) const;

  int GetGameObjectNum() const;
  int GetCameraObjectNum() const;

  void Update(InputReceiver& input_receiver,
              const float delta_time) override;

 private:
  std::string name_;
  std::vector<GameObject*> game_objects_;
  std::vector<CameraObject*> camera_objects_;
  CameraObject* main_camera_;
};
}  // namespace ho_renderer
#endif  // _HORENDERER_ASSET_SCENE_H_
