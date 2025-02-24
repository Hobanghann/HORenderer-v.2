#ifndef _HORENDERER_ENGINE_RENDERER_H_
#define _HORENDERER_ENGINE_RENDERER_H_

#include <cstdint>
#include <memory>
#include <vector>

#include "asset/include/scene.h"
#include "engine/include/mesh_manager.h"
#include "engine/include/renderer_settings.h"
#include "engine/include/scene_manager.h"
#include "engine/include/timer.h"
#include "rendering_pipeline/pipeline/include/rendering_pipeline.h"

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
  SceneManager scene_manager_;
  MeshManager mesh_manager_;
  RenderingPipeline rendering_pipeline_;
  RendererSettings renderer_settings_;
  InputManager input_manager_;
  Timer timer_;
  long long total_frame_count_;
  long long delta_time_;
  long long FPS_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_ENGINE_RENDERER_H_