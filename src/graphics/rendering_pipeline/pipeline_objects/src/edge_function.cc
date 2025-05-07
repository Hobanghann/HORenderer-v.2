#include "graphics/rendering_pipeline/pipeline_objects/include/edge_function.h"

namespace ho_renderer {
EdgeFunction::EdgeFunction(const Vector2& start_point, const Vector2& end_point,
                           const Vector2& initial_point) {
  dx_ = end_point.y() - start_point.y();
  dy_ = start_point.x() - end_point.x();
  initial_value_ =
      dx_ * initial_point.x() + dy_ * initial_point.y() +
      (end_point.x() * start_point.y() - start_point.x() * end_point.y());
}
EdgeFunction::~EdgeFunction() = default;

const int EdgeFunction::dx() const { return dx_; }
const int EdgeFunction::dy() const { return dy_; }
const int EdgeFunction::initial_value() const { return initial_value_; }
}  // namespace ho_renderer