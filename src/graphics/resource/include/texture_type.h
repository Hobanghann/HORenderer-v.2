#ifndef _HORENDERER_TEXTURE_TYPE_H_
#define _HORENDERER_TEXTURE_TYPE_H_

namespace ho_renderer {
enum TextureType {
  Ambient = 0,
  Diffuse,
  Specular,
  SpecularHighlight,
  Alpha,
  Bump,
  Displacement,
  Roughness,
  Metallic,
  Sheen,
  Emmissive,
  Normal,
  Last
};
}

#endif  // _HORENDERER_TEXTURE_TYPE_H_