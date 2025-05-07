#ifndef _HORENDERER_LINE_H_
#define _HORENDERER_LINE_H_

// Responsibility : define Line as primitive used in rendering pipeline

#include <cstdint>

#include "graphics/rendering_pipeline/pipeline_objects/include/primitive.h"

namespace ho_renderer {
class Line : public Primitive {
 public:
  Line() = delete;
  Line(const Line& line);
  Line(const Material* mat, std::uint32_t index0, std::uint32_t index1);
  Line& operator=(const Line& line);
  ~Line();

  std::uint32_t index0() const;
  std::uint32_t index1() const;

  Line& set_index0(std::uint32_t index);
  Line& set_index1(std::uint32_t index);

 private:
  std::uint32_t index0_;
  std::uint32_t index1_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_LINE_H_