#include "rendering_pipeline/pipeline/include/rendering_pipeline.h"

#include <cstdint>
#include <vector>

#include "app/include/debug.h"
#include "asset/include/camera_object.h"
#include "asset/include/game_object.h"
#include "asset/include/vertex.h"
#include "engine/color/include/srgb.h"
#include "engine/scene/include/scene.h"
#include "math/include/quaternion_transform.h"
#include "rendering_pipeline/pipeline/include/pipeline_settings.h"
#include "rendering_pipeline/pipeline/include/resources_manager.h"

namespace ho_renderer {
RenderingPipeline::RenderingPipeline(const int screen_width,
                                     const int screen_height,
                                     const Vector2& viewport_position,
                                     const float depth_range_min,
                                     const float depth_range_max)
    : pre_render_stage_(new PreRenderStage()),
      vertex_specification_stage_(
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
      .set_background_color(LinearRGB::kWHITE)
      .set_interpolation_mode(InterpolationMode::kAFFINE)
      .set_bounding_volume_mode(BoundingVolumeMode::kSPHERE)
      .set_rendering_mode(RenderingMode::kFILL)
      .set_is_using_backface_culling(true)
      .set_is_using_diffuse_lighting(true)
      .set_is_using_specular_lighting(true);
  // set initial frame buffer
  frame_buffer().CreateColorBuffer(
      screen_width, screen_height,
      pipeline_settings_.background_color().ToARGB32());
  frame_buffer().CreateDepthBuffer(screen_width, screen_height, depth_range_min,
                                   depth_range_max);
}
RenderingPipeline::~RenderingPipeline() = default;

PipelineSettings& RenderingPipeline::pipeline_settings() {
  return pipeline_settings_;
}
FrameBuffer& RenderingPipeline::frame_buffer() { return frame_buffer_; }

void RenderingPipeline::Run(const Scene* scene) {
  if (scene == nullptr) {
    return;
  }
  // construct transform
  const CameraObject& camera_object = *scene->GetMainCamera();
  AffineTransform view_transform =
      AffineTransform::CreateViewTransform(camera_object);
  AffineTransform projection_transform =
      AffineTransform::CreateProjectionTransform(camera_object);
  AffineTransform view_projection_transform =
      view_transform.GetComposeWith(projection_transform);
  /////////////////////////////////////////////////////////////////////
  // pre-render
  /////////////////////////////////////////////////////////////////////
  // reset inputs
  pre_render_stage_->ResetInputs();
  // set inputs
  pre_render_stage_->SetInputFrameBuffer(&frame_buffer_);
  pre_render_stage_->SetInputTransform(&view_transform);
  if (scene->GetAmbientLightNum() != 0) {
    pre_render_stage_->SetInputAmbientLight(scene->GetMainAmbientLight());
  }
  if (scene->GetDirectionalLightNum() != 0) {
    pre_render_stage_->SetInputDirectionalLight(
        scene->GetMainDirectionalLight());
  }
  if (scene->GetPointLightNum() != 0) {
    for (int i = 0; i < scene->GetPointLightNum(); i++) {
      pre_render_stage_->SetInputPointLight(scene->GetPointLight(i));
    }
  }
  // excute
  pre_render_stage_->PreRender();

  for (int i = 0; i < scene->GetGameObjectNum(); i++) {
    const GameObject& game_object = *scene->GetGameObject(i);
    // construct transform
    AffineTransform modeling_transform =
        AffineTransform::CreateModelingTransform(game_object);
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
    std::vector<Vertex>* vertex_buffer =
        vertex_specification_stage_->GetOutputVertexBuffer();
    std::vector<std::uint32_t>* index_buffer =
        vertex_specification_stage_->GetOutputIndexBuffer();
    // reset outputs
    vertex_specification_stage_->ResetOutputs();
    /////////////////////////////////////////////////////////////////////
    // vertex processing
    /////////////////////////////////////////////////////////////////////
    // reset inputs
    vertex_processing_stage_->ResetInputs();
    // set inputs
    vertex_processing_stage_->SetInputVertexBuffer(vertex_buffer)
        .SetInputModelingTransform(&modeling_transform)
        .SetInputViewTransform(&view_transform)
        .SetInputProjectionTransform(&projection_transform);
    // excute
    vertex_processing_stage_->Process();
    // get outputs
    vertex_buffer = vertex_processing_stage_->GetOutputVertexBuffer();
    std::vector<Vector3>* view_coordinate_buffer =
        vertex_processing_stage_->GetOutputViewCoordinateBuffer();
    // reset outputs
    vertex_processing_stage_->ResetOutputs();
    /////////////////////////////////////////////////////////////////////
    // vertex post-processing
    /////////////////////////////////////////////////////////////////////
    // read object's primitive color
    std::vector<LinearRGB>* primitive_color_buffer =
        ResourcesManager::GetClearColorBuffer();
    *primitive_color_buffer = game_object.mesh().primitive_color_buffer();
    // construct frustum
    Frustum frustum = Frustum(modeling_view_projection_transform.matrix());
    // reset inputs
    vertex_post_processing_stage_->ResetInputs();
    // set inputs
    vertex_post_processing_stage_->SetInputGameObject(&game_object)
        .SetInputVertexBuffer(vertex_buffer)
        .SetInputIndexBuffer(index_buffer)
        .SetInputViewCoordinateBuffer(view_coordinate_buffer)
        .SetInputPrimitiveColorBuffer(primitive_color_buffer)
        .SetInputFrustum(&frustum)
        .SetInputPipelineSettings(&pipeline_settings_);
    // excute
    vertex_post_processing_stage_->Process();
    // get outputs
    RenderObjectState* render_object_state =
        vertex_post_processing_stage_->GetOutputRenderObjectStates();
    // If object is outside of frustum, quit pipeline immediately
    if (render_object_state->object_culling_state() ==
        FrustumCullingResult::kOUTSIDE) {
      continue;
    }
    std::vector<Vector3>* ndc_buffer =
        vertex_post_processing_stage_->GetOutputNDCBuffer();
    std::vector<Vector3>* viewport_ndc_buffer =
        vertex_post_processing_stage_->GetOutputViewportNDCBuffer();
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
          .SetInputVertexBuffer(vertex_buffer)
          .SetInputViewCoordinateBuffer(view_coordinate_buffer)
          .SetInputNDCBuffer(ndc_buffer)
          .SetInputViewportNDCBuffer(viewport_ndc_buffer)
          .SetInputPipelineSettings(&pipeline_settings_)
          .SetInputFrameBuffer(&frame_buffer_);
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
            .SetInputPipelineSettings(&pipeline_settings_)
            .SetInputAmbientLight(scene->GetMainAmbientLight())
            .SetInputPointLight(scene->GetPointLight(0));
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
    }
  }
}
}  // namespace ho_renderer
