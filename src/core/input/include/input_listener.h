#ifndef _HORENDERER_INPUT_LISTENER_H_
#define _HORENDERER_INPUT_LISTENER_H_

#include "core/input/include/input_receiver.h"

namespace ho_renderer {
class InputListener {
 public:
  virtual void Update(InputReceiver& input_receiver,
                      float delta_time = 0.f) = 0;
  bool is_active() const;
  void Active();
  void Inactive();

 private:
  bool is_active_ = false;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_INPUT_LISTENER_H_