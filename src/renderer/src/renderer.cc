#include "renderer/include/renderer.h"

#include <memory>
#include <random>
#include <string>

#include "app/include/debug.h"
#include "asset/include/mesh_generator.h"
#include "engine/color/include/linear_rgb.h"
#include "engine/light/include/ambient_light.h"
#include "engine/light/include/directional_light.h"
#include "engine/light/include/point_light.h"
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
  CreateMeshs();
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
  rendering_pipeline_.frame_buffer().GetColorBuffer().InjectExternalBuffer(
      color_buffer);
}
void Renderer::InjectExternalDepthBuffer(float* depth_buffer) {
  rendering_pipeline_.frame_buffer().GetDepthBuffer().InjectExternalBuffer(
      depth_buffer);
}

long long Renderer::GetFPS() { return FPS_; }

int Renderer::CreateMeshs() {
  // create meshes
  mesh_manager_.AddMesh(
      MeshGenerator::GeneratePlane("Unit Plane", 1.f, 1.f, LinearRGB::kBROWN));
  mesh_manager_.AddMesh(
      MeshGenerator::GenerateBox("Unit Box", 1.f, 1.f, 1.f, LinearRGB::kBROWN));
  mesh_manager_.AddMesh(MeshGenerator::GenerateSphere("Unit Sphere", 20, 20,
                                                      1.f, LinearRGB::kBROWN));
  mesh_manager_.AddMesh(
      MeshGenerator::GenerateLine("X axis", 1000.f, LinearRGB::kRED));
  mesh_manager_.AddMesh(
      MeshGenerator::GenerateLine("Y axis", 1000.f, LinearRGB::kGREEN));
  mesh_manager_.AddMesh(
      MeshGenerator::GenerateLine("Z axis", 1000.f, LinearRGB::kBLUE));
  return 0;
}
int Renderer::CreateScene() {
  // create scene
  Scene* main_scene = new Scene(std::string("Main Scene"));
  // add scene
  scene_manager_.AddScene(main_scene);
  scene_manager_.SetMainScene("Main Scene");
  return 0;
}
int Renderer::CreateCameraObjects() {
  // create main_camera
  CameraObject* main_camera = new CameraObject(std::string("Main Camera"));
  // set initial camera settings
  main_camera
      ->set_aspect_ratio(renderer_settings_.screen_width(),
                         renderer_settings_.screen_height())
      .set_transform(
          Transform()
              .set_world_coordinate(Vector3(0.f, 100.f, 500.f))
              .set_world_euler_angle(EulerAngle()
                                         .set_pitch_angle(0.f)
                                         .set_yaw_angle(MathUtils::kPI)
                                         .set_roll_angle(0.f)))
      .set_fov(MathUtils::kPI * 0.38f)
      .set_near_distance(5.5f)
      .set_far_distance(5000.f);
  // add, set camera in scene
  scene_manager_.GetMainScene()->AddCameraObject(main_camera);
  scene_manager_.GetMainScene()->SetMainCamera("Main Camera");
  return 0;
}
int Renderer::CreateGameObjects() {
  GameObject* main_object = new GameObject("Main Object");
  main_object
      ->set_transform(Transform()
                          .set_world_coordinate({0.f, 0.f, 0.f})
                          .set_world_euler_angle(EulerAngle()
                                                     .set_pitch_angle(0.f)
                                                     .set_yaw_angle(0.f)
                                                     .set_roll_angle(0.f))
                          .set_world_scale(100.f))
      // Problem: The static member kBOX is initialized using SRGB's static
      // members. However, the initialization order of static members is
      // undefined. If kBOX is initialized first before SRGB's static members,
      // it will be default-initialized. The initialization order must be
      // explicitly defined so that SRGB's static members are initialized first
      // before kBOX. Solution: Convert SRGB's static members to non-static
      // members.
      .set_mesh(mesh_manager_.GetMesh("Unit Box"))
      .Active();

  // add game_object
  scene_manager_.GetMainScene()->AddGameObject(main_object);

  // create sub game object
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> position_dist(-500.f, 500.0f);
  std::uniform_real_distribution<float> depth_dist(-500.f, 0.f);
  std::uniform_real_distribution<float> angle_dist(0.0f, MathUtils::kPI);
  char buffer[30];
  for (int i = 0; i < 0; i++) {
    snprintf(buffer, sizeof(buffer), "Object%d", i);
    GameObject* object = new GameObject(std::string(buffer));
    object
        ->set_transform(
            Transform()
                .set_world_coordinate(
                    {position_dist(gen), position_dist(gen), depth_dist(gen)})
                .set_world_euler_angle(EulerAngle()
                                           .set_pitch_angle(angle_dist(gen))
                                           .set_yaw_angle(angle_dist(gen))
                                           .set_roll_angle(angle_dist(gen)))
                .set_world_scale(100.f))
        .set_mesh(mesh_manager_.GetMesh("Unit Box"))
        .Inactive();
    // add sub game_object
    scene_manager_.GetMainScene()->AddGameObject(object);
  }

  // create axis
  GameObject* x_axis = new GameObject("X axis");
  x_axis
      ->set_transform(Transform()
                          .set_world_coordinate(Vector3::kZero)
                          .set_world_euler_angle(EulerAngle()
                                                     .set_pitch_angle(0.f)
                                                     .set_yaw_angle(0.f)
                                                     .set_roll_angle(0.f))
                          .set_world_scale(10.f))
      .set_mesh(mesh_manager_.GetMesh("X axis"))
      .Inactive();
  GameObject* y_axis = new GameObject("Y axis");
  y_axis
      ->set_transform(
          Transform()
              .set_world_coordinate(Vector3::kZero)
              .set_world_euler_angle(EulerAngle()
                                         .set_pitch_angle(0.f)
                                         .set_yaw_angle(MathUtils::kPI * 0.5f)
                                         .set_roll_angle(0.f))
              .set_world_scale(10.f))
      .set_mesh(mesh_manager_.GetMesh("Y axis"))
      .Inactive();
  GameObject* z_axis = new GameObject("Z axis");
  z_axis
      ->set_transform(
          Transform()
              .set_world_coordinate(Vector3::kZero)
              .set_world_euler_angle(EulerAngle()
                                         .set_pitch_angle(0.f)
                                         .set_yaw_angle(0.f)
                                         .set_roll_angle(MathUtils::kPI * 0.5f))
              .set_world_scale(10.f))
      .set_mesh(mesh_manager_.GetMesh("Z axis"))
      .Inactive();

  // add axis
  scene_manager_.GetMainScene()->AddGameObject(x_axis);
  scene_manager_.GetMainScene()->AddGameObject(y_axis);
  scene_manager_.GetMainScene()->AddGameObject(z_axis);

  return 0;
}
int Renderer::CreateLights() {
  AmbientLight* ambient_light = new AmbientLight("Main Ambient Light");
  ambient_light->set_light_color(LinearRGB::kGRAY).set_light_intensity(1.f);
  scene_manager_.GetMainScene()->AddAmbientLight(ambient_light);
  scene_manager_.GetMainScene()->SetMainAmbientLight("Main Ambient Light");
  DirectionalLight* directional_light =
      new DirectionalLight("Main Directional Light");
  directional_light->set_light_direction({1.f, 1.f, -1.f, 0.f})
      .set_light_color(LinearRGB::kWHITE)
      .set_light_intensity(0.3f);
  scene_manager_.GetMainScene()->AddDirectionalLight(directional_light);
  scene_manager_.GetMainScene()->SetMainDirectionalLight(
      "Main Directional Light");
  PointLight* point_light = new PointLight("Main Point Light");
  point_light->set_world_coordinate(Vector4(150.f, 200.f, 150.f, 1.f))
      .set_constant_attenuation(1.f)
      .set_linear_attenuation(0.007f)
      .set_quadratic_attenuation(0.0002f)
      .set_light_color(LinearRGB::kWHITE)
      .set_light_intensity(15.0f);
  scene_manager_.GetMainScene()->AddPointLight(point_light);
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