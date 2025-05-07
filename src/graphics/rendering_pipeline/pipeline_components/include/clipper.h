#ifndef _HORENDERER_CLIPPER_H_
#define _HORENDERER_CLIPPER_H_

#include <array>
#include <memory>

#include "core/math/include/frustum.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/line.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/point.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/primitive.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/transformed_vertex.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/triangle.h"
#include "graphics/rendering_pipeline/system/include/pipeline_enum.h"

namespace ho_renderer {
class Clipper {
 public:
  Clipper();
  Clipper(const Clipper&) = delete;
  Clipper& operator=(const Clipper&) = delete;
  ~Clipper();

  void ClipPoint(Point* p, std::vector<TransformedVertex>* v_buffer) const;

  void ClipLine(Line* l, std::vector<TransformedVertex>* v_buffer) const;

  std::vector<std::unique_ptr<Triangle>> ClipTriangle(
      Triangle* t, std::vector<TransformedVertex>* v_buffer,
      IndexOrder order) const;

 private:
  enum CoordinateState { kINSIDE, kOUTSIDE };

  CoordinateState CheckCoordinateState(const Vector4& coord, int& num_inside,
                                       Frustum::PlanePosition p) const;

  void ShrinkLine(Line* l, std::vector<TransformedVertex>* v_buffer,
                  const std::array<CoordinateState, 2>& index_states,
                  const std::array<std::uint32_t, 2>& i_buffer,
                  Frustum::PlanePosition p) const;

  std::vector<std::unique_ptr<Triangle>> ClipBufferedTriangle(
      std::vector<std::unique_ptr<Triangle>> t_buffer,
      std::vector<TransformedVertex>* v_buffer, IndexOrder order) const;

  void ShrinkTriangle(Triangle* t, std::vector<TransformedVertex>* v_buffer,
                      IndexOrder order,
                      const std::array<CoordinateState, 3>& index_states,
                      const std::array<std::uint32_t, 3>& i_buffer,
                      Frustum::PlanePosition p) const;

  std::unique_ptr<Triangle> DivideTriangle(
      Triangle* t, std::vector<TransformedVertex>* v_buffer, IndexOrder order,
      const std::array<CoordinateState, 3>& index_states,
      const std::array<std::uint32_t, 3>& i_buffer,
      Frustum::PlanePosition p) const;
  // scalar s is (1-s)*Coordinate1 + s*Coordinate2
  float CalculateScalar(const Vector4& v1, const Vector4& v2,
                        Frustum::PlanePosition p) const;
  // affine combination is (1-s)*Coordinate1 + s*Coordinate2
  TransformedVertex AffineCombination(const TransformedVertex& v1,
                                      const TransformedVertex& v2,
                                      const float scalar) const;
  Vector4 AffineCombination(const Vector4& v1, const Vector4& v2,
                            const float scalar) const;
  Vector3 AffineCombination(const Vector3& v1, const Vector3& v2,
                            const float scalar) const;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_CLIPPER_H_