#ifndef _HORENDERER_TRANSFORMED_VERTEX_H_
#define _HORENDERER_TRANSFORMED_VERTEX_H_

#include "core/math/include/vector3.h"
#include "core/math/include/vector4.h"
#include "graphics/resource/include/vertex.h"

namespace ho_renderer {
class TransformedVertex {
 public:
  TransformedVertex() = delete;
  TransformedVertex(const TransformedVertex& tv);
  explicit TransformedVertex(const Vertex* source);
  TransformedVertex& operator=(const TransformedVertex& tv);
  ~TransformedVertex();

  const Vector3& view_coord() const;
  const Vector4& clip_coord() const;
  const Vector3& ndc() const;
  const Vector3& viewport_ndc() const;
  const Vector3& texture_coord() const;
  const Vector3& normal_vector() const;
  const Vector3& tangent_vector() const;
  float handedness() const;
  const Vertex* source_vertex() const;

  TransformedVertex& set_view_coord(const Vector3& v);
  TransformedVertex& set_clip_coord(const Vector4& v);
  TransformedVertex& set_ndc(const Vector3& v);
  TransformedVertex& set_viewport_ndc(const Vector3& v);
  TransformedVertex& set_texture_coord(const Vector3& v);
  TransformedVertex& set_normal_vector(const Vector3& v);
  TransformedVertex& set_tangent_vector(const Vector3& v);

  TransformedVertex operator+(const TransformedVertex& rhs) const;
  TransformedVertex& operator+=(const TransformedVertex& rhs);
  TransformedVertex operator-(const TransformedVertex& rhs) const;
  TransformedVertex& operator-=(const TransformedVertex& rhs);
  TransformedVertex operator*(float scalar) const;
  TransformedVertex& operator*=(float scalar);
  TransformedVertex operator/(float scalar) const;
  TransformedVertex& operator/=(float scalar);

 private:
  Vector3 view_coord_;
  Vector4 clip_coord_;
  Vector3 ndc_;
  Vector3 viewport_ndc_;
  Vector3 texture_coord_;
  Vector3 normal_vector_;
  Vector3 tangent_vector_;

  const Vertex* source_vertex_;
};

inline TransformedVertex operator*(float scalar, const TransformedVertex& v) {
  return v * scalar;
}
}  // namespace ho_renderer
#endif  // _HORENDERER_TRANSFORMED_VERTEX_H_