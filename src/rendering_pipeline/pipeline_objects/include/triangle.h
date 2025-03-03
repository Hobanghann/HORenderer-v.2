#ifndef _HORENDERER_RENDERINGPIPELINE_PIPELINEOBJECT_TRIANGLE_H_
#define _HORENDERER_RENDERINGPIPELINE_PIPELINEOBJECT_TRIANGLE_H_

// Responsibility : define Triangle as primitive used in rendering pipeline

#include <cstdint>

#include "math/include/vector3.h"
#include "rendering_pipeline/pipeline_objects/include/primitive.h"

namespace ho_renderer {
class Triangle : public Primitive {
 public:
  Triangle() = delete;
  Triangle(const Triangle& triangle);
  Triangle(int index0, int index1, int index2, const Vector3& normal_vector);
  Triangle(int index0, int index1, int index2, const Vector3& normal_vector,
           const LinearRGB& color);
  Triangle(int index0, int index1, int index2, const Vector3& normal_vector,
           const LinearRGB& color, float coefficient, float shininess);
  Triangle& operator=(const Triangle& triangle);
  ~Triangle();

  const int index0() const;
  const int index1() const;
  const int index2() const;
  const bool is_backface() const;
  const Vector3& normal_vector() const;
  const float specular_reflection_coefficient() const;
  const float shininess() const;

  Triangle& set_index0(int index0);
  Triangle& set_index1(int index1);
  Triangle& set_index2(int index2);
  Triangle& set_is_backface(bool arg);
  Triangle& set_normal_vector(const Vector3& normal_vector);
  Triangle& set_specular_reflection_coefficient(const float c);
  Triangle& set_shininess(const float s);

 private:
  int index0_;
  int index1_;
  int index2_;
  bool is_backface_;
  Vector3 normal_vector_;
  float specular_reflection_coefficient_;
  float shininess_;
};

}  // namespace ho_renderer

#endif  // _HORENDERER_RENDERINGPIPELINE_PIPELINEOBJECT_TRIANGLE_H_