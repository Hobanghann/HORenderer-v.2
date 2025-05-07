#ifndef _HORENDERER_GRAPHIC_RESOURCE_MANAGER_H_
#define _HORENDERER_GRAPHIC_RESOURCE_MANAGER_H_

#include <memory>
#include <string>
#include <unordered_map>

#include "graphics/resource/include/model.h"

namespace ho_renderer {
class GraphicResourceManager {
 public:
  GraphicResourceManager();
  GraphicResourceManager(const GraphicResourceManager&) = delete;
  GraphicResourceManager& operator=(const GraphicResourceManager&) = delete;
  ~GraphicResourceManager();

  bool AddModel(std::unique_ptr<Model> model);

  bool DeleteModel(std::uint32_t index);
  bool DeleteModel(const std::string& name);

  Model* GetModel(std::uint32_t index) const;
  Model* GetModel(const std::string& name) const;

 private:
  std::vector<std::unique_ptr<Model>> models_;
  std::unordered_map<std::string, std::uint32_t> models_map_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_GRAPHIC_RESOURCE_MANAGER_H_