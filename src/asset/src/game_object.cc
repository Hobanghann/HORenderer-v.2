#include "asset/include/game_object.h"

#include "app/include/debug.h"
#include "asset/include/transform.h"
#include "math/include/math_utils.h"

namespace ho_renderer {
GameObject::GameObject() : rotate_velocity_(MathUtils::kPI * 0.4) {}
GameObject::GameObject(const GameObject& game_object) = default;
GameObject::GameObject(const std::string& name)
    : name_(name), rotate_velocity_(MathUtils::kPI * 0.4) {}
GameObject::~GameObject() = default;
GameObject& GameObject::operator=(const GameObject& game_object) = default;

const std::string& GameObject::name() const { return name_; }
const Transform& GameObject::transform() const { return transform_; }
const Mesh& GameObject::mesh() const { return *mesh_; }
GameObject& GameObject::set_name(const std::string& name) {
  name_ = name;
  return *this;
}
GameObject& GameObject::set_transform(const Transform& transform) {
  transform_ = transform;
  return *this;
}
GameObject& GameObject::set_mesh(const Mesh& mesh) {
  mesh_ = &mesh;
  return *this;
}

void GameObject::Update(InputReceiver& input_receiver, const float delta_time) {
  if (!is_active()) {
    return;
  }
  if (input_receiver.IsPressed(kKEY_W)) {
    transform_.get_world_euler_angle().set_pitch_angle(
        transform_.get_world_euler_angle().pitch_angle() +
        rotate_velocity_ * delta_time);
  }
  if (input_receiver.IsPressed(kKEY_S)) {
    transform_.get_world_euler_angle().set_pitch_angle(
        transform_.get_world_euler_angle().pitch_angle() -
        rotate_velocity_ * delta_time);
  }
  if (input_receiver.IsPressed(kKEY_A)) {
    transform_.get_world_euler_angle().set_yaw_angle(
        transform_.get_world_euler_angle().yaw_angle() -
        rotate_velocity_ * delta_time);
  }
  if (input_receiver.IsPressed(kKEY_D)) {
    transform_.get_world_euler_angle().set_yaw_angle(
        transform_.get_world_euler_angle().yaw_angle() +
        rotate_velocity_ * delta_time);
  }
}
}  // namespace ho_renderer