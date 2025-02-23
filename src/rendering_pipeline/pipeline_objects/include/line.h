#ifndef _HORENDERER_RENDERINGPIPELINE_PIPELINEOBJECT_LINE_H_
#define _HORENDERER_RENDERINGPIPELINE_PIPELINEOBJECT_LINE_H_

// Responsibility : define Line as primitive used in rendering pipeline

#include <cstdint>

#include "rendering_pipeline/pipeline_objects/include/primitive.h"

namespace ho_renderer {
class Line : public Primitive {
 public:
  Line() = delete;
  Line(const Line& line);
  Line(int index0, int index1);
  Line(int index0, int index1, std::uint32_t color_bit);
  Line& operator=(const Line& line);
  ~Line();

  const int index0() const;
  const int index1() const;

  Line& set_index0(int index0);
  Line& set_index1(int index1);

 private:
  int index0_;
  int index1_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_RENDERINGPIPELINE_PIPELINEOBJECT_LINE_H_