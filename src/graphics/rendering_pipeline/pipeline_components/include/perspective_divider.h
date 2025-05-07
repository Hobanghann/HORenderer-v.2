#ifndef _HORENDERER_PERSPECTIVE_DIVIDER_H_
#define _HORENDERER_PERSPECTIVE_DIVIDER_H_

#include "graphics/rendering_pipeline/pipeline_objects/include/transformed_vertex.h"

namespace ho_renderer {
class PerspectiveDivider {
 public:
  PerspectiveDivider();
  PerspectiveDivider(const PerspectiveDivider&) = delete;
  PerspectiveDivider& operator=(const PerspectiveDivider&) = delete;
  ~PerspectiveDivider();

  TransformedVertex& PerspectiveDivide(TransformedVertex& vertex) const;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_PERSPECTIVE_DIVIDER_H_