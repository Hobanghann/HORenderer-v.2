#include "scene/object/include/game_object.h"

#include <string>

#include "core/input/include/input_listener.h"
#include "core/math/include/affine_transform.h"
#include "core/math/include/math_utils.h"
#include "core/math/include/quaternion_transform.h"
#include "graphics/resource/include/mesh.h"
#include "scene/object/include/transform.h"

namespace ho_renderer {
GameObject::GameObject(const GameObject& game_object) = default;
GameObject::GameObject(const std::string& name, const Transform& transform,
                       const Model* model, float rotate_veclocity)
    : name_(name),
      transform_(transform),
      model_(model),
      rotate_velocity_(rotate_veclocity) {}
GameObject::~GameObject() = default;
GameObject& GameObject::operator=(const GameObject& game_object) = default;

const std::string& GameObject::name() const { return name_; }
const Transform& GameObject::transform() const { return transform_; }
const Model* GameObject::model() const { return model_; }
float GameObject::rotate_velocity() const { return rotate_velocity_; }

GameObject& GameObject::set_transform(const Transform& transform) {
  transform_ = transform;
  return *this;
}
GameObject& GameObject::set_model(const Model* model) {
  model_ = model;
  return *this;
}
GameObject& GameObject::set_rotate_velocity(float velocity) {
  rotate_velocity_ = velocity;
  return *this;
}

AffineTransform GameObject::GetModelingTransform() const {
  AffineTransform scale_transform =
      LinearTransform::CreateScaleTransform(transform_.world_scale())
          .ToAffineTransform();
  AffineTransform rotation_transform =
      LinearTransform::CreateRotationTransform(transform_.world_right(),
                                               transform_.world_up(),
                                               transform_.world_forward())
          .ToAffineTransform();
  AffineTransform translation_transform =
      AffineTransform::CreateTranslationTransform(transform_.world_coord());
  return scale_transform.ComposeWith(rotation_transform)
      .ComposeWith(translation_transform);
}

void GameObject::Update(InputReceiver& input_receiver, float delta_time) {
  if (!is_active()) {
    return;
  }
  if (input_receiver.IsPressed(kMOUSE_LBUTTON)) {
    EulerAngle e_angle;
    float mouse_delta_x =
        input_receiver.GetMouseDeltaX() * rotate_velocity_ * delta_time;
    float mouse_delta_y =
        input_receiver.GetMouseDeltaY() * rotate_velocity_ * delta_time;
    e_angle.set_yaw_angle(mouse_delta_x);
    e_angle.set_pitch_angle(mouse_delta_y);
    QuaternionTransform r_transform =
        QuaternionTransform::CreateRotationTransform(e_angle);
    Vector3 transformed_forward =
        r_transform.Transform(transform_.world_forward()).GetNormalized();
    Vector3 transformed_right =
        r_transform.Transform(transform_.world_right()).GetNormalized();
    Vector3 transformed_up =
        r_transform.Transform(transform_.world_up()).GetNormalized();
    transform_.set_world_forward(transformed_forward);
    transform_.set_world_right(transformed_right);
    transform_.set_world_up(transformed_up);
  }
}
}  // namespace ho_renderer