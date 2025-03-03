#ifndef _HORENDERER_ENGINE_INPUT_INPUT_SENDER_H_
#define _HORENDERER_ENGINE_INPUT_INPUT_SENDER_H_

#include "engine/input/include/input_receiver.h"

namespace ho_renderer {
class InputSender {
 public:
  InputSender();
  InputSender(const InputSender&) = delete;
  InputSender& operator=(const InputSender&) = delete;
  ~InputSender();

  void EnrollReceiver(InputReceiver* input_receiver);

  void KeyPressed(InputKey key);
  void KeyReleased(InputKey key);

 protected:
  InputReceiver* input_receiver_;
};
}  // namespace ho_renderer
#endif  // _HORENDERER_ENGINE_INPUT_INPUT_SENDER_H_