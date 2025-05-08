#include "graphics/resource/include/model_node.h"

#include "graphics/resource/include/model.h"
#include "tools/include/debug.h"

namespace ho_renderer {
ModelNode::ModelNode(Model* owner, const std::string& name,
                     std::vector<std::uint32_t>& mesh_indices,
                     std::vector<std::unique_ptr<ModelNode>> childs,
                     const Transform& transform)
    : name_(name),
      mesh_indices_(mesh_indices),
      parent_(nullptr),
      childs_(std::move(childs)),
      owner_(owner),
      transform_(transform) {}
ModelNode::ModelNode(Model* owner, const std::string& name,
                     std::vector<std::uint32_t>& mesh_indices,
                     ModelNode* parent,
                     std::vector<std::unique_ptr<ModelNode>> childs,
                     const Transform& transform)
    : name_(name),
      mesh_indices_(mesh_indices),
      parent_(parent),
      childs_(std::move(childs)),
      owner_(owner),
      transform_(transform) {}
ModelNode::~ModelNode() = default;

const std::string& ModelNode::name() const { return name_; }
const ModelNode* ModelNode::parent() const { return parent_; }
const Transform& ModelNode::transform() const { return transform_; }
const AffineTransform& ModelNode::modeling_transform_cache() const {
  return modeling_taransform_cache_;
}

ModelNode& ModelNode::set_modeling_transform_cache(
    const AffineTransform& m_transform) {
  modeling_taransform_cache_ = m_transform;
  return *this;
}
const Mesh* ModelNode::GetMesh(std::uint32_t index) const {
  ASSERT_MSG(
      index < mesh_indices_.size(),
      "ModelNode::GetMesh Error: index out of range (invalid mesh index)");
  ASSERT_MSG(owner_ != nullptr,
             "ModelNode::GetMesh Error: owner model is null");
  if (index >= mesh_indices_.size() || owner_ == nullptr) {
    return nullptr;
  }
  return owner_->GetMesh(mesh_indices_[index]);
}
ModelNode* ModelNode::GetChild(std::uint32_t index) const {
  ASSERT_MSG(
      index < childs_.size(),
      "ModelNode::GetChild Error: index out of range (invalid child index)");
  if (index >= childs_.size()) {
    return nullptr;
  }
  return childs_[index].get();
}

std::uint32_t ModelNode::NumMeshes() const { return mesh_indices_.size(); }
std::uint32_t ModelNode::NumChilds() const { return childs_.size(); }

AffineTransform ModelNode::GetModelingTransform() const {
  AffineTransform scale_transform =
      LinearTransform::CreateScaleTransform(transform_.world_scale())
          .ToAffineTransform();
  AffineTransform rotation_transform =
      LinearTransform::CreateRotationTransform(transform_.world_right(),
                                               transform_.world_up(),
                                               transform_.world_forward())
          .ToAffineTransform();
  AffineTransform translation_transform =
      AffineTransform::CreateTranslationTransform(transform_.world_coord());
  return scale_transform.ComposeWith(rotation_transform)
      .ComposeWith(translation_transform);
}

ModelNode& ModelNode::set_parent(ModelNode* parent) {
  parent_ = parent;
  return *this;
}
}  // namespace ho_renderer