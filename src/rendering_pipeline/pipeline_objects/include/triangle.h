#ifndef _HORENDERER_RENDERINGPIPELINE_PIPELINEOBJECT_TRIANGLE_H_
#define _HORENDERER_RENDERINGPIPELINE_PIPELINEOBJECT_TRIANGLE_H_

// Responsibility : define Triangle as primitive used in rendering pipeline

#include <cstdint>

#include "rendering_pipeline/pipeline_objects/include/primitive.h"

namespace ho_renderer {
class Triangle : public Primitive {
 public:
  Triangle() = delete;
  Triangle(const Triangle& triangle);
  Triangle(int index0, int index1, int index2);
  Triangle(int index0, int index1, int index2, std::uint32_t color_bit);
  Triangle& operator=(const Triangle& triangle);
  ~Triangle();

  const int index0() const;
  const int index1() const;
  const int index2() const;
  const bool is_backface() const;

  Triangle& set_index0(int index0);
  Triangle& set_index1(int index1);
  Triangle& set_index2(int index2);
  Triangle& set_is_backface(bool arg);

 private:
  int index0_;
  int index1_;
  int index2_;
  bool is_backface_;
};

}  // namespace ho_renderer

#endif  // _HORENDERER_RENDERINGPIPELINE_PIPELINEOBJECT_TRIANGLE_H_