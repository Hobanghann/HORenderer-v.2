#ifndef _HORENDERER_ASSET_GAMEOBJECT_H_
#define _HORENDERER_ASSET_GAMEOBJECT_H_

#include <memory>
#include <string>

#include "asset/include/mesh.h"
#include "asset/include/transform.h"
#include "engine/input/include/input_listener.h"

namespace ho_renderer {
class GameObject : public InputListener {
 public:
  GameObject();
  GameObject(const GameObject& game_object);
  GameObject(const std::string& name);
  ~GameObject();
  GameObject& operator=(const GameObject& game_object);

  const std::string& name() const;
  const Transform& transform() const;
  const Mesh& mesh() const;
  GameObject& set_name(const std::string& name);
  GameObject& set_transform(const Transform& transform);
  GameObject& set_mesh(const Mesh* mesh);

  void Update(InputReceiver& input_receiver, const float delta_time) override;

 private:
  std::string name_;
  Transform transform_;
  const Mesh* mesh_;
  float rotate_velocity_;
};

}  // namespace ho_renderer
#endif  // _HORENDERER_ASSET_GAMEOBJECT_H_