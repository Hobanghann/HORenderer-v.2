#ifndef _HORENDERER_TRANSFORM_H_
#define _HORENDERER_TRANSFORM_H_

#include "core/math/include/vector3.h"

namespace ho_renderer {
class Transform {
 public:
  Transform();
  Transform(const Vector3& position, const Vector3& forward,
            const Vector3& right, const Vector3& up, float scale);
  Transform(const Transform& transform);
  Transform& operator=(const Transform& transform);
  ~Transform();

  const Vector3& world_coord() const;
  const Vector3& world_forward() const;
  const Vector3& world_right() const;
  const Vector3& world_up() const;
  float world_scale() const;
  Transform& set_world_coord(const Vector3& position);
  Transform& set_world_forward(const Vector3& forward);
  Transform& set_world_right(const Vector3& right);
  Transform& set_world_up(const Vector3& up);
  Transform& set_world_scale(float scale);

 private:
  Vector3 world_coord_;
  // object's rotation state is stored as local axis in world space
  // object's rotational transform defined by this local axis
  // when object's rotation state needs to be updated, it is performed by
  // transformation of this local axis.
  Vector3 world_forward_;
  Vector3 world_right_;
  Vector3 world_up_;
  float world_scale_;
};
}  // namespace ho_renderer
#endif  // _HORENDERER_TRANSFORM_H_