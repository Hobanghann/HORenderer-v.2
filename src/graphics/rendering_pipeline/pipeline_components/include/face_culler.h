#ifndef _HORENDERER_FACE_CULLER_H_
#define _HORENDERER_FACE_CULLER_H_

#include <memory>
#include <vector>

#include "core/math/include/vector3.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/transformed_vertex.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/triangle.h"
#include "graphics/rendering_pipeline/system/include/pipeline_enum.h"

namespace ho_renderer {
class FaceCuller {
 public:
  FaceCuller();
  FaceCuller(const FaceCuller&) = delete;
  FaceCuller& operator=(const FaceCuller&) = delete;
  ~FaceCuller();

  void BackfaceCulling(Triangle* t, std::vector<TransformedVertex>* v_buffer,
                       const Vector3& view_direction, IndexOrder order) const;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_FACE_CULLER_H_