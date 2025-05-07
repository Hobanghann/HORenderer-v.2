#include "graphics/resource/include/graphic_resource_manager.h"

#include <memory>
#include <string>
#include <unordered_map>

namespace ho_renderer {

GraphicResourceManager::GraphicResourceManager() = default;
GraphicResourceManager::~GraphicResourceManager() = default;

bool GraphicResourceManager::AddModel(std::unique_ptr<Model> model) {
  std::uint32_t index = models_.size();
  const std::string& name = model->name();
  if (models_map_.find(name) == models_map_.end()) {
    models_.push_back(std::move(model));
    models_map_.insert({name, index});
    return true;
  }
  return false;
}

bool GraphicResourceManager::DeleteModel(std::uint32_t index) {
  if (index >= models_.size()) {
    return false;
  }
  models_.erase(models_.begin() + index);
  return true;
}
bool GraphicResourceManager::DeleteModel(const std::string& name) {
  if (models_map_.erase(name)) {
    return true;
  }
  return false;
}

Model* GraphicResourceManager::GetModel(std::uint32_t index) const {
  if (index >= models_.size()) {
    return nullptr;
  }
  return models_[index].get();
}
Model* GraphicResourceManager::GetModel(const std::string& name) const {
  auto found = models_map_.find(name);
  if (found == models_map_.end()) {
    return nullptr;
  }
  return models_[found->second].get();
}
}  // namespace ho_renderer