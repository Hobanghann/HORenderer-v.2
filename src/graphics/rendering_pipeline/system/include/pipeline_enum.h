#ifndef _HORENDERER_PIPELINE_ENUM_H_
#define _HORENDERER_PIPELINE_ENUM_H_

namespace ho_renderer {
enum IndexOrder { kClockWise = 0, kCounterClockWise };
enum PrimitiveType { kPoint = 0, kLine, kTriangle };
enum BoundingVolumeMode { kSphere = 0, kAABB };
enum InterpolationMode { kAffine = 0, kPerspectiveCorrection };
enum RenderingMode { kWireFrame = 0, kFill, kTextureMapping };
enum TextureMappingMode { kNonPBR = 0, kPBRApproximation };
enum ShadingMode { kFlat = 0, kPhong };
enum FrustumCullingResult { kInside, kIntersect, kOutside };
}  // namespace ho_renderer

#endif  // _HORENDERER_PIPELINE_ENUM_H_