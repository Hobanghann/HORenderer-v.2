#ifndef _HORENDERER_RENDERINGPIPELINE_SHADERS_CLIPPINGSHADER_H_
#define _HORENDERER_RENDERINGPIPELINE_SHADERS_CLIPPINGSHADER_H_

#include <array>
#include <memory>

#include "asset/include/vertex.h"
#include "engine/color/include/linear_rgb.h"
#include "math/include/frustum.h"
#include "rendering_pipeline/pipeline_objects/include/line.h"
#include "rendering_pipeline/pipeline_objects/include/primitive.h"
#include "rendering_pipeline/pipeline_objects/include/triangle.h"

namespace ho_renderer {
class ClippingShader {
 public:
  ClippingShader();
  ClippingShader(const ClippingShader&) = delete;
  ClippingShader& operator=(const ClippingShader&) = delete;
  ~ClippingShader();

  void ClipPointAgainstFrustum(std::vector<Vertex>& clip_coordinate_buffer,
                               std::vector<Vector3>& view_coordinate_buffer,
                               std::vector<Primitive*>& primitive_buffer) const;

  void ClipLineAgainstFrustum(std::vector<Vertex>& clip_coordinate_buffer,
                              std::vector<Vector3>& view_coordinate_buffer,
                              std::vector<Primitive*>& primitive_buffer) const;

  void ClipTriangleAgainstFrustum(
      std::vector<Vertex>& clip_coordinate_buffer,
      std::vector<Vector3>& view_coordinate_buffer,
      std::vector<Primitive*>& primitive_buffer) const;

 private:
  enum CoordinateState { kINSIDE, kOUTSIDE };

  CoordinateState CheckCoordinateState(const Vector4& coordinate,
                                       int& num_inside,
                                       Frustum::PlanePosition position) const;

  void ShrinkLine(std::vector<Vertex>& clip_coordinate_buffer,
                  std::vector<Vector3>& view_coordinate_buffer,
                  std::vector<Primitive*>& primitive_buffer,
                  const std::array<CoordinateState, 2>& index_states,
                  std::array<int, 2>& index_buffer,
                  Frustum::PlanePosition position, const Line& line) const;

  void ShrinkTriangle(std::vector<Vertex>& clip_coordinate_buffer,
                      std::vector<Vector3>& view_coordinate_buffer,
                      std::vector<Primitive*>& primitive_buffer,
                      const std::array<CoordinateState, 3>& index_states,
                      std::array<int, 3>& index_buffer,
                      Frustum::PlanePosition position,
                      const Triangle& triangle) const;
  void DivideTriangle(std::vector<Vertex>& clip_coordinate_buffer,
                      std::vector<Vector3>& view_coordinate_buffer,
                      std::vector<Primitive*>& primitive_buffer,
                      const std::array<CoordinateState, 3>& index_states,
                      std::array<int, 3>& index_buffer,
                      Frustum::PlanePosition position,
                      const Triangle& triangle) const;
  // scalar s is (1-s)*Coordinate1 + s*Coordinate2
  float CalculateScalar(const Vector4& coordinate1, const Vector4& coordinate2,
                        Frustum::PlanePosition position) const;
  // affine combination is (1-s)*Coordinate1 + s*Coordinate2
  Vector4 AffineCombination(const Vector4& coordinate1,
                            const Vector4& coordinate2,
                            const float scalar) const;
  Vector3 AffineCombination(const Vector3& coordinate1,
                            const Vector3& coordinate2,
                            const float scalar) const;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_RENDERINGPIPELINE_SHADERS_CLIPPINGSHADER_H_