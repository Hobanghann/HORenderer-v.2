#ifndef _HORENDERER_MATH_AFFINETRANSFORM_H_
#define _HORENDERER_MATH_AFFINETRANSFORM_H_

#include "asset/include/camera_object.h"
#include "asset/include/game_object.h"
#include "math/include/linear_transform.h"
#include "math/include/matrix4x4.h"

namespace ho_renderer {
class AffineTransform {
 public:
  AffineTransform();
  AffineTransform(const AffineTransform& transform);
  AffineTransform(const Matrix4x4& affine_matrix);
  AffineTransform& operator=(const AffineTransform& transform);
  ~AffineTransform();

  static AffineTransform CreateTranslationTransform(
      const Vector3& translation_vector);
  static AffineTransform CreateInverseTranslationTransform(
      const Vector3& translation_vector);
  static AffineTransform CreateModelingTransform(const GameObject& game_object);
  static AffineTransform CreateViewTransform(const CameraObject& camera_object);
  static AffineTransform CreateProjectionTransform(
      const CameraObject& camera_object);
  static AffineTransform CreateReversedProjectionTransform(
      const CameraObject& camera_object);

  // compose with translation vector
  AffineTransform& ComposeWith(const AffineTransform& affine_transform);
  AffineTransform GetComposeWith(const AffineTransform& affine_transform) const;
  Vector4 Transform(const Vector4& vector) const;
  LinearTransform ExtractLinearTransform() const;
  const Matrix4x4& matrix() const;

 private:
  Matrix4x4 matrix_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_MATH_AFFINETRANSFORM_H_