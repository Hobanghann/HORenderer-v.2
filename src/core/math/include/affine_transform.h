#ifndef _HORENDERER_AFFINE_TRANSFORM_H_
#define _HORENDERER_AFFINE_TRANSFORM_H_

#include <string>
#include <vector>

#include "core/math/include/linear_transform.h"
#include "core/math/include/matrix4x4.h"
#include "core/math/include/vector3.h"
#include "core/math/include/vector4.h"

namespace ho_renderer {
class AffineTransform {
 public:
  AffineTransform();
  AffineTransform(const AffineTransform& transform);
  explicit AffineTransform(const Matrix4x4& affine_matrix);
  AffineTransform& operator=(const AffineTransform& transform);
  ~AffineTransform();

  static AffineTransform CreateTranslationTransform(
      const Vector3& translation_vector);
  static AffineTransform CreateInverseTranslationTransform(
      const Vector3& translation_vector);

  // compose with translation vector
  AffineTransform& ComposeWith(const AffineTransform& affine_transform);
  AffineTransform GetComposeWith(const AffineTransform& affine_transform) const;
  Vector4 Transform(const Vector4& vector) const;
  LinearTransform GetLinearPart() const;
  const Matrix4x4& matrix() const;

  std::vector<std::string> ToString() const;

 private:
  Matrix4x4 matrix_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_AFFINE_TRANSFORM_H_