#include "rendering_pipeline/shaders/include/face_culling_shader.h"

#include "app/include/debug.h"
#include "math/include/vector3.h"

namespace ho_renderer {
FaceCullingShader::FaceCullingShader() = default;
FaceCullingShader::~FaceCullingShader() = default;

void FaceCullingShader::BackfaceCullingInViewSpace(
    const std::vector<Vertex>& view_coordinate_buffer,
    std::vector<Primitive*>& primitive_buffer) const {
  for (auto triangle_itr = primitive_buffer.begin();
       triangle_itr != primitive_buffer.end(); triangle_itr++) {
    Triangle& triangle = static_cast<Triangle&>(**triangle_itr);
    if (triangle.is_outof_frustum()) {
      continue;
    }
    Vector3 vector_0to1 =
        (view_coordinate_buffer[triangle.index1()].coordinate() -
         view_coordinate_buffer[triangle.index0()].coordinate())
            .ToVector3();
    Vector3 vector_0to2 =
        (view_coordinate_buffer[triangle.index2()].coordinate() -
         view_coordinate_buffer[triangle.index0()].coordinate())
            .ToVector3();
    Vector3 normal_vector = vector_0to1.Cross(vector_0to2);
    if (normal_vector.Dot(-1.f * Vector3::kUnitZ) < 0.f) {
      triangle.set_is_backface(false);
    } else {
      triangle.set_is_backface(true);
    }
  }
}

/*In Clip space, frontface is -z, backface is +z.
So Normal vector need to be inversed.*/
void FaceCullingShader::BackfaceCullingInClipSpace(
    const std::vector<Vector3>& ndc_buffer,
    std::vector<Primitive*>& primitive_buffer) const {
  for (auto triangle_itr = primitive_buffer.begin();
       triangle_itr != primitive_buffer.end(); triangle_itr++) {
    Triangle& triangle = static_cast<Triangle&>(**triangle_itr);
    if (triangle.is_outof_frustum()) {
      continue;
    }
    Vector3 vector_0to1 =
        ndc_buffer[triangle.index1()] - ndc_buffer[triangle.index0()];
    Vector3 vector_0to2 =
        ndc_buffer[triangle.index2()] - ndc_buffer[triangle.index0()];
    Vector3 normal_vector = vector_0to1.Cross(vector_0to2);
    if ((-1.f * normal_vector).Dot(Vector3::kUnitZ) < 0.f) {
      triangle.set_is_backface(false);
    } else {
      triangle.set_is_backface(true);
    }
  }
}
}  // namespace ho_renderer