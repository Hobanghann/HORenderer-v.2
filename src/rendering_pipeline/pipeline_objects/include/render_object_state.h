#ifndef _HORENDERER_RENDERINGPIPELINE_PIPELINEOBJECTS_RENDEROBJECTSTATE_H_
#define _HORENDERER_RENDERINGPIPELINE_PIPELINEOBJECTS_RENDEROBJECTSTATE_H_

namespace ho_renderer {
enum FrustumCullingResult { kINSIDE, kINTERSECT, kOUTSIDE };
class RenderObjectState {
 public:
  RenderObjectState();
  RenderObjectState(const RenderObjectState& state);
  RenderObjectState& operator=(const RenderObjectState& state);
  ~RenderObjectState();

  FrustumCullingResult object_culling_state() const;
  RenderObjectState& set_object_culling_state(FrustumCullingResult result);

 private:
  FrustumCullingResult object_culling_state_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_RENDERINGPIPELINE_PIPELINEOBJECTS_RENDEROBJECTSTATE_H_