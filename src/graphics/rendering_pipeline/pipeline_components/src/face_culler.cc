#include "graphics/rendering_pipeline/pipeline_components/include/face_culler.h"

#include "core/math/include/math_utils.h"
#include "core/math/include/vector3.h"
#include "tools/include/debug.h"

namespace ho_renderer {
FaceCuller::FaceCuller() = default;
FaceCuller::~FaceCuller() = default;

void FaceCuller::BackfaceCulling(Triangle* t,
                                 std::vector<TransformedVertex>* v_buffer,
                                 const Vector3& view_direction,
                                 IndexOrder order) const {
  ASSERT_MSG(t != nullptr,
             "FaceCuller::BackfaceCulling Error : triangle is null");
  ASSERT_MSG(v_buffer != nullptr,
             "FaceCuller::BackfaceCulling Error : vertex buffer is null");
  if (t == nullptr || v_buffer == nullptr) {
    return;
  }
  if (t->is_outof_frustum()) {
    t->set_is_backface(true);
    return;
  }
  const Vector3& i0_to_i1 =
      (*v_buffer)[t->index1()].ndc() - (*v_buffer)[t->index0()].ndc();
  const Vector3& i0_to_i2 =
      (*v_buffer)[t->index2()].ndc() - (*v_buffer)[t->index0()].ndc();
  Vector3 normal_vector;
  switch (order) {
    case kClockWise:
      normal_vector = i0_to_i2.Cross(i0_to_i1);
      break;
    case kCounterClockWise:
      normal_vector = i0_to_i1.Cross(i0_to_i2);
      break;
  }
  if (MathUtils::IsLessEqual(normal_vector.Dot(view_direction), 0.f)) {
    t->set_is_backface(false);
  } else {
    t->set_is_backface(true);
  }
}
}  // namespace ho_renderer

/*In Clip space, frontface is -z, backface is +z.
So Normal vector need to be inversed.*/
