#ifndef _HORENDERER_RENDERINGPIPELINE_PIPELINEOBJECT_POINT_H_
#define _HORENDERER_RENDERINGPIPELINE_PIPELINEOBJECT_POINT_H_

// Responsibility : define Point as primitive used in rendering pipeline

#include <cstdint>

#include "rendering_pipeline/pipeline_objects/include/primitive.h"

namespace ho_renderer {
class Point : public Primitive {
 public:
  Point() = delete;
  Point(const Point& point);
  Point(int index0);
  Point(int index0, std::uint32_t color_bit);
  Point& operator=(const Point& point);
  ~Point();

  const int index0() const;

  Point& set_index0(int index0);

 private:
  int index0_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_RENDERINGPIPELINE_PIPELINEOBJECT_POINT_H_