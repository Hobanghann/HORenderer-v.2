#ifndef _HORENDERER_VERTEX_H_
#define _HORENDERER_VERTEX_H_

#include "core/math/include/vector3.h"
#include "core/math/include/vector4.h"

namespace ho_renderer {
class Vertex {
 public:
  Vertex();
  Vertex(const Vector4& p, const Vector3& tc, const Vector3& n,
         const Vector3& tg, float h);
  Vertex(const Vertex& v);
  Vertex& operator=(const Vertex& v);
  ~Vertex();

  const Vector4& position() const;
  const Vector3& texture_coord() const;
  const Vector3& normal_vector() const;
  const Vector3& tangent_vector() const;
  float handedness() const;

  Vertex& set_position(const Vector4& v);
  Vertex& set_texture_coord(const Vector3& v);
  Vertex& set_normal_vector(const Vector3& v);
  Vertex& set_tangent_vector(const Vector3& v);
  Vertex& set_handedness(float h);

  Vertex operator+(const Vertex& rhs) const;
  Vertex& operator+=(const Vertex& rhs);
  Vertex operator-(const Vertex& rhs) const;
  Vertex& operator-=(const Vertex& rhs);
  Vertex operator*(float scalar) const;
  Vertex& operator*=(float scalar);
  Vertex operator/(float scalar) const;
  Vertex& operator/=(float scalar);

  float GetHandednessSign() const;

 private:
  Vector4 position_;
  Vector3 texture_coord_;
  Vector3 normal_vector_;
  Vector3 tangent_vector_;
  float handedness_;
};

inline Vertex operator*(float scalar, const Vertex& v) { return v * scalar; }
}  // namespace ho_renderer

#endif  // _HORENDERER_VERTEX_H_