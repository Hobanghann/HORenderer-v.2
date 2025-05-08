#include "graphics/resource/include/vertex.h"

#include "tools/include/debug.h"
namespace ho_renderer {

Vertex::Vertex()
    : position_(Vector4::kUnitW),
      texture_coord_(Vector3::kZero),
      normal_vector_(Vector3::kZero) {}

Vertex::Vertex(const Vector4& p, const Vector3& tc, const Vector3& n,
               const Vector3& tg, float h)
    : position_(p),
      texture_coord_(tc),
      normal_vector_(n),
      tangent_vector_(tg),
      handedness_(h) {}

Vertex::Vertex(const Vertex& v) = default;

Vertex& Vertex::operator=(const Vertex& v) = default;

Vertex::~Vertex() = default;

const Vector4& Vertex::position() const { return position_; }
const Vector3& Vertex::texture_coord() const { return texture_coord_; }
const Vector3& Vertex::normal_vector() const { return normal_vector_; }
const Vector3& Vertex::tangent_vector() const { return tangent_vector_; }
float Vertex::handedness() const { return handedness_; }

Vertex& Vertex::set_position(const Vector4& v) {
  position_ = v;
  return *this;
}
Vertex& Vertex::set_texture_coord(const Vector3& v) {
  texture_coord_ = v;
  return *this;
}
Vertex& Vertex::set_normal_vector(const Vector3& v) {
  normal_vector_ = v;
  return *this;
}
Vertex& Vertex::set_tangent_vector(const Vector3& v) {
  tangent_vector_ = v;
  return *this;
}
Vertex& Vertex::set_handedness(float h) {
  handedness_ = h;
  return *this;
}

Vertex Vertex::operator+(const Vertex& rhs) const {
  return Vertex(*this) += rhs;
}
Vertex& Vertex::operator+=(const Vertex& rhs) {
  position_ += rhs.position_;
  texture_coord_ += rhs.texture_coord_;
  normal_vector_ += rhs.normal_vector_;
  tangent_vector_ += rhs.tangent_vector_;
  handedness_ += handedness_;
  return *this;
}

Vertex Vertex::operator-(const Vertex& rhs) const {
  return Vertex(*this) -= rhs;
}
Vertex& Vertex::operator-=(const Vertex& rhs) {
  position_ -= rhs.position_;
  texture_coord_ -= rhs.texture_coord_;
  normal_vector_ -= rhs.normal_vector_;
  tangent_vector_ -= rhs.tangent_vector_;
  handedness_ -= handedness_;
  return *this;
}

Vertex Vertex::operator*(float scalar) const { return Vertex(*this) *= scalar; }
Vertex& Vertex::operator*=(float scalar) {
  position_ *= scalar;
  texture_coord_ *= scalar;
  normal_vector_ *= scalar;
  tangent_vector_ *= scalar;
  handedness_ *= scalar;
  return *this;
}

Vertex Vertex::operator/(float scalar) const {
  ASSERT_MSG(
      scalar != 0.f,
      "Vertex::operator/ Error: scalar must not be zero (division by zero)");
  return Vertex(*this) /= scalar;
}

Vertex& Vertex::operator/=(float scalar) {
  ASSERT_MSG(
      scalar != 0.f,
      "Vertex::operator/= Error: scalar must not be zero (division by zero)");
  float inv_scalar = 1.f / scalar;
  position_ *= inv_scalar;
  texture_coord_ *= inv_scalar;
  normal_vector_ *= inv_scalar;
  tangent_vector_ *= inv_scalar;
  handedness_ *= inv_scalar;
  return *this;
}

}  // namespace ho_renderer
