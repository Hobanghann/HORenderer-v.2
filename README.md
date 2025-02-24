```plaintext
## 🔨Build Instructions
Use CMake to build the project.  
Currently, this project supports only Windows and Visual Studio.


## 🔀 Work Flow
Initialize ── Preupdate data ── Update data ── Run rendering pipeline ── Postupdate data ── Quit
		    └────────────────────────────Loop──────────────────────────────┘



## 📂 Project Structure
<src> 
│
├── <app>
│    ├── debug.h
│    ├── resource script
│    └── main.cc 
│
├── <math>
│    ├── Vector2
│    ├── Vector3
│    ├── Vector4
│    ├── Matrix2x2                     
│    ├── Matrix3x3
│    ├── Matrix4x4
│    ├── Quaternion
│    ├── LinearTransform 
│    ├── AffineTransform   
│    ├── QuaternionTransform             
│    ├── Plane
│    ├── Frustum
│    └── EulerAngle
│
├── <asset>
│    ├── CameraObject
│    ├── GameObject
│    ├── Transform
│    ├── Mesh
│    ├── Vertex
│    ├── SphereBoundingVolume 
│    ├── AAB (Axis Aligned Box) BoundingVolume      
│    └── Scene
│            
├── <rendering_pipeline> 
│    ├── /pipeline
│    │    ├── RenderingPipeline
│    │    ├── PipelineSettings
│    │    └── ResourcesManager
│    │
│    ├── /pipeline_object
│    │    ├── ColorBuffer         
│    │    ├── DepthBuffer
│    │    ├── FrameBuffer
│    │    ├── Primitive
│    │    ├── Point
│    │    ├── Line
│    │    ├── Triangle
│    │    ├── Fragment
│    │    └── RenderObjectStates
│    │
│    ├── /stages
│    │    ├── VertexSpecification
│    │    ├── VertexProcessing
│    │    ├── VertexPostProcessing
│    │    ├── Rasterization 
│    │    ├── FragmentProcessing
│    │    └── PerSampleProcessing
│    │     
│    └── /shaders
│         ├── VertexSpecifyingShader
│         ├── VertexShader
│         ├── FrustumCullingShader
│         ├── PrimitiveAssemblyShader
│         ├── ClippingShader
│         ├── PerspectiveDivideShader
│         ├── FaceCullingShader
│         ├── ViewportTransformShader
│         ├── RasterizingShader       
│         ├── FragmentShader
│         ├── ScissorTestingShader
│         ├── DepthTestingShader
│         └── FrameWritingShader
│
├── <engine>
│        ├── InputSender
│        ├── InputReceiver
│        ├── InputListener
│        ├── InputManager
│        ├── SRGB
│        ├── Timer
│        ├── MeshGenerator
│        ├── MeshManager
│        ├── SceneManager
│        ├── RendererSettings
│        └── Renderer
│
└── <windows>
      └── WindowsApp



## 📜Mathematical Rules and Algorithms Used in the Renderer
[🌐 Coordinate System]
-Local space : Left-handed Y-up Coordinate System.
-World space : Left-handed Y-up Coordinate System.
-View space : Right-handed Y-up Coordinate System.
-Clip space : Left-handed Y-up Coordinate System.

[💾 Index Buffer Layout]
-Store indices in a clockwise order.

[🧮 Method for Defining a Transform]
-Scale transform : Matrix
-Rotation transform : Quaternion
-Translation transform : Matrix
-Projection transform : Matrix

[🎨 Color]
-The color space used is sRGB.
-The renderer supports gamma correction.
-The color depth is 32-bit, and it is composed of alpha, red, green, and blue (ARGB format).

[🧠 Algorithms]
-Line Rasterization : Bresenham's Algorithm
-Triangle Rasterization : Barycentric Algorithm
-Backface Culling: Triple Product
-Interpolation : Linear Interpolation / Perspective-Correct Interpolation / Sphere Linearly Interpolation(Slerp)


## 🎮 Key Guide
[Renderer]
-F1 : Wireframe mode
-F2 : Fill mode
-F3 : Texture mapping mode
-F4 : Sphere bounding volume / Aligned axis box bounding volume
-F5 : Affine interpolation / Perspective correct interpolation
-F6 : On / Off backface culling mode
-F9 : 30 FPS mode
-F10 : 60 FPS mode
-F11 : Variable FPS mode

[Main Game Object]
-Q : Rotate the main object in the positive roll direction.
-E : Rotate the main object in the negative roll direction.
-W : Rotate the main object in the positive pitch direction.
-S : Rotate the main object in the negative pitch direction.
-A : Rotate the main object in the positive yaw direction.
-D : Rotate the main object in the negative yaw direction.

[Camera]
-UP : Rotate the camera object in the positive pitch direction.
-DOWN : Rotate the camera object in the negative roll direction.
-LEFT : Rotate the camera object in the positive roll direction.
-RIGHT : Rotate the camera object in the negative roll direction.


