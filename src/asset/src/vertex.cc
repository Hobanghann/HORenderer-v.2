#include "asset/include/vertex.h"

#include "app/include/debug.h"

namespace ho_renderer {
Vertex::Vertex(const Vector4& coordinate) : coordinate_(coordinate) {}
Vertex::Vertex(const Vertex&) = default;
Vertex& ho_renderer::Vertex::operator=(const Vertex&) = default;
Vertex::~Vertex() = default;

const Vector4& Vertex::coordinate() const { return coordinate_; }

Vertex& Vertex::set_coordinate(const Vector4& coordinate) {
  coordinate_ = coordinate;
  return *this;
}
}  // namespace ho_renderer