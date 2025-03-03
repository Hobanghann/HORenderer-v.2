#include "rendering_pipeline/stages/include/vertex_post_processing.h"

#include <cassert>

#include "app/include/debug.h"
#include "rendering_pipeline/pipeline/include/resources_manager.h"

namespace ho_renderer {
VertexPostProcessing::VertexPostProcessing()
    : primitive_assembly_shader_(new PrimitiveAssemblyShader()),
      frustum_culling_shader_(new FrustumCullingShader()),
      perspective_divide_shader_(new PerspectiveDivideShader),
      face_culling_shader_(new FaceCullingShader()),
      clipping_shader_(new ClippingShader()),
      viewport_transform_shader_(new ViewportTransformShader()),
      vertex_shader_(new VertexShader()) {}
VertexPostProcessing::~VertexPostProcessing() = default;

VertexPostProcessing& VertexPostProcessing::SetInputGameObject(
    const GameObject* game_object) {
  input_game_object_ = game_object;
  return *this;
}
VertexPostProcessing& VertexPostProcessing::SetInputVertexBuffer(
    std::vector<Vertex>* vertex_buffer) {
  input_vertex_buffer_ = vertex_buffer;
  return *this;
}
VertexPostProcessing& VertexPostProcessing::SetInputIndexBuffer(
    std::vector<uint32_t>* index_buffer) {
  input_index_buffer_ = index_buffer;
  return *this;
}
VertexPostProcessing& VertexPostProcessing::SetInputViewCoordinateBuffer(
    std::vector<Vector3>* view_coordinate_buffer) {
  input_view_coordinate_buffer_ = view_coordinate_buffer;
  return *this;
}
VertexPostProcessing& VertexPostProcessing::SetInputPrimitiveColorBuffer(
    std::vector<LinearRGB>* primitive_color_buffer) {
  input_primitive_color_buffer_ = primitive_color_buffer;
  return *this;
}
VertexPostProcessing& VertexPostProcessing::SetInputFrustum(
    const Frustum* frustum) {
  input_frustum_ = frustum;
  return *this;
}
VertexPostProcessing& VertexPostProcessing::SetInputPipelineSettings(
    PipelineSettings* pipeline_settings) {
  input_pipeline_settings_ = pipeline_settings;
  return *this;
}

VertexPostProcessing& VertexPostProcessing::ResetInputs() {
  input_game_object_ = nullptr;
  input_vertex_buffer_ = nullptr;
  input_index_buffer_ = nullptr;
  input_view_coordinate_buffer_ = nullptr;
  input_primitive_color_buffer_ = nullptr;
  input_frustum_ = nullptr;
  input_pipeline_settings_ = nullptr;
  return *this;
}

std::vector<Primitive*>* VertexPostProcessing::GetOutputPrimitiveBuffer() {
  if (output_primitive_buffer_ == nullptr) {
#ifdef DEBUG
    DEBUG_MSG("output_primitive_buffer_ is null.")
    assert(false);
#endif
  }
  return output_primitive_buffer_;
}
std::vector<Vector3>* VertexPostProcessing::GetOutputNDCBuffer() {
  if (output_ndc_buffer_ == nullptr) {
#ifdef DEBUG
    DEBUG_MSG("output_ndc_buffer_ is null.")
    assert(false);
#endif
  }
  return output_ndc_buffer_;
}
std::vector<Vector3>* VertexPostProcessing::GetOutputViewportNDCBuffer() {
  if (output_viewport_ndc_buffer_ == nullptr) {
#ifdef DEBUG
    DEBUG_MSG("output_viewport_ndc_buffer_ is null.")
    assert(false);
#endif
  }
  return output_viewport_ndc_buffer_;
}
RenderObjectState* VertexPostProcessing::GetOutputRenderObjectStates() {
  if (output_render_object_states_ == nullptr) {
#ifdef DEBUG
    DEBUG_MSG("output_render_object_states_ is null.")
    assert(false);
#endif
  }
  return output_render_object_states_;
}

VertexPostProcessing& VertexPostProcessing::ResetOutputs() {
  output_primitive_buffer_ = nullptr;
  output_ndc_buffer_ = nullptr;
  output_viewport_ndc_buffer_ = nullptr;
  output_render_object_states_ = nullptr;
  return *this;
}

void VertexPostProcessing::Process() {
  if (input_pipeline_settings_ == nullptr) {
#ifdef DEBUG
    DEBUG_MSG("input_pipeline_settings_ is null.")
    assert(false);
#endif
  }
  /////////////////////////////////////////////////////////////////////
  // bounding volume culling
  /////////////////////////////////////////////////////////////////////
  if (input_game_object_ == nullptr) {
#ifdef DEBUG
    DEBUG_MSG("input_game_object_ is null.")
    assert(false);
#endif
  }
  if (input_frustum_ == nullptr) {
#ifdef DEBUG
    DEBUG_MSG("input_frustum_ is null.")
    assert(false);
#endif
  }
  output_render_object_states_ = ResourcesManager::GetClearRenderObjectState();
  switch (input_pipeline_settings_->primitive_type()) {
    // If primitive type is point or line, culling is performed after
    // primitive assembly. because object don't have bounding volume
    case kPOINT:
      output_render_object_states_->set_object_culling_state(kINTERSECT);
      break;
    case kLINE:
      output_render_object_states_->set_object_culling_state(kINTERSECT);
      break;
    case kTRIANGLE:
      switch (input_pipeline_settings_->bounding_volume_mode()) {
        case kSPHERE:
          output_render_object_states_->set_object_culling_state(
              frustum_culling_shader_->CullSphereAgainstFrustum(
                  input_game_object_->mesh().sphere_bounding_volume(),
                  *input_frustum_));
          break;
        case kAABB:
          output_render_object_states_->set_object_culling_state(
              frustum_culling_shader_->CullAABBAgainstFrustum(
                  input_game_object_->mesh().aab_bounding_volume(),
                  *input_frustum_));
          break;
      }

      // result : relation between object and frustum in
      // output_render_object_states->object_culling_state

      // If object is totally outside of frustum, quit rendering pipeline
      // immediately
      if (output_render_object_states_->object_culling_state() ==
          FrustumCullingResult::kOUTSIDE) {
        return;
      }
  }
  /////////////////////////////////////////////////////////////////////
  // primitive assembly
  /////////////////////////////////////////////////////////////////////
  if (input_index_buffer_ == nullptr) {
#ifdef DEBUG
    DEBUG_MSG("input_index_buffer_ is null.")
    assert(false);
#endif
  }

  if (input_pipeline_settings_->rendering_mode() !=
      RenderingMode::kTEXTURE_MAPPING) {
    if (input_primitive_color_buffer_ == nullptr) {
#ifdef DEBUG
      DEBUG_MSG("input_primitive_color_buffer_ is null.")
      assert(false);
#endif
    }
    switch (input_pipeline_settings_->primitive_type()) {
      case kPOINT:
        output_primitive_buffer_ =
            primitive_assembly_shader_->AssembleColoredPoint(
                *input_index_buffer_, *input_primitive_color_buffer_);
        break;
      case kLINE:
        output_primitive_buffer_ =
            primitive_assembly_shader_->AssembleColoredLine(
                *input_index_buffer_, *input_primitive_color_buffer_);
        break;
      case kTRIANGLE:
        if (input_view_coordinate_buffer_ == nullptr) {
#ifdef DEBUG
          DEBUG_MSG("input_view_coordinate_buffer_ is null.")
          assert(false);
#endif
        }
        output_primitive_buffer_ =
            primitive_assembly_shader_->AssembleColoredTriangle(
                *input_index_buffer_, *input_view_coordinate_buffer_,
                *input_primitive_color_buffer_);
        break;
    }
  } else {
    switch (input_pipeline_settings_->primitive_type()) {
      case kPOINT:
        output_primitive_buffer_ =
            primitive_assembly_shader_->AssembleTexturedPoint(
                *input_index_buffer_);
        break;
      case kLINE:
        output_primitive_buffer_ =
            primitive_assembly_shader_->AssembleTexturedLine(
                *input_index_buffer_);
        break;
      case kTRIANGLE:
        output_primitive_buffer_ =
            primitive_assembly_shader_->AssembleTexturedTriangle(
                *input_index_buffer_, *input_view_coordinate_buffer_);
        break;
    }
  }
  // result : primitives in output_primitive_buffer

  /////////////////////////////////////////////////////////////////////
  // frustum clipping
  /////////////////////////////////////////////////////////////////////

  if (input_vertex_buffer_ == nullptr) {
#ifdef DEBUG
    DEBUG_MSG("input_vertex_buffer_ is null.")
    assert(false);
#endif
  }
  if (output_primitive_buffer_ == nullptr) {
#ifdef DEBUG
    DEBUG_MSG(
        "output_primitive_buffer_ is null.\nfrustum clipping have to be "
        "excuted after primitive assembly.")
    assert(false);
#endif
  }
  if (output_render_object_states_->object_culling_state() == kINTERSECT) {
    switch (input_pipeline_settings_->primitive_type()) {
      case kPOINT:
        clipping_shader_->ClipPointAgainstFrustum(
            *input_vertex_buffer_, *input_view_coordinate_buffer_,
            *output_primitive_buffer_);
        break;
      case kLINE:
        clipping_shader_->ClipLineAgainstFrustum(*input_vertex_buffer_,
                                                 *input_view_coordinate_buffer_,
                                                 *output_primitive_buffer_);
        break;
      case kTRIANGLE:
        clipping_shader_->ClipTriangleAgainstFrustum(
            *input_vertex_buffer_, *input_view_coordinate_buffer_,
            *output_primitive_buffer_);
        break;
    }
  }

  // result : clipped primitives in output_primitive_buffer_
  //** In frustum clipping, when triangle division occur,
  // input_vertex_buffer_ doesn't match with transformed_coordinte_buffer_
  // because perspective divide occured before frustum clipping
  // -> frustum clipping should be excuted before perspective divide

  /////////////////////////////////////////////////////////////////////
  // perspective divide
  /////////////////////////////////////////////////////////////////////
  output_ndc_buffer_ = ResourcesManager::GetClearNDCBuffer();
  for (auto vertex_itr = input_vertex_buffer_->cbegin();
       vertex_itr != input_vertex_buffer_->cend(); vertex_itr++) {
    output_ndc_buffer_->push_back(perspective_divide_shader_->PerspectiveDivide(
        vertex_itr->coordinate()));
  }
  // result : NDC in output_transformed_coordinate_buffer
  /////////////////////////////////////////////////////////////////////
  // back face culling
  /////////////////////////////////////////////////////////////////////
  if (output_ndc_buffer_ == nullptr) {
#ifdef DEBUG
    DEBUG_MSG(
        "output_ndc_buffer_ is null.\n backface culling has to be "
        "excuted after perspective divide")
    assert(false);
#endif
  }
  if (input_pipeline_settings_->is_using_backface_culling()) {
    if (input_pipeline_settings_->primitive_type() == kTRIANGLE) {
      face_culling_shader_->BackfaceCulling(*output_primitive_buffer_,
                                            *output_ndc_buffer_,
                                            -1.f * Vector3::kUnitZ);
    }
  }
  /////////////////////////////////////////////////////////////////////
  // viewport transform
  /////////////////////////////////////////////////////////////////////
  if (output_ndc_buffer_ == nullptr) {
#ifdef DEBUG
    DEBUG_MSG(
        "output_ndc_buffer_ is null.\n viewport "
        "transformation has "
        "to be excuted after perspective divide.")
    assert(false);
#endif
  }
  output_viewport_ndc_buffer_ = ResourcesManager::GetClearViewportNDCBuffer();
  for (auto coordinate_itr = output_ndc_buffer_->begin();
       coordinate_itr != output_ndc_buffer_->end(); coordinate_itr++) {
    output_viewport_ndc_buffer_->push_back(
        viewport_transform_shader_->TransformNDC(
            *coordinate_itr, input_pipeline_settings_->viewport_position(),
            input_pipeline_settings_->screen_width(),
            input_pipeline_settings_->screen_height(),
            input_pipeline_settings_->depth_range_min(),
            input_pipeline_settings_->depth_range_max()));
  }
  // result : NDC in output_transformed_coordinate_buffer

  // result : screen coordinate that has depth in clip space
  // output_ndc_buffer_
}
}  // namespace ho_renderer