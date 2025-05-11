```plaintext
## 🧑‍💻 About This Project
HORenderer is a software renderer developed from scratch in C++ without relying on any external rendering libraries.
This project was initiated to gain a deep understanding of the graphics pipeline, and implements all major stages—from vertex transformation to rasterization and fragment shading—manually.

Currently, the renderer operates on a single thread, supports only non-PBR rendering, and loads models exclusively in the .obj format.
The ultimate goal of this project is to evolve it into a hardware-accelerated or hybrid game engine.

HORenderer는 외부 렌더링 라이브러리에 의존하지 않고, C++로 처음부터 직접 구현한 소프트웨어 렌더러입니다.
이 프로젝트는 그래픽스 파이프라인의 동작 원리를 깊이 이해하기 위해 시작되었으며, 정점 변환부터 래스터화, 프래그먼트 셰이딩 등 모든 렌더링 파이프라인의 주요 단계를 직접 구현했습니다.

현재 프로젝트는 싱글 스레드로 구현되어 있으며, non-PBR 렌더링, .obj 포멧만을 지원합니다.
궁극적으로는 이 프로젝트를 기반으로 하드웨어 렌더링 또는 하이브리드 게임 엔진으로 발전시키는 것을 목표로 하고 있습니다.

## 🔨 Build & Run Instructions
[Prerequisites]
- Windows 10 or later
- Visual Studio 2022
- CMake 3.20+
- C++17

[Build Steps]
From the root of the project source tree, you can generate a Visual Studio solution using CMake.

프로젝트의 최상위 소스 트리에서 cmake를 통해 Visual Studio 솔루션을 생성할 수 있습니다.

## 📸 Screenshots

[Wireframe Mode] 
![Image](https://github.com/user-attachments/assets/7fef0c2d-caa8-4cf7-81ce-eb9ca5149c92)

[Flat Shading]
![Image](https://github.com/user-attachments/assets/f371fde9-ec2a-44a9-b680-29bb633236db)

[Phong Shading]  
![Image](https://github.com/user-attachments/assets/972a2a57-7d0e-43b2-a3c5-e5301c339d46)

[Texture Mapping]  
![Image](https://github.com/user-attachments/assets/3a756c4d-1895-4a4b-acf0-d7640cad6385)


## 🔀 Work Flow
Initialize ── Preupdate── Update── Run rendering pipeline ── Postupdate ── Quit
		  └─────────────────Loop────────────────┘

## 📂 Project Structure
<src> 
  │
  ├── <app>
  │
  ├── <core>
  │      ├── <input>
  │      │  
  │      ├── <math>
  │      │
  │      └── <time>
  │
  ├── <graphics>
  │        ├── <color>
  │        │
  │        ├── <rendering_pipeline>
  │        │             ├── <pipeline_components>
  │        │                     │
  │        │             ├── <pipeline_objects>
  │        │                     │
  │        │             ├── <stages>
  │        │                     │
  │        │             └── <system>
  │        │
  │        └── <resource>
  │            
  ├── <renderer> 
  │
  ├── <scene>
  │       ├── <camera>
  │       │  
  │       ├── <light>
  │       │  
  │       ├── <object>
  │       │  
  │       └── <system>
  │
  ├── <tools>
  │
  └── <windows>




## 📜Mathematical Rules and Algorithms Used in the Renderer
[🌐 Coordinate System]
-Local space : Left-handed Y-up Coordinate System.
-World space : Left-handed Y-up Coordinate System.
-View space : Right-handed Y-up Coordinate System.
-Clip space : Left-handed Y-up Coordinate System.

[💾 Index Buffer Layout]
-The renderer supports both counter clockwise, clockwise order.

[🧮 Method for Defining a Transform]
-Scale transform : Matrix
-Rotation transform : Quaternion
-Translation transform : Matrix
-Projection transform : Matrix

[🎨 Color]
-The color spaces used is LinearRGB, sRGB.
-The renderer supports gamma correction.
-The color depth is 32-bit, and it is composed of alpha, red, green, and blue (ARGB format).

[🧠 Algorithms]
-Line Rasterization : Bresenham's Algorithm
-Triangle Rasterization : Barycentric Algorithm / Edge function Half-testing, Incremental Approch
-Backface Culling: Triple Product
-Interpolation : Linear Interpolation / Perspective-Correct Interpolation / Sphere Linearly Interpolation(Slerp)

[🌓 Lighting]
- Supports ambient light, directional light, and point lights.
- Diffuse Lighting: Based on a Rembrandt-style lighting model.
- Specular Lighting: Implemented using the Blinn-Phong lighting model.
- Lighting Calculations: All attributes are computed in view space.
- TBN Matrix: Constructed per-fragment using vertex normal, tangent, and handedness.


## 🎮 Key Guide
[Renderer]
-F1 : 30 FPS mode
-F2 : 60 FPS mode
-F3 :  Variable FPS mode
-Num1 : Wireframe mode
-Num2 : Fill mode
-Num3 : Texture mapping mode
-Num4 : Change shading mode(Flat, Phong)
-Num5 : Change mesh's bounding volume(Sphere, AABB)
-Num6 : Change interpolation(Linear, Perspective correction)
-Num7 : On/Off Backface culling
-Num8 : On/Off Ambient lighting
-Num9 : On/Off Diffuse lighting
-Num0 : On/Off Specular lighting

[Main Game Object]
-Mouse Right Button + Mouse Move : Rotate object

[Camera]
-Mouse Right Button + Mouse Move : Rotate camera view
-W : Move forward
-S : Move backward
-A : Move left
-D : Move Right

##📁 Assets License / Attribution
Mug : https://www.cgtrader.com/free-3d-models/food/beverage/lowpoly-mug-for-free
Nier2B : 