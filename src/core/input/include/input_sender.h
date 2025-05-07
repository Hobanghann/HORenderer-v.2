#ifndef _HORENDERER_INPUT_SENDER_H_
#define _HORENDERER_INPUT_SENDER_H_

#include "core/input/include/input_receiver.h"

namespace ho_renderer {
class InputSender {
 public:
  InputSender();
  InputSender(const InputSender&) = delete;
  InputSender& operator=(const InputSender&) = delete;
  ~InputSender();

  void EnrollReceiver(InputReceiver* input_receiver);

  void KeyPressed(Input key);
  void KeyReleased(Input key);
  void MousePressed(Input key, int x, int y);
  void MouseReleased(Input key, int x, int y);
  void MouseMoved(int x, int y);

 protected:
  InputReceiver* input_receiver_;
};
}  // namespace ho_renderer
#endif  // _HORENDERER_INPUT_SENDER_H_