#include "graphics/resource/include/graphic_resource_manager.h"

#include <memory>
#include <string>
#include <unordered_map>

#include "tools/include/debug.h"

namespace ho_renderer {

GraphicResourceManager::GraphicResourceManager() = default;
GraphicResourceManager::~GraphicResourceManager() = default;

bool GraphicResourceManager::AddModel(std::unique_ptr<Model> model) {
  ASSERT_MSG(model != nullptr,
             "GraphicResourceManager::AddModel Error: model must not be null");
  std::uint32_t index = models_.size();
  const std::string& name = model->name();
  ASSERT_MSG(models_map_.find(name) == models_map_.end(),
             "GraphicResourceManager::AddModel Error: model with same name "
             "already exists");
  if (models_map_.find(name) == models_map_.end()) {
    models_.push_back(std::move(model));
    models_map_.insert({name, index});
    return true;
  }
  return false;
}

bool GraphicResourceManager::DeleteModel(std::uint32_t index) {
  ASSERT_MSG(index >= 0,
             "GraphicResourceManager::DeleteModel Error: index out of range");
  if (index >= models_.size()) {
    return false;
  }
  models_.erase(models_.begin() + index);
  return true;
}
bool GraphicResourceManager::DeleteModel(const std::string& name) {
  auto found = models_map_.find(name);
  ASSERT_MSG(found != models_map_.end(),
             "GraphicResourceManager::DeleteModel Error : model with given "
             "name does not exist");
  if (found == models_map_.end()) {
    return false;
  }
  return DeleteModel(found->second);
}

Model* GraphicResourceManager::GetModel(std::uint32_t index) const {
  ASSERT_MSG(index >= 0,
             "GraphicResourceManager::DeleteModel Error: index out of range");
  if (index >= models_.size()) {
    return nullptr;
  }
  return models_[index].get();
}
Model* GraphicResourceManager::GetModel(const std::string& name) const {
  auto found = models_map_.find(name);
  ASSERT_MSG(found != models_map_.end(),
             "GraphicResourceManager::GetModel Error : model with given "
             "name does not exist");
  if (found == models_map_.end()) {
    return nullptr;
  }
  return models_[found->second].get();
}
}  // namespace ho_renderer