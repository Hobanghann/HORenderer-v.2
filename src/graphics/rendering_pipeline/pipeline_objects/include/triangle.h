#ifndef _HORENDERER_TRIANGLE_H_
#define _HORENDERER_TRIANGLE_H_

// Responsibility : define Triangle as primitive used in rendering pipeline

#include <cstdint>

#include "core/math/include/linear_transform.h"
#include "core/math/include/vector3.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/primitive.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/transformed_vertex.h"

namespace ho_renderer {
class Triangle : public Primitive {
 public:
  Triangle() = delete;
  Triangle(const Triangle& triangle);
  Triangle(const Material* material, std::uint32_t index0, std::uint32_t index1,
           std::uint32_t index2);
  Triangle(const Material* material, std::uint32_t index0, std::uint32_t index1,
           std::uint32_t index2, const Vector3& v, const Vector3& center);
  Triangle& operator=(const Triangle& triangle);
  ~Triangle();

  std::uint32_t index0() const;
  std::uint32_t index1() const;
  std::uint32_t index2() const;
  const Vector3& normal() const;
  const Vector3& center() const;
  bool is_backface() const;

  Triangle& set_index0(std::uint32_t index);
  Triangle& set_index1(std::uint32_t index);
  Triangle& set_index2(std::uint32_t index);
  Triangle& set_normal(const Vector3& v);
  Triangle& set_center(const Vector3& v);
  Triangle& set_is_backface(bool arg);

 private:
  std::uint32_t index0_;
  std::uint32_t index1_;
  std::uint32_t index2_;
  // this attributes are used for flat shading mode.
  Vector3 normal_;
  Vector3 center_;
  bool is_backface_;
};

}  // namespace ho_renderer

#endif  // _HORENDERER_RENDERINGPIPELINE_PIPELINEOBJECT_TRIANGLE_H_