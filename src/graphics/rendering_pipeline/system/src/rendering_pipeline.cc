#include "graphics/rendering_pipeline/system/include/rendering_pipeline.h"

#include <cstdint>
#include <queue>
#include <vector>

#include "core/math/include/quaternion_transform.h"
#include "graphics/color/include/srgb.h"
#include "graphics/rendering_pipeline/pipeline_objects/include/transformed_vertex.h"
#include "graphics/rendering_pipeline/system/include/pipeline_resources_manager.h"
#include "graphics/rendering_pipeline/system/include/pipeline_settings.h"
#include "graphics/resource/include/vertex.h"
#include "scene/camera/include/camera.h"
#include "scene/object/include/game_object.h"
#include "scene/system/include/scene.h"

namespace ho_renderer {
RenderingPipeline::RenderingPipeline(const int viewport_width,
                                     const int viewport_height)
    : pipeline_settings_(viewport_width, viewport_height) {
  // set initial frame buffer
  frame_buffer().CreateColorBuffer(
      viewport_width, viewport_height,
      pipeline_settings_.background_color().ToBGRA32());
  frame_buffer().CreateDepthBuffer(viewport_width, viewport_height,
                                   pipeline_settings_.depth_range_min(),
                                   pipeline_settings_.depth_range_max());
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
  const Camera& camera = *scene->GetMainCamera();
  AffineTransform v_transform = camera.GetViewTransform();
  AffineTransform p_transform = camera.GetProjectionTransform();
  AffineTransform vp_transform = v_transform.GetComposeWith(p_transform);

  std::vector<PointLight*> p_lights;
  for (int i = 0; i < scene->GetPointLightsCount(); i++) {
    p_lights.push_back(scene->GetPointLight(i));
  }
  /////////////////////////////////////////////////////////////////////
  // pre-render
  /////////////////////////////////////////////////////////////////////
  pre_render_.ResetFrameBuffer(frame_buffer_);
  pre_render_.TransformDirectionalLightToView(scene->GetMainDirectionalLight(),
                                              v_transform);
  for (auto itr = p_lights.begin(); itr != p_lights.end(); itr++) {
    pre_render_.TransformPointLightToView(*itr, v_transform);
  }

  /////////////////////////////////////////////////////////////////////
  // Start rendering
  /////////////////////////////////////////////////////////////////////
  for (int i = 0; i < scene->GetGameObjectsCount(); i++) {
    const GameObject& game_object = *scene->GetGameObject(i);
    // construct transform
    AffineTransform object_m_transform = game_object.GetModelingTransform();

    const Model* model = game_object.model();
    std::queue<ModelNode*> node_q;
    node_q.push(model->root());

    while (!node_q.empty()) {
      ModelNode* node = node_q.front();
      node_q.pop();
      for (int i = 0; i < node->NumChilds(); i++) {
        node_q.push(node->GetChild(i));
      }

      AffineTransform acc_m_transform =
          (node->parent() == nullptr)
              ? object_m_transform
              : node->parent()->modeling_transform_cache();

      AffineTransform node_m_transform = node->GetModelingTransform();

      AffineTransform m_transform =
          acc_m_transform.GetComposeWith(node_m_transform);
      node->set_modeling_transform_cache(m_transform);
      AffineTransform mvp_transform = m_transform.GetComposeWith(vp_transform);
      for (int i = 0; i < node->NumMeshes(); i++) {
        const Mesh* mesh = node->GetMesh(i);

        /////////////////////////////////////////////////////////////////////
        // vertex specification
        /////////////////////////////////////////////////////////////////////
        auto v_buffer = resource_manager_.GetClearVertexBuffer();
        v_buffer = vertex_specification_.ReadVertices(v_buffer, mesh);
        auto i_buffer = vertex_specification_.ReadIndices(mesh);
        /////////////////////////////////////////////////////////////////////
        // vertex processing
        /////////////////////////////////////////////////////////////////////
        vertex_processing_.TransformVertices(v_buffer,m_transform,
                                             v_transform, p_transform);
        /////////////////////////////////////////////////////////////////////
        // vertex post-processing
        /////////////////////////////////////////////////////////////////////
        // construct frustum
        Frustum frustum = Frustum(mvp_transform.matrix());
        // If object is outside of frustum, quit pipeline immediately
        if (vertex_post_processing_.CullMesh(node->GetMesh(0), frustum,
                                             pipeline_settings_) ==
            FrustumCullingResult::kOutside) {
          continue;
        }
        auto p_buffer = resource_manager_.GetClearPrimitiveBuffer();
        p_buffer = vertex_post_processing_.AssemblePrimitives(
            p_buffer, v_buffer, i_buffer, mesh->material(), pipeline_settings_);
        vertex_post_processing_.ClipPrimitives(p_buffer, v_buffer,
                                               pipeline_settings_);
        v_buffer = vertex_post_processing_.PerspectiveDivideVertices(v_buffer);
        if (pipeline_settings_.primitive_type() == kTriangle) {
          vertex_post_processing_.CullBackfaces(p_buffer, v_buffer,
                                                pipeline_settings_);
        }
        vertex_post_processing_.TransformNDCToViewport(v_buffer,
                                                       pipeline_settings_);

        for (auto p_itr = p_buffer->begin(); p_itr != p_buffer->end();
             p_itr++) {
          /////////////////////////////////////////////////////////////////////
          // rasterization
          /////////////////////////////////////////////////////////////////////
          // if primitive is outof frustum, skip
          if ((*p_itr)->is_outof_frustum()) {
            continue;
          }
          // if triangle is backface, skip
          if (pipeline_settings_.primitive_type() == PrimitiveType::kTriangle) {
            if (static_cast<Triangle*>(p_itr->get())->is_backface()) {
              continue;
            }
          }
          auto f_buffer = resource_manager_.GetClearFragmentBuffer();
          f_buffer =
              rasterization_.Rasterize(f_buffer, p_itr->get(), v_buffer,
                                       frame_buffer_, pipeline_settings_);
          // degenerate case
          if (f_buffer->empty()) {
            continue;
          }
          for (auto f_itr = f_buffer->begin(); f_itr != f_buffer->end();
               f_itr++) {
            /////////////////////////////////////////////////////////////////////
            // fragment processing
            /////////////////////////////////////////////////////////////////////
            fragment_processing_.Shading(*f_itr, scene->GetMainAmbientLight(),
                                         scene->GetMainDirectionalLight(),
                                         p_lights, pipeline_settings_);
            /////////////////////////////////////////////////////////////////////
            // per-sample processing
            /////////////////////////////////////////////////////////////////////
            per_sample_processing_.ScissorTesting(
                *f_itr, pipeline_settings_.viewport_width(),
                pipeline_settings_.viewport_height());
            per_sample_processing_.WriteFragment(*f_itr, frame_buffer_);
          }
        }
      }
    }
  }
}
}  // namespace ho_renderer
