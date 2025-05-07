#include "graphics/rendering_pipeline/pipeline_objects/include/primitive.h"

namespace ho_renderer {
Primitive::Primitive(Type type, const Material* mat)
    : type_(type), material_(mat), is_outof_frustum_(false) {}
Primitive::Primitive(const Primitive&) = default;
Primitive& Primitive::operator=(const Primitive&) = default;
Primitive::~Primitive() = default;

Primitive& Primitive::set_is_outof_frustum(bool arg) {
  is_outof_frustum_ = arg;
  return *this;
}

Primitive::Type Primitive::type() const { return type_; }
const bool Primitive::is_outof_frustum() const { return is_outof_frustum_; }
const Material* Primitive::material() const { return material_; }
}  // namespace ho_renderer