#include "graphics/rendering_pipeline/pipeline_components/include/perspective_divider.h"

#include "core/math/include/math_utils.h"
#include "core/math/include/vector4.h"

namespace ho_renderer {

PerspectiveDivider::PerspectiveDivider() = default;
PerspectiveDivider::~PerspectiveDivider() = default;

TransformedVertex& PerspectiveDivider::PerspectiveDivide(
    TransformedVertex& vertex) const {
  vertex.set_ndc(vertex.clip_coord().ToCartesianCoordinate());
  return vertex;
}
}  // namespace ho_renderer
