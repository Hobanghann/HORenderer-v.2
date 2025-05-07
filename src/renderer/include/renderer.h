#ifndef _HORENDERER_RENDERER_RENDERER_H_
#define _HORENDERER_RENDERER_RENDERER_H_

#include <cstdint>
#include <memory>
#include <vector>
#include <filesystem>

#include "core/input/include/input_manager.h"
#include "core/time/include/timer.h"
#include "graphics/rendering_pipeline/system/include/rendering_pipeline.h"
#include "graphics/resource/include/graphic_resource_manager.h"
#include "graphics/resource/include/model_loader.h"
#include "renderer/include/renderer_settings.h"
#include "scene/system/include/scene.h"
#include "scene/system/include/scene_manager.h"

namespace ho_renderer {
class Renderer {
 public:
  Renderer(const int screen_width, const int screen_height);
  Renderer(const Renderer&) = delete;
  Renderer& operator=(const Renderer&) = delete;
  ~Renderer();

  int Initialize();
  int PreUpdate();
  int Update();
  int PostUpdate();
  int Render();
  int Quit();

  // this method is used for receiving inputs from window
  InputManager& GetInputManager();

  void InjectExternalColorBuffer(std::uint32_t* color_buffer);
  void InjectExternalDepthBuffer(float* depth_buffer);

  long long GetFPS();

 private:
  int LoadModels();
  int CreateScene();
  int CreateCameraObjects();
  int CreateGameObjects();
  int CreateLights();
  int EnrollInputListener();

  SceneManager scene_manager_;
  GraphicResourceManager resource_manager_;
  RenderingPipeline rendering_pipeline_;
  RendererSettings renderer_settings_;
  InputManager input_manager_;
  Timer timer_;
  long long total_frame_count_;
  long long delta_time_;
  long long FPS_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_RENDERER_RENDERER_H_