#ifndef _HORENDERER_EDGE_FUNCTION_H_
#define _HORENDERER_EDGE_FUNCTION_H_

#include "core/math/include/vector2.h"

namespace ho_renderer {
class EdgeFunction {
 public:
  EdgeFunction() = delete;
  EdgeFunction(const Vector2& start_point, const Vector2& end_point,
               const Vector2& initial_point);
  EdgeFunction(const EdgeFunction&) = delete;
  EdgeFunction& operator=(const EdgeFunction&) = delete;
  ~EdgeFunction();

  const int dx() const;
  const int dy() const;
  const int initial_value() const;

 private:
  int dx_;
  int dy_;
  int initial_value_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_EDGE_FUNCTION_H_