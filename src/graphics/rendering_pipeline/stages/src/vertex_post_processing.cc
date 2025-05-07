#include "graphics/rendering_pipeline/stages/include/vertex_post_processing.h"

namespace ho_renderer {
VertexPostProcessing::VertexPostProcessing() = default;
VertexPostProcessing::~VertexPostProcessing() = default;

FrustumCullingResult VertexPostProcessing::CullMesh(
    const Mesh *mesh, const Frustum &frustum,
    const PipelineSettings &settings) const {
  switch (settings.primitive_type()) {
    // If primitive type is point or line, culling is performed after
    // primitive assembly. because object don't have bounding volume
    case kPoint:
      return kIntersect;
      break;
    case kLine:
      return kIntersect;
      break;
    case kTriangle:
      switch (settings.bounding_volume_mode()) {
        case kSphere:
          return frustum_culler_.CullSphereAgainstFrustum(
              mesh->sphere_bounding_volume(), frustum);
          break;
        case kAABB:
          return frustum_culler_.CullAABBAgainstFrustum(
              mesh->aab_bounding_volume(), frustum);
          break;
      }
  }
}

std::vector<std::unique_ptr<Primitive>> *
VertexPostProcessing::AssemblePrimitives(
    std::vector<std::unique_ptr<Primitive>> *output_p_buffer,
    const std::vector<TransformedVertex> *v_buffer,
    const std::vector<std::uint32_t> &index_buffer, const Material *material,
    const PipelineSettings &settings) const {
  switch (settings.primitive_type()) {
    case kPoint:
      primitive_assembler_.AssemblePoint(output_p_buffer, v_buffer,
                                         index_buffer, material);
      break;
    case kLine:
      primitive_assembler_.AssembleLine(output_p_buffer, v_buffer, index_buffer,
                                        material);
      break;
    case kTriangle:
      primitive_assembler_.AssembleTriangle(output_p_buffer, v_buffer,
                                            index_buffer, material,
                                            settings.index_order());
      break;
  }
  return output_p_buffer;
}

void VertexPostProcessing::ClipPrimitives(
    std::vector<std::unique_ptr<Primitive>> *p_buffer,
    std::vector<TransformedVertex> *v_buffer,
    const PipelineSettings &settings) const {
  switch (settings.primitive_type()) {
    case kPoint:
      for (auto itr = p_buffer->begin(); itr != p_buffer->end(); itr++) {
        clipper_.ClipPoint(static_cast<Point *>(itr->get()), v_buffer);
      }
      break;
    case kLine:
      for (auto itr = p_buffer->begin(); itr != p_buffer->end(); itr++) {
        clipper_.ClipLine(static_cast<Line *>(itr->get()), v_buffer);
      }
      break;
    case kTriangle:
      int size = p_buffer->size();
      for (int i = 0; i < size; i++) {
        std::vector<std::unique_ptr<Triangle>> divided_triangles =
            std::move(clipper_.ClipTriangle(
                static_cast<Triangle *>(((*p_buffer)[i]).get()), v_buffer,
                settings.index_order()));
        p_buffer->insert(p_buffer->end(),
                         std::make_move_iterator(divided_triangles.begin()),
                         std::make_move_iterator(divided_triangles.end()));
      }
      break;
  }
}

std::vector<TransformedVertex> *VertexPostProcessing::PerspectiveDivideVertices(
    std::vector<TransformedVertex> *v_buffer) const {
  for (TransformedVertex &vertex : *v_buffer) {
    perspective_divider_.PerspectiveDivide(vertex);
  }
  return v_buffer;
}

void VertexPostProcessing::CullBackfaces(
    std::vector<std::unique_ptr<Primitive>> *triangle_buffer,
    std::vector<TransformedVertex> *v_buffer,
    const PipelineSettings &settings) const {
  if (settings.primitive_type() != kTriangle ||
      !settings.is_using_backface_culling()) {
    return;
  }
  for (auto itr = triangle_buffer->begin(); itr != triangle_buffer->end();
       itr++) {
    face_culler_.BackfaceCulling(static_cast<Triangle *>(itr->get()), v_buffer,
                                 Vector3::kUnitZ, settings.index_order());
  }
}

std::vector<TransformedVertex> *VertexPostProcessing::TransformNDCToViewport(
    std::vector<TransformedVertex> *v_buffer,
    const PipelineSettings &settings) const {
  for (TransformedVertex &vertex : *v_buffer) {
    viewport_transformer_.TransformNDC(
        vertex, Vector2::kZero, settings.viewport_width(),
        settings.viewport_height(), settings.depth_range_min(),
        settings.depth_range_max());
  }
  return v_buffer;
}
}  // namespace ho_renderer