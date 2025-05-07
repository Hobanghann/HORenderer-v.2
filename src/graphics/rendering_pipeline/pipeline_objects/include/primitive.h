#ifndef _HORENDERER_PRIMITIVE_H_
#define _HORENDERER_PRIMITIVE_H_

#include "core/math/include/vector3.h"
#include "graphics/resource/include/material.h"

namespace ho_renderer {
class Primitive {
 public:
  enum class Type : std::uint8_t { kPoint = 0, kLine, kTriangle };
  Primitive() = delete;
  Primitive(Type type, const Material* mat);
  Primitive(const Primitive&);
  Primitive& operator=(const Primitive&);
  virtual ~Primitive();

  Primitive& set_is_outof_frustum(bool arg);

  Type type() const;
  const Material* material() const;
  const bool is_outof_frustum() const;

 private:
  Type type_;
  const Material* material_;
  bool is_outof_frustum_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_PRIMITIVE_H_