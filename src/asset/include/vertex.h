#ifndef _HORENDERER_ASSET_VERTEX_H_
#define _HORENDERER_ASSET_VERTEX_H_

#include "math/include/vector3.h"
#include "math/include/vector4.h"

namespace ho_renderer {
class Vertex {
 public:
  Vertex(const Vector4& coordinate);
  Vertex(const Vertex&);
  Vertex& operator=(const Vertex&);
  ~Vertex();

  const Vector4& coordinate() const;
  Vertex& set_coordinate(const Vector4& coordinate);

 private:
  Vector4 coordinate_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_ASSET_VERTEX_H_