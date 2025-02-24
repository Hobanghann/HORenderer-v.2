```plaintext
## 🔹 Work Flow
Initialize ── Preupdate data ── Update data ── Run rendering pipeline ── Postupdate data ── Quit
		    └─────────────────────Loop─────────────────────┘
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
│    ├── Linear Transform 
│    ├── Affine Transformvector                
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
│        ├── SceneManager
│        ├── RendererSettings
│        └── Renderer
│
└── <windows>
      └── WindowsApp
## 🎮 Key Guide
F1 : Wireframe mode
F2 : Fill mode
F3 : Texture mapping mode
F4 : Sphere bounding volume / Aligned axis box bounding volume
F5 : Affine interpolation / Perspective correct interpolation
F6 : On / Off backface culling mode
F9 : 30 FPS mode
F10 : 60 FPS mode
F11 : Variable FPS mode

