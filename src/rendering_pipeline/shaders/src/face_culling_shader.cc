#include "rendering_pipeline/shaders/include/face_culling_shader.h"

#include "app/include/debug.h"
#include "math/include/math_utils.h"
#include "math/include/vector3.h"

namespace ho_renderer {
FaceCullingShader::FaceCullingShader() = default;
FaceCullingShader::~FaceCullingShader() = default;

void FaceCullingShader::BackfaceCulling(
    std::vector<Primitive*>& primitive_buffer,
    std::vector<Vector3>& coordinate_buffer,
    const Vector3& view_direction) const {
  for (auto triangle_itr = primitive_buffer.begin();
       triangle_itr != primitive_buffer.end(); triangle_itr++) {
    Triangle& triangle = static_cast<Triangle&>(**triangle_itr);
    if (triangle.is_outof_frustum()) {
      continue;
    }
    const Vector3& i0_to_i1 = coordinate_buffer[triangle.index1()] -
                              coordinate_buffer[triangle.index0()];
    const Vector3& i0_to_i2 = coordinate_buffer[triangle.index2()] -
                              coordinate_buffer[triangle.index0()];
    const Vector3& normal_vector = i0_to_i1.Cross(i0_to_i2);
    if (MathUtils::IsLessEqual(normal_vector.Dot(view_direction), 0.f)) {
      triangle.set_is_backface(false);
    } else {
      triangle.set_is_backface(true);
    }
  }
}

/*In Clip space, frontface is -z, backface is +z.
So Normal vector need to be inversed.*/

}  // namespace ho_renderer