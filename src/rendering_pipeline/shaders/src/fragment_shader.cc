#include "rendering_pipeline/shaders/include/fragment_shader.h"

#include "app/include/debug.h"
#include "rendering_pipeline/pipeline_objects/include/line.h"
#include "rendering_pipeline/pipeline_objects/include/point.h"
#include "rendering_pipeline/pipeline_objects/include/triangle.h"

namespace ho_renderer {
FragmentShader::FragmentShader() = default;
FragmentShader::~FragmentShader() = default;

const FragmentShader& FragmentShader::ReadFragmentColorFromPrimitive(
    Fragment& fragment) const {
  switch (fragment.belonging_primitive_type()) {
    case kPOINT:
      fragment.set_color_bit(
          static_cast<const Point&>(fragment.belonging_primitive())
              .color_bit());
      break;
    case kLINE:
      fragment.set_color_bit(
          static_cast<const Line&>(fragment.belonging_primitive()).color_bit());
      break;
    case kTRIANGLE:
      fragment.set_color_bit(
          static_cast<const Triangle&>(fragment.belonging_primitive())
              .color_bit());
      break;
  }
  return *this;
}
}  // namespace ho_renderer