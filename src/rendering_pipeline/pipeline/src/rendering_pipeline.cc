#include "rendering_pipeline/pipeline/include/rendering_pipeline.h"

#include <cstdint>
#include <vector>

#include "app/include/debug.h"
#include "asset/include/camera_object.h"
#include "asset/include/game_object.h"
#include "asset/include/scene.h"
#include "asset/include/vertex.h"
#include "engine/include/srgb.h"
#include "rendering_pipeline/pipeline/include/pipeline_settings.h"
#include "rendering_pipeline/pipeline/include/resources_manager.h"

namespace ho_renderer {
RenderingPipeline::RenderingPipeline(const int screen_width,
                                     const int screen_height,
                                     const Vector2& viewport_position,
                                     const float depth_range_min,
                                     const float depth_range_max)
    : vertex_specification_stage_(
          std::unique_ptr<VertexSpecification>(new VertexSpecification())),
      vertex_processing_stage_(
          std::unique_ptr<VertexProcessing>(new VertexProcessing())),
      vertex_post_processing_stage_(
          std::unique_ptr<VertexPostProcessing>(new VertexPostProcessing())),
      rasterization_stage_(std::unique_ptr<Rasterization>(new Rasterization())),
      fragment_processing_stage_(
          std::unique_ptr<FragmentProcessing>(new FragmentProcessing())),
      per_sample_processing_stage_(
          std::unique_ptr<PerSampleProcessing>(new PerSampleProcessing())) {
  // set initial pipeline settings
  pipeline_settings()
      .set_screen_width(screen_width)
      .set_screen_height(screen_height)
      .set_viewport_position(viewport_position)
      .set_depth_range_min(depth_range_min)
      .set_depth_range_max(depth_range_max)
      .set_background_color(SRGB::GetLinearWhite())
      .set_interpolation_mode(InterpolationMode::kPERSPECTIVE_CORRECT)
      .set_bounding_volume_mode(BoundingVolumeMode::kAABB)
      .set_rendering_mode(RenderingMode::kWIRE_FRAME)
      .set_is_using_backface_culling(true);
  // set initial frame buffer
  frame_buffer().CreateColorBuffer(screen_width, screen_height,
                                   SRGB::GetLinearWhite());
  frame_buffer().CreateDepthBuffer(screen_width, screen_height, depth_range_min,
                                   depth_range_max);
}
RenderingPipeline::~RenderingPipeline() = default;

PipelineSettings& RenderingPipeline::pipeline_settings() {
  return pipeline_settings_;
}
FrameBuffer& RenderingPipeline::frame_buffer() { return frame_buffer_; }

void RenderingPipeline::Run(const Scene& scene) {
  // Reset Frame buffer
  frame_buffer_.ResetBuffers();
  // load transforms
  const CameraObject& main_camera = scene.main_camera();
  AffineTransform view_projection_transform =
      AffineTransform::CreateViewTransform(main_camera)
          .ComposeWith(AffineTransform::CreateProjectionTransform(main_camera));

  for (int i = 0; i < scene.GetGameObjectNum(); i++) {
    const GameObject& game_object = scene.GetGameObject(i);
    AffineTransform modeling_transform =
        AffineTransform::CreateModelingTransform(game_object);
    // compose modeling-view-projection matrix
    AffineTransform modeling_view_projection_transform =
        modeling_transform.GetComposeWith(view_projection_transform);
    // set primitive type as object's primitive type
    pipeline_settings_.set_primitive_type(game_object.mesh().primitive_type());
    /////////////////////////////////////////////////////////////////////
    // vertex specification
    /////////////////////////////////////////////////////////////////////
    // reset inputs
    vertex_specification_stage_->ResetInputs();
    // set inputs
    vertex_specification_stage_->SetInputGameObject(&game_object);
    // excute
    vertex_specification_stage_->ReadBuffer();
    // get outputs
    std::vector<Vertex>* output_vertex_buffer =
        vertex_specification_stage_->GetOutputVertexBuffer();
    std::vector<std::uint32_t>* output_index_buffer =
        vertex_specification_stage_->GetOutputIndexBuffer();
    // reset outputs
    vertex_specification_stage_->ResetOutputs();
    /////////////////////////////////////////////////////////////////////
    // vertex processing
    /////////////////////////////////////////////////////////////////////
    // reset inputs
    vertex_processing_stage_->ResetInputs();
    // set inputs
    vertex_processing_stage_->SetInputVertexBuffer(output_vertex_buffer)
        .SetInputTransform(&modeling_view_projection_transform);
    // excute
    vertex_processing_stage_->Process();
    // get outputs
    output_vertex_buffer = vertex_processing_stage_->GetOutputVertexBuffer();
    // reset outputs
    vertex_processing_stage_->ResetOutputs();
    /////////////////////////////////////////////////////////////////////
    // vertex post-processing
    /////////////////////////////////////////////////////////////////////
    // read object's primitive color
    std::vector<std::uint32_t>* primitive_color_buffer =
        ResourcesManager::AllocateColorBuffer();
    *primitive_color_buffer = game_object.mesh().primitive_color_buffer();
    // construct frustum
    Frustum frustum = Frustum(modeling_view_projection_transform.matrix());
    // reset inputs
    vertex_post_processing_stage_->ResetInputs();
    // set inputs
    vertex_post_processing_stage_->SetInputGameObject(&game_object)
        .SetInputVertexBuffer(output_vertex_buffer)
        .SetInputIndexBuffer(output_index_buffer)
        .SetInputPrimitiveColorBuffer(primitive_color_buffer)
        .SetInputFrustum(&frustum)
        .SetInputPipelineSettings(&pipeline_settings_);
    // excute
    vertex_post_processing_stage_->Process();
    // get outputs
    RenderObjectState* output_render_object_state =
        vertex_post_processing_stage_->GetOutputRenderObjectStates();
    // If object is outside of frustum, quit pipeline immediately
    if (output_render_object_state->object_culling_state() ==
        FrustumCullingResult::kOUTSIDE) {
      continue;
    }
    std::vector<Vector3>* output_transformed_coordinate_buffer =
        vertex_post_processing_stage_->GetOutputTransformedCoordinateBuffer();
    std::vector<Primitive*>* output_primitive_buffer =
        vertex_post_processing_stage_->GetOutputPrimitiveBuffer();
    // reset outputs
    vertex_post_processing_stage_->ResetOutputs();
    for (auto primitive_itr = output_primitive_buffer->begin();
         primitive_itr != output_primitive_buffer->end(); primitive_itr++) {
      /////////////////////////////////////////////////////////////////////
      // rasterization
      /////////////////////////////////////////////////////////////////////
      // if primitive is outof frustum, skip
      if ((*primitive_itr)->is_outof_frustum()) {
        continue;
      }
      // if triangle is backface, skip
      if (pipeline_settings_.primitive_type() == PrimitiveType::kTRIANGLE) {
        if (static_cast<Triangle*>(*primitive_itr)->is_backface()) {
          continue;
        }
      }
      // reset inputs
      rasterization_stage_->ResetInputs();
      // set inputs
      rasterization_stage_->SetInputPrimitive(*primitive_itr)
          .SetInputVertexBuffer(output_vertex_buffer)
          .SetInputTransformedCoordinateBuffer(
              output_transformed_coordinate_buffer)
          .SetInputPipelineSettings(&pipeline_settings_);
      // excute
      rasterization_stage_->Rasterize();
      // get outputs
      std::vector<Fragment>* output_fragment_buffer =
          rasterization_stage_->GetOutputFragmentBuffer();
      // reset outputs
      rasterization_stage_->ResetOutputs();
      // degenerate case
      if (output_fragment_buffer == nullptr) {
        continue;
      }
      for (auto fragment_itr = output_fragment_buffer->begin();
           fragment_itr != output_fragment_buffer->end(); fragment_itr++) {
        /////////////////////////////////////////////////////////////////////
        // fragment processing
        /////////////////////////////////////////////////////////////////////
        // reset inputs
        fragment_processing_stage_->ResetInputs();
        // set inputs
        fragment_processing_stage_->SetInputFragment(&*fragment_itr)
            .SetInputPipelineSettings(&pipeline_settings_);
        // excute
        fragment_processing_stage_->Process();
        // get outputs
        Fragment* output_fragment =
            fragment_processing_stage_->GetOutputFragment();
        // reset outputs
        fragment_processing_stage_->ResetOutputs();
        /////////////////////////////////////////////////////////////////////
        // per-sample processing
        /////////////////////////////////////////////////////////////////////
        // reset inputs
        per_sample_processing_stage_->ResetInputs();
        // set input
        per_sample_processing_stage_->SetInputFragment(output_fragment)
            .SetInputFrameBuffer(&frame_buffer_)
            .SetInputPipelineSettings(&pipeline_settings_);
        // excute
        per_sample_processing_stage_->Process();
        // frame buffer wrote
      }
      // deallocate fragment_buffer
      ResourcesManager::DeallocateFragmentBuffer();
    }
    // deallocate all
    ResourcesManager::DeallocateAll();
  }
  // buffer swap
}
}  // namespace ho_renderer
