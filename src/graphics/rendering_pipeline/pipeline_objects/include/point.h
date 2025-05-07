#ifndef _HORENDERER_POINT_H_
#define _HORENDERER_POINT_H_

// Responsibility : define Point as primitive used in rendering pipeline

#include <cstdint>

#include "graphics/rendering_pipeline/pipeline_objects/include/primitive.h"

namespace ho_renderer {
class Point : public Primitive {
 public:
  Point() = delete;
  Point(const Point& point);
  Point(const Material* mat, std::uint32_t index0);
  Point& operator=(const Point& point);
  ~Point();

  std::uint32_t index0() const;

  Point& set_index0(std::uint32_t index);

 private:
  std::uint32_t index0_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_RENDERINGPIPELINE_PIPELINEOBJECT_POINT_H_