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
VertexPostProcessing& VertexPostProcessing::SetInputProjectionTransform(
    const AffineTransform* projection_transform) {
  input_projection_transform_ = projection_transform;
  return *this;
}
VertexPostProcessing& VertexPostProcessing::SetInputPrimitiveColorBuffer(
    std::vector<uint32_t>* primitive_color_buffer) {
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
  input_projection_transform_ = nullptr;
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
std::vector<Vector3>*
VertexPostProcessing::GetOutputTransformedCoordinateBuffer() {
  if (output_transformed_coordinate_buffer_ == nullptr) {
#ifdef DEBUG
    DEBUG_MSG("output_transformed_coordinate_buffer_ is null.")
    assert(false);
#endif
  }
  return output_transformed_coordinate_buffer_;
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
  output_transformed_coordinate_buffer_ = nullptr;
  output_render_object_states_ = nullptr;
  return *this;
}

void VertexPostProcessing::Process() {
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
  output_render_object_states_ = ResourcesManager::AllocateRenderObjectState();
  switch (input_pipeline_settings_->primitive_type()) {
    // If primitive type is point or line, culling is performed after primitive
    // assembly.
    // because object don't have bounding volume
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
  if (input_pipeline_settings_ == nullptr) {
#ifdef DEBUG
    DEBUG_MSG("input_pipeline_settings_ is null.")
    assert(false);
#endif
  }
  if (input_index_buffer_ == nullptr) {
#ifdef DEBUG
    DEBUG_MSG("input_index_buffer_ is null.")
    assert(false);
#endif
  }
  if (input_primitive_color_buffer_ == nullptr) {
#ifdef DEBUG
    DEBUG_MSG("input_primitive_color_buffer_ is null.")
    assert(false);
#endif
  }
  if (input_pipeline_settings_->rendering_mode() !=
      RenderingMode::kTEXTURE_MAPPING) {
    switch (input_pipeline_settings_->primitive_type()) {
      case kPOINT:
        output_primitive_buffer_ =
            primitive_assembly_shader_->AssembleFilledPoint(
                *input_index_buffer_, *input_primitive_color_buffer_);
        break;
      case kLINE:
        output_primitive_buffer_ =
            primitive_assembly_shader_->AssembleFilledLine(
                *input_index_buffer_, *input_primitive_color_buffer_);
        break;
      case kTRIANGLE:
        output_primitive_buffer_ =
            primitive_assembly_shader_->AssembleFilledTriangle(
                *input_index_buffer_, *input_primitive_color_buffer_);
        break;
    }
  } else {
    switch (input_pipeline_settings_->primitive_type()) {
      case kPOINT:
        output_primitive_buffer_ =
            primitive_assembly_shader_->AssemblePoint(*input_index_buffer_);
        break;
      case kLINE:
        output_primitive_buffer_ =
            primitive_assembly_shader_->AssembleLine(*input_index_buffer_);
        break;
      case kTRIANGLE:
        output_primitive_buffer_ =
            primitive_assembly_shader_->AssembleTriangle(*input_index_buffer_);
        break;
    }
  }
  // result : primitives in output_primitive_buffer

  /*

   /////////////////////////////////////////////////////////////////////
   // Projection transform
   /////////////////////////////////////////////////////////////////////
   if(input_vertex_buffer_ == nullptr) {
#ifdef DEBUG
    DEBUG_MSG("input_vertex_buffer_ is null.")
    assert(false);
#endif
  }
  if(input_projection_transform_ == nullptr) {
  #ifdef DEBUG
    DEBUG_MSG("input_projection_transform_ is null.")
    assert(false);
#endif
  }
   for (auto vertex_itr = input_vertex_buffer_->begin();
        vertex_itr != input_vertex_buffer_->end(); vertex_itr++) {
     *vertex_itr = vertex_shader_->TransformCoordinate(
         *vertex_itr, *input_projection_transform_);
   }
   */
  /////////////////////////////////////////////////////////////////////
  // frustum clipping
  /////////////////////////////////////////////////////////////////////
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
        clipping_shader_->ClipPointAgainstFrustum(*input_vertex_buffer_,
                                                  *output_primitive_buffer_);
        break;
      case kLINE:
        clipping_shader_->ClipLineAgainstFrustum(*input_vertex_buffer_,
                                                 *output_primitive_buffer_);
        break;
      case kTRIANGLE:
        clipping_shader_->ClipTriangleAgainstFrustum(*input_vertex_buffer_,
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
  if (input_vertex_buffer_ == nullptr) {
#ifdef DEBUG
    DEBUG_MSG("input_vertex_buffer_ is null.")
    assert(false);
#endif
  }
  output_transformed_coordinate_buffer_ =
      ResourcesManager::AllocateCoordinateBuffer();
  for (auto vertex_itr = input_vertex_buffer_->cbegin();
       vertex_itr != input_vertex_buffer_->cend(); vertex_itr++) {
    output_transformed_coordinate_buffer_->push_back(
        perspective_divide_shader_->PerspectiveDivide(
            vertex_itr->coordinate()));
  }
  // result : NDC in output_transformed_coordinate_buffer

  /////////////////////////////////////////////////////////////////////
  // back face culling
  /////////////////////////////////////////////////////////////////////
  if (output_primitive_buffer_ == nullptr) {
#ifdef DEBUG
    DEBUG_MSG(
        "output_primitive_buffer_ is null.\n backface culling has to be "
        "excuted after primitive assembly")
    assert(false);
#endif
  }
  if (output_transformed_coordinate_buffer_ == nullptr) {
#ifdef DEBUG
    DEBUG_MSG(
        "output_transformed_coordinate_buffer_ is null.\n backface culling has "
        "to be excuted after perspective divide.")
    assert(false);
#endif
  }
  if (input_pipeline_settings_ == nullptr) {
#ifdef DEBUG
    DEBUG_MSG("input_pipeline_settings_ is null.")
    assert(false);
#endif
  }
  if (input_pipeline_settings_->is_using_backface_culling()) {
    if (input_pipeline_settings_->primitive_type() == kTRIANGLE) {
      face_culling_shader_->BackfaceCullingInClipSpace(
          *output_transformed_coordinate_buffer_, *output_primitive_buffer_);
    }
  }
  /////////////////////////////////////////////////////////////////////
  // viewport transform
  /////////////////////////////////////////////////////////////////////
  if (input_pipeline_settings_ == nullptr) {
#ifdef DEBUG
    DEBUG_MSG("input_pipeline_settings_ is null.")
    assert(false);
#endif
  }
  if (output_transformed_coordinate_buffer_ == nullptr) {
#ifdef DEBUG
    DEBUG_MSG(
        "output_transformed_coordinate_buffer_ is null.\n viewport "
        "transformation has "
        "to be excuted after perspective divide.")
    assert(false);
#endif
  }
  for (auto coordinate_itr = output_transformed_coordinate_buffer_->begin();
       coordinate_itr != output_transformed_coordinate_buffer_->end();
       coordinate_itr++) {
    *coordinate_itr = viewport_transform_shader_->TransformNDC(
        *coordinate_itr, input_pipeline_settings_->viewport_position(),
        input_pipeline_settings_->screen_width(),
        input_pipeline_settings_->screen_height(),
        input_pipeline_settings_->depth_range_min(),
        input_pipeline_settings_->depth_range_max());
  }
  // result : NDC in output_transformed_coordinate_buffer

  // result : screen coordinate that has depth in clip space
  // output_transformed_coordinate_buffer_
}
}  // namespace ho_renderer