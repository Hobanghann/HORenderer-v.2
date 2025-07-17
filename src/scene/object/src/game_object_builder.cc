#include "scene/object/include/game_object_builder.h"

#include <memory>
#include <string>

#include "core/math/include/vector3.h"
#include "graphics/resource/include/mesh.h"
#include "scene/object/include/transform.h"

namespace ho_renderer {
GameObjectBuilder::GameObjectBuilder()
    : name_("Unnamed"),
      world_coord_(Vector3::kZero),
      world_forward_(Vector3::kUnitZ),
      world_right_(Vector3::kUnitX),
      world_up_(Vector3::kUnitY),
      world_scale_(1.0f),
      model_(nullptr),
      rotate_velocity_(0.0f) {}

GameObjectBuilder::~GameObjectBuilder() = default;

GameObjectBuilder& GameObjectBuilder::set_name(const std::string& name) {
  name_ = name;
  return *this;
}

GameObjectBuilder& GameObjectBuilder::set_world_coord(const Vector3& coord) {
  world_coord_ = coord;
  return *this;
}

GameObjectBuilder& GameObjectBuilder::set_world_forward(
    const Vector3& forward) {
  world_forward_ = forward;
  return *this;
}

GameObjectBuilder& GameObjectBuilder::set_world_right(const Vector3& right) {
  world_right_ = right;
  return *this;
}

GameObjectBuilder& GameObjectBuilder::set_world_up(const Vector3& up) {
  world_up_ = up;
  return *this;
}

GameObjectBuilder& GameObjectBuilder::set_world_scale(float scale) {
  world_scale_ = scale;
  return *this;
}

GameObjectBuilder& GameObjectBuilder::set_model(const Model* model) {
  model_ = model;
  return *this;
}

GameObjectBuilder& GameObjectBuilder::set_rotate_velocity(float velocity) {
  rotate_velocity_ = velocity;
  return *this;
}

std::unique_ptr<GameObject> GameObjectBuilder::Build() const {
  return std::make_unique<GameObject>(
      name_,
      Transform(world_coord_, world_forward_, world_right_, world_up_,
                world_scale_),
      model_, rotate_velocity_);
}

void GameObjectBuilder::Reset() {
  name_ = "Unnamed";
  world_coord_ = Vector3::kZero;
  world_forward_ = Vector3::kUnitZ;
  world_right_ = Vector3::kUnitX;
  world_up_ = Vector3::kUnitY;
  world_scale_ = 1.0f;
  model_ = nullptr;
  rotate_velocity_ = 0.0f;
}

}  // namespace ho_renderer
