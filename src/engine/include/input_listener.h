#ifndef _HORENDERER_ENGINE_INPUT_LISTENER_H_
#define _HORENDERER_ENGINE_INPUT_LISTENER_H_

#include "engine/include/input_manager.h"

namespace ho_renderer {
class InputListener {
 public:
  virtual void Update(InputReceiver& input_receiver,
                      const float delta_time) = 0;
  bool is_active() const;
  void Active();
  void Inactive();

 private:
  bool is_active_ = false;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_ENGINE_INPUT_LISTENER_H_