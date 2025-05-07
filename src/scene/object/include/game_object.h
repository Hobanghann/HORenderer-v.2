#ifndef _HORENDERER_GAME_OBJECT_H_
#define _HORENDERER_GAME_OBJECT_H_

#include <memory>
#include <string>

#include "core/input/include/input_listener.h"
#include "core/math/include/affine_transform.h"
#include "graphics/resource/include/model.h"
#include "scene/object/include/transform.h"

namespace ho_renderer {
class GameObject : public InputListener {
 public:
  GameObject() = delete;
  GameObject(const GameObject& game_object);
  GameObject(const std::string& name, const Transform& transform,
             const Model* model, float rotate_veclocity);
  GameObject& operator=(const GameObject& game_object);
  ~GameObject();

  const std::string& name() const;
  const Transform& transform() const;
  const Model* model() const;
  float rotate_velocity() const;

  GameObject& set_transform(const Transform& transform);
  GameObject& set_model(const Model* model);
  GameObject& set_rotate_velocity(float velocity);

  AffineTransform GetModelingTransform() const;

  void Update(InputReceiver& input_receiver, float delta_time) override;

 private:
  std::string name_;
  Transform transform_;
  const Model* model_;
  float rotate_velocity_;
};

}  // namespace ho_renderer
#endif  // _HORENDERER_GAME_OBJECT_H_