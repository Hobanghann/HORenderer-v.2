#include "engine/include/renderer.h"

#include <memory>
#include <random>
#include <string>

#include "app/include/debug.h"
#include "math/include/math_utils.h"

namespace ho_renderer {

Renderer::Renderer(const int screen_width, const int screen_height)
    : total_frame_count_(0),
      delta_time_(0),
      FPS_(0),
      rendering_pipeline_(screen_width, screen_height, Vector2(0.f, 0.f), 0.f,
                          1.f) {
  // set initial renderer settings
  renderer_settings_.set_screen_width(screen_width)
      .set_screen_height(screen_height)
      .set_frame_rate_mode(FrameRateMode::kVARIABLE);
}
Renderer::~Renderer() = default;

int Renderer::Initialize() {
  // create scene
  Scene* main_scene = new Scene(std::string("Main Scene"));
  // add scene
  scene_manager_.AddScene(main_scene);
  scene_manager_.SetMainScene("Main Scene");
  // create main_camera
  CameraObject* main_camera = new CameraObject(std::string("Main Camera"));
  // set initial camera settings
  main_camera
      ->set_aspect_ratio(renderer_settings_.screen_width(),
                         renderer_settings_.screen_height())
      .set_transform(
          Transform()
              .set_world_coordinate(Vector3(0.f, 0.f, 500.f))
              .set_world_euler_angle(EulerAngle()
                                         .set_pitch_angle(0.f)
                                         .set_yaw_angle(MathUtils::kPI)
                                         .set_roll_angle(0.f)))
      .set_fov(MathUtils::kPI * 0.38f)
      .set_near_distance(5.5f)
      .set_far_distance(5000.f);
  // add, set camera in scene
  main_scene->AddCameraObject(main_camera);
  main_scene->SetMainCamera("Main Camera");

  GameObject* main_object = new GameObject("Main Object");
  main_object
      ->set_transform(Transform()
                          .set_world_coordinate({0.f, 0.f, 0.f})
                          .set_world_euler_angle(EulerAngle()
                                                     .set_pitch_angle(0.f)
                                                     .set_yaw_angle(0.f)
                                                     .set_roll_angle(0.f))
                          .set_world_scale(100.f))
      // 문제: static 멤버인 kBOX는 SRGB의 static 멤버를 사용하여 초기화됨.
      // 이때, static 멤버간 초기화 순서는 undefined.
      // kBOX가 먼저 초기화된 후 SRGB의 static 멤버가 초기화되면 kBOX는 default
      // initialize됨. SRGB의 staic 멤버가 먼저 초기화된 후, kBOX가 초기화되도록
      // 순서를 명시해야함 -> SRGB static member를 non static member로
      .set_mesh(Mesh::kBOX)
      .Active();

  // add game_object
  main_scene->AddGameObject(main_object);

  // create sub game object
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> position_dist(-1000.f, 1000.0f);
  std::uniform_real_distribution<float> angle_dist(0.0f, MathUtils::kPI);
  char buffer[30];
  for (int i = 0; i < 10; i++) {
    snprintf(buffer, sizeof(buffer), "Object%d", i);
    GameObject* object = new GameObject(std::string(buffer));
    object
        ->set_transform(
            Transform()
                .set_world_coordinate({position_dist(gen), position_dist(gen),
                                       -position_dist(gen)})
                .set_world_euler_angle(EulerAngle()
                                           .set_pitch_angle(angle_dist(gen))
                                           .set_yaw_angle(angle_dist(gen))
                                           .set_roll_angle(angle_dist(gen)))
                .set_world_scale(100.f))
        .set_mesh(Mesh::kBLACK_BOX)
        .Inactive();
    // add game_object
    main_scene->AddGameObject(object);
  }


  // add input listener
  input_manager_.AddInputListener(&renderer_settings_);
  input_manager_.AddInputListener(&rendering_pipeline_.pipeline_settings());
  input_manager_.AddInputListener(main_scene);
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
      printf("frame mode is 60\n");
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
  rendering_pipeline_.Run(scene_manager_.main_scene());
  return 0;
}
int Renderer::Quit() { return 0; }

InputManager& Renderer::GetInputManager() { return input_manager_; }

void Renderer::InjectExternalColorBuffer(std::uint32_t* color_buffer) {
  rendering_pipeline_.frame_buffer().GetColorBuffer().InjectExternalBuffer(
      color_buffer);
}
void Renderer::InjectExternalDepthBuffer(float* depth_buffer) {
  rendering_pipeline_.frame_buffer().GetDepthBuffer().InjectExternalBuffer(
      depth_buffer);
}

long long Renderer::GetFPS() { return FPS_; }
}  // namespace ho_renderer