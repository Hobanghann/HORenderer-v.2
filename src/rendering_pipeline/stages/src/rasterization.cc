#include "rendering_pipeline/stages/include/rasterization.h"

#include "app/include/debug.h"
#include "rendering_pipeline/shaders/include/depth_testing_shader.h"

namespace ho_renderer {

Rasterization::Rasterization()
    : rasterizing_shader_(new RasterizingShader()) {}
Rasterization::~Rasterization() = default;

Rasterization& Rasterization::SetInputPipelineSettings(
    PipelineSettings* pipeline_settings) {
  input_pipeline_settings_ = pipeline_settings;
  return *this;
}
Rasterization& Rasterization::SetInputVertexBuffer(
    std::vector<Vertex>* vertex_buffer) {
  input_vertex_buffer_ = vertex_buffer;
  return *this;
}
Rasterization& Rasterization::SetInputViewCoordinateBuffer(
    std::vector<Vector3>* view_coordinate_buffer) {
  input_view_coordinate_buffer_ = view_coordinate_buffer;
  return *this;
}
Rasterization& Rasterization::SetInputNDCBuffer(
    std::vector<Vector3>* ndc_buffer) {
  input_ndc_buffer_ = ndc_buffer;
  return *this;
}
Rasterization& Rasterization::SetInputViewportNDCBuffer(
    std::vector<Vector3>* viewport_ndc_buffer) {
  input_viewport_ndc_buffer_ = viewport_ndc_buffer;
  return *this;
}
Rasterization& Rasterization::SetInputPrimitive(const Primitive* primitive) {
  input_primitive_ = primitive;
  return *this;
}
Rasterization& Rasterization::SetInputFrameBuffer(
    const FrameBuffer* frame_buffer) {
  input_frame_buffer_ = frame_buffer;
  return *this;
}

Rasterization& Rasterization::ResetInputs() {
  input_pipeline_settings_ = nullptr;
  input_vertex_buffer_ = nullptr;
  input_ndc_buffer_ = nullptr;
  input_viewport_ndc_buffer_ = nullptr;
  input_primitive_ = nullptr;
  input_frame_buffer_ = nullptr;
  return *this;
}

std::vector<Fragment>* Rasterization::GetOutputFragmentBuffer() const {
  return output_fragment_buffer_;
}

Rasterization& Rasterization::ResetOutputs() {
  output_fragment_buffer_ = nullptr;
  return *this;
}

void Rasterization::Rasterize() {
  if (input_pipeline_settings_ == nullptr) {
#ifdef DEBUG
    DEBUG_MSG("input_pipeline_settings_ is null.")
    assert(false);
#endif
  }
  if (input_vertex_buffer_ == nullptr) {
#ifdef DEBUG
    DEBUG_MSG("input_vertex_buffer_ is null.")
    assert(false);
#endif
  }
  if (input_view_coordinate_buffer_ == nullptr) {
#ifdef DEBUG
    DEBUG_MSG(
        "input_ndc_buffer_ is null.\nRasterization has to "
        "be excuted after perspective divide.")
    assert(false);
#endif
  }
  if (input_viewport_ndc_buffer_ == nullptr) {
#ifdef DEBUG
    DEBUG_MSG(
        "input_viewport_ndc_buffer_ is null.\nRasterization has to "
        "be excuted after viewport transformation.")
    assert(false);
#endif
  }
  if (input_primitive_ == nullptr) {
#ifdef DEBUG
    DEBUG_MSG(
        "input_primitive_ is null.\nRasterization has to "
        "be excuted after primitive assembly.")
    assert(false);
#endif
  }
  switch (input_pipeline_settings_->primitive_type()) {
    case kPOINT:
      output_fragment_buffer_ = rasterizing_shader_->RasterizePoint(
          *input_frame_buffer_, *input_vertex_buffer_, *input_view_coordinate_buffer_,
          *input_viewport_ndc_buffer_,
          *(static_cast<const Point*>(input_primitive_)));
      break;
    case kLINE:
      switch (input_pipeline_settings_->interpolation_mode()) {
        case kAFFINE:
          output_fragment_buffer_ = rasterizing_shader_->RasterizeLineAffine(
              *input_frame_buffer_, 
              *input_vertex_buffer_, *input_view_coordinate_buffer_,
              *input_viewport_ndc_buffer_,

              *(static_cast<const Line*>(input_primitive_)));
          break;
        case kPERSPECTIVE_CORRECT:
          output_fragment_buffer_ =
              rasterizing_shader_->RasterizeLinePerspective(
                  *input_frame_buffer_, 
                  *input_vertex_buffer_, *input_view_coordinate_buffer_,
                  *input_viewport_ndc_buffer_,

                  *(static_cast<const Line*>(input_primitive_)));
          break;
      }
      break;
    case kTRIANGLE:
      switch (input_pipeline_settings_->interpolation_mode()) {
        case kAFFINE:
          switch (input_pipeline_settings_->rendering_mode()) {
            case kWIRE_FRAME:
              output_fragment_buffer_ =
                  rasterizing_shader_->RasterizeWireTriangleAffine(
                      *input_frame_buffer_, 
                      *input_vertex_buffer_, *input_view_coordinate_buffer_,
                      *input_viewport_ndc_buffer_,

                      *(static_cast<const Triangle*>(input_primitive_)));
              break;
            case kFILL:
              output_fragment_buffer_ =
                  rasterizing_shader_->EdgeFunctionRasterizeTriangleAffine(
                      *input_frame_buffer_, 
                      *input_vertex_buffer_, *input_view_coordinate_buffer_,
                      *input_viewport_ndc_buffer_,

                      *(static_cast<const Triangle*>(input_primitive_)));
              break;
            case kTEXTURE_MAPPING:
              break;
          }
          break;
        case kPERSPECTIVE_CORRECT:
          switch (input_pipeline_settings_->rendering_mode()) {
            case kWIRE_FRAME:
              output_fragment_buffer_ =
                  rasterizing_shader_->RasterizeWireTrianglePerspective(
                      *input_frame_buffer_, 
                      *input_vertex_buffer_, *input_view_coordinate_buffer_,
                      *input_viewport_ndc_buffer_,

                      *(static_cast<const Triangle*>(input_primitive_)));
              break;
            case kFILL:
              output_fragment_buffer_ =
                  rasterizing_shader_->EdgeFunctionRasterizeTrianglePerspective(
                      *input_frame_buffer_, 
                      *input_vertex_buffer_, *input_view_coordinate_buffer_,
                      *input_viewport_ndc_buffer_,

                      *(static_cast<const Triangle*>(input_primitive_)));
              break;
            case kTEXTURE_MAPPING:
              break;
          }
          break;
      }
      break;
  }
  // result : fragments in output_fragment_buffer_
}
}  // namespace ho_renderer