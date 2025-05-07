#ifndef _HORENDERER_MODEL_NODE_H_
#define _HORENDERER_MODEL_NODE_H_

#include <memory>
#include <string>
#include <vector>

#include "core/math/include/affine_transform.h"
#include "graphics/resource/include/mesh.h"
#include "scene/object/include/transform.h"

namespace ho_renderer {
class Model;
class ModelLoader;
class ModelNode {
  friend ModelLoader;

 public:
  ModelNode() = delete;
  ModelNode(const ModelNode& node) = delete;
  ModelNode(Model* owner, const std::string& name,
            std::vector<std::uint32_t>& mesh_indices,
            std::vector<std::unique_ptr<ModelNode>> childs,
            const Transform& transform);
  ModelNode(Model* owner, const std::string& name,
            std::vector<std::uint32_t>& mesh_indices, ModelNode* parent,
            std::vector<std::unique_ptr<ModelNode>> childs,
            const Transform& transform);
  ModelNode& operator=(const ModelNode&) = delete;
  ~ModelNode();

  const std::string& name() const;
  const ModelNode* parent() const;
  const Transform& transform() const;
  const AffineTransform& modeling_transform_cache() const;

  ModelNode& set_modeling_transform_cache(const AffineTransform& m_transform);

  const Mesh* GetMesh(std::uint32_t index) const;
  ModelNode* GetChild(std::uint32_t index) const;

  std::uint32_t NumMeshes() const;
  std::uint32_t NumChilds() const;

  AffineTransform GetModelingTransform() const;

 private:
  ModelNode& set_parent(ModelNode* parent);

  std::string name_;
  std::vector<std::uint32_t> mesh_indices_;
  ModelNode* parent_;
  std::vector<std::unique_ptr<ModelNode>> childs_;
  Transform transform_;
  Model* owner_;
  AffineTransform modeling_taransform_cache_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_MODEL_NODE_H_