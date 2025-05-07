#ifndef _HORENDERER_GAME_OBJECT_BUILDER_H_
#define _HORENDERER_GAME_OBJECT_BUILDER_H_

#include <memory>
#include <string>

#include "core/math/include/vector3.h"
#include "graphics/resource/include/mesh.h"
#include "scene/object/include/game_object.h"
#include "scene/object/include/transform.h"

namespace ho_renderer {
class GameObjectBuilder {
 public:
  GameObjectBuilder();
  GameObjectBuilder(const GameObjectBuilder&) = delete;
  GameObjectBuilder& operator=(const GameObjectBuilder&) = delete;
  ~GameObjectBuilder();

  GameObjectBuilder& set_name(const std::string& name);
  GameObjectBuilder& set_world_coord(const Vector3& coord);
  GameObjectBuilder& set_world_forward(const Vector3& forward);
  GameObjectBuilder& set_world_right(const Vector3& right);
  GameObjectBuilder& set_world_up(const Vector3& up);
  GameObjectBuilder& set_world_scale(float scale);
  GameObjectBuilder& set_model(const Model* model);
  GameObjectBuilder& set_rotate_velocity(float velocity);

  std::unique_ptr<GameObject> Build() const;
  void Reset();

 private:
  std::string name_;
  Vector3 world_coord_;
  Vector3 world_forward_;
  Vector3 world_right_;
  Vector3 world_up_;
  float world_scale_;
  const Model* model_;
  float rotate_velocity_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_GAME_OBJECT_BUILDER_H_