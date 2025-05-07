#include "renderer/include/renderer.h"

#include <memory>
#include <random>
#include <string>

#include "core/math/include/math_utils.h"
#include "graphics/color/include/linear_rgb.h"
#include "scene/camera/include/camera_builder.h"
#include "scene/light/include/ambient_light.h"
#include "scene/light/include/directional_light.h"
#include "scene/light/include/point_light.h"
#include "scene/object/include/game_object_builder.h"

namespace ho_renderer {

Renderer::Renderer(const int screen_width, const int screen_height)
    : total_frame_count_(0),
      delta_time_(0),
      FPS_(0),
      renderer_settings_(screen_width, screen_height),
      rendering_pipeline_(screen_width, screen_height) {}
Renderer::~Renderer() = default;

int Renderer::Initialize() {
  LoadModels();
  CreateScene();
  CreateCameraObjects();
  CreateGameObjects();
  CreateLights();
  EnrollInputListener();
  timer_.SetStartTime();
  return 0;
}

int Renderer::PreUpdate() {
  timer_.SetLatestFrameStartTime();
  return 0;
}

int Renderer::Update() {
  GetInputManager().HandleInputs(delta_time_ / 1000.f);
  return 0;
}
int Renderer::PostUpdate() {
  total_frame_count_++;
  switch (renderer_settings_.frame_rate_mode()) {
    case k30:
      delta_time_ = timer_.ClampMilliDeltaTime(33, 50);
      break;
    case k60:
      delta_time_ = timer_.ClampMilliDeltaTime(16, 50);
      break;
    case kVARIABLE:
      delta_time_ = timer_.ClampMilliDeltaTime(10, 50);
      break;
  }
  FPS_ = 1000.f / delta_time_;
  return 0;
}
int Renderer::Render() {
  // render current main scene in color buffer
  rendering_pipeline_.Run(scene_manager_.GetMainScene());
  return 0;
}
int Renderer::Quit() { return 0; }

InputManager& Renderer::GetInputManager() { return input_manager_; }

void Renderer::InjectExternalColorBuffer(std::uint32_t* color_buffer) {
  rendering_pipeline_.frame_buffer().GetColorBuffer()->ImportExternalBuffer(
      std::unique_ptr<std::uint32_t[]>(color_buffer));
}
void Renderer::InjectExternalDepthBuffer(float* depth_buffer) {
  rendering_pipeline_.frame_buffer().GetDepthBuffer()->ImportExternalBuffer(
      std::unique_ptr<float[]>(depth_buffer));
}

long long Renderer::GetFPS() { return FPS_; }

int Renderer::LoadModels() {
  std::unique_ptr<Model> model;
  /* std::unique_ptr<Model> sphere =
      std::move(ModelLoader().Load("Sphere", "./resource/Sphere/sphere.obj"));
  if (sphere == nullptr) {
    // exception : model not loaded
    return 1;
  }
  resource_manager_.AddModel(std::move(sphere));
  std::unique_ptr<Model> cube =
      std::move(ModelLoader().Load("Cube", "./resource/Cube/cube.obj"));
  if (cube == nullptr) {
    return 1;
  }
  resource_manager_.AddModel(std::move(cube));
  std::unique_ptr<Model> triangle =
      std::move(ModelLoader().Load("Triangle", "./resource/Triangle/triangle.obj"));
  if (triangle == nullptr) {
    return 1;
  }
  resource_manager_.AddModel(std::move(triangle));
  std::unique_ptr<Model> cone =
      std::move(ModelLoader().Load("Cone", "./resource/Cone/cone.obj"));
  if (cone == nullptr) {
    return 1;
  }
  resource_manager_.AddModel(std::move(cone));*/
  model =
      std::move(ModelLoader().Load("Nier2B", "./resource/Nier2B/Nier2B.obj"));
  if (model == nullptr) {
    // exception : model not loaded
    return 1;
  }
  resource_manager_.AddModel(std::move(model));
   model =
      std::move(ModelLoader().Load("Mug", "./resource/Mug/Mug.obj"));
  if (model == nullptr) {
    // exception : model not loaded
    return 1;
  }
  resource_manager_.AddModel(std::move(model));
  model = std::move(ModelLoader().Load("Dummy", "./resource/Dummy-low/Dummy-low.obj"));
  if (model == nullptr) {
    // exception : model not loaded
    return 1;
  }
  resource_manager_.AddModel(std::move(model));
  return 0;
}

int Renderer::CreateScene() {
  scene_manager_.AddScene(std::make_unique<Scene>("Main Scene"));
  scene_manager_.SetMainScene("Main Scene");
  return 0;
}
int Renderer::CreateCameraObjects() {
  scene_manager_.GetMainScene()->AddCamera(
      CameraBuilder()
          .set_name("Main Camera")
          .set_viewport_width(renderer_settings_.screen_width())
          .set_viewport_height(renderer_settings_.screen_height())
          // Since the view space is defined in a right-handed coord system,
          // the default local axis is the camera's local axis rotated by 180
          // degrees around the yaw axis.
          .set_world_coord(Vector3(0.f, 200.f, 500.f))
          .set_world_forward(-Vector3::kUnitZ)
          .set_world_right(-Vector3::kUnitX)
          .set_world_up(Vector3::kUnitY)
          .set_fov(MathUtils::kPi * 0.38f)
          .set_near_distance(5.5f)
          .set_far_distance(5000.f)
          .set_rotate_velocity(MathUtils::kPi * 0.01f)
          .set_move_velocity(80.f)
          .Build());
  scene_manager_.GetMainScene()->SetMainCamera("Main Camera");
  scene_manager_.GetMainScene()->GetMainCamera()->Active();
  return 0;
}
int Renderer::CreateGameObjects() {
  scene_manager_.GetMainScene()->AddGameObject(
      GameObjectBuilder()
          .set_name("Main Object")
          .set_world_coord({0.f, 0.f, 0.f})
          .set_world_forward(Vector3::kUnitZ)
          .set_world_right(Vector3::kUnitX)
          .set_world_up(Vector3::kUnitY)
          .set_world_scale(100.f)
          // Problem: The static member kBOX is initialized using SRGB's static
          // members. However, the initialization order of static members is
          // undefined. If kBOX is initialized first before SRGB's static
          // members, it will be default-initialized. The initialization order
          // must be explicitly defined so that SRGB's static members are
          // initialized first before kBOX. Solution: Convert SRGB's static
          // members to non-static members.
          .set_model(resource_manager_.GetModel("Mug"))
          .set_rotate_velocity(MathUtils::kPi * 0.01f)
          .Build());
  scene_manager_.GetMainScene()->GetGameObject("Main Object")->Active();
  return 0;
}
int Renderer::CreateLights() {
  scene_manager_.GetMainScene()->AddAmbientLight(std::make_unique<AmbientLight>(
      "Main Ambient Light", LinearRGB::kDARK_GRAY, 1.0f));
  scene_manager_.GetMainScene()->SetMainAmbientLight("Main Ambient Light");

  scene_manager_.GetMainScene()->AddDirectionalLight(
      std::make_unique<DirectionalLight>("Main Directional Light",
                                         LinearRGB::kWHITE, 1.f,
                                         Vector4(1.f, 1.f, -1.f, 0.f)));
  scene_manager_.GetMainScene()->SetMainDirectionalLight(
      "Main Directional Light");

  scene_manager_.GetMainScene()->AddPointLight(std::make_unique<PointLight>(
      "Main Point Light", LinearRGB::kWHITE, 1.f,
      Vector4(0.f, 300.f, -500.f, 1.f), 1.f, 0.007f, 0.0002f));
  return 0;
}
int Renderer::EnrollInputListener() {
  // add input listener
  input_manager_.AddInputListener(&renderer_settings_);
  input_manager_.AddInputListener(&rendering_pipeline_.pipeline_settings());
  input_manager_.AddInputListener(scene_manager_.GetMainScene());
  return 0;
}
}  // namespace ho_renderer