#include "graphics/rendering_pipeline/pipeline_objects/include/transformed_vertex.h"

#include "tools/include/debug.h"

namespace ho_renderer {

TransformedVertex::TransformedVertex(const TransformedVertex& tv) = default;
TransformedVertex::TransformedVertex(const Vertex* source)
    : view_coord_(Vector3::kZero),
      clip_coord_(Vector4::kUnitW),
      ndc_(Vector3::kZero),
      viewport_ndc_(Vector3::kZero),
      texture_coord_(source->texture_coord()),
      normal_vector_(source->normal_vector()),
      tangent_vector_(source->tangent_vector()),
      source_vertex_(source) {}
TransformedVertex& TransformedVertex::operator=(const TransformedVertex& tv) =
    default;
TransformedVertex::~TransformedVertex() = default;

const Vector3& TransformedVertex::view_coord() const { return view_coord_; }
const Vector4& TransformedVertex::clip_coord() const { return clip_coord_; }
const Vector3& TransformedVertex::ndc() const { return ndc_; }
const Vector3& TransformedVertex::viewport_ndc() const { return viewport_ndc_; }
const Vector3& TransformedVertex::texture_coord() const {
  return texture_coord_;
}
const Vector3& TransformedVertex::normal_vector() const {
  return normal_vector_;
}
const Vector3& TransformedVertex::tangent_vector() const {
  return tangent_vector_;
}
float TransformedVertex::handedness() const {
  return source_vertex_->handedness();
}
const Vertex* TransformedVertex::source_vertex() const {
  return source_vertex_;
}

TransformedVertex& TransformedVertex::set_view_coord(const Vector3& v) {
  view_coord_ = v;
  return *this;
}
TransformedVertex& TransformedVertex::set_clip_coord(const Vector4& v) {
  clip_coord_ = v;
  return *this;
}
TransformedVertex& TransformedVertex::set_ndc(const Vector3& v) {
  ndc_ = v;
  return *this;
}
TransformedVertex& TransformedVertex::set_viewport_ndc(const Vector3& v) {
  viewport_ndc_ = v;
  return *this;
}

TransformedVertex& TransformedVertex::set_texture_coord(const Vector3& v) {
  texture_coord_ = v;
  return *this;
}

TransformedVertex& TransformedVertex::set_normal_vector(const Vector3& v) {
  normal_vector_ = v;
  return *this;
}
TransformedVertex& TransformedVertex::set_tangent_vector(const Vector3& v) {
  tangent_vector_ = v;
  return *this;
}

TransformedVertex TransformedVertex::operator+(
    const TransformedVertex& rhs) const {
  return TransformedVertex(*this) += rhs;
}

TransformedVertex& TransformedVertex::operator+=(const TransformedVertex& rhs) {
  view_coord_ += rhs.view_coord_;
  clip_coord_ += rhs.clip_coord_;
  ndc_ += rhs.ndc_;
  viewport_ndc_ += rhs.viewport_ndc_;
  texture_coord_ += rhs.texture_coord_;
  normal_vector_ += rhs.normal_vector_;
  tangent_vector_ += rhs.tangent_vector_;
  return *this;
}

TransformedVertex TransformedVertex::operator-(
    const TransformedVertex& rhs) const {
  return TransformedVertex(*this) -= rhs;
}

TransformedVertex& TransformedVertex::operator-=(const TransformedVertex& rhs) {
  view_coord_ -= rhs.view_coord_;
  clip_coord_ -= rhs.clip_coord_;
  ndc_ -= rhs.ndc_;
  viewport_ndc_ -= rhs.viewport_ndc_;
  texture_coord_ -= rhs.texture_coord_;
  normal_vector_ -= rhs.normal_vector_;
  tangent_vector_ -= rhs.tangent_vector_;
  return *this;
}

TransformedVertex TransformedVertex::operator*(float scalar) const {
  return TransformedVertex(*this) *= scalar;
}

TransformedVertex& TransformedVertex::operator*=(float scalar) {
  view_coord_ *= scalar;
  clip_coord_ *= scalar;
  ndc_ *= scalar;
  viewport_ndc_ *= scalar;
  texture_coord_ *= scalar;
  normal_vector_ *= scalar;
  tangent_vector_ *= scalar;
  return *this;
}

TransformedVertex TransformedVertex::operator/(float scalar) const {
  ASSERT_MSG(
      scalar != 0.f,
      "TransformedVertex::operator/ Error : scalar must not be zero (Divide "
      "by zero)");
  return TransformedVertex(*this) /= scalar;
}

TransformedVertex& TransformedVertex::operator/=(float scalar) {
  ASSERT_MSG(
      scalar != 0.f,
      "TransformedVertex::operator/= Error : scalar must not be zero (Divide "
      "by zero)");
  float inv_scalar = 1.f / scalar;
  view_coord_ *= inv_scalar;
  clip_coord_ *= inv_scalar;
  ndc_ *= inv_scalar;
  viewport_ndc_ *= inv_scalar;
  texture_coord_ *= inv_scalar;
  normal_vector_ *= inv_scalar;
  tangent_vector_ *= inv_scalar;
  return *this;
}

}  // namespace ho_renderer
