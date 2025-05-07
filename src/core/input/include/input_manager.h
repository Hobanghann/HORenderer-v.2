#ifndef _HORENDERER_INPUT_MANAGER_H_
#define _HORENDERER_INPUT_MANAGER_H_

#include <deque>
#include <list>

#include "core/input/include/input_listener.h"
#include "core/input/include/input_receiver.h"

namespace ho_renderer {
class InputListener;
class InputManager {
 public:
  InputManager();
  InputManager(const InputManager &) = delete;
  InputManager &operator=(const InputManager &) = delete;
  ~InputManager();

  void HandleInputs(float delta_time);
  void AddInputListener(InputListener *input_listener);
  void DeleteInputListener(InputListener *input_listener);

  InputReceiver *GetInputReceiverPointer();

 private:
  InputReceiver input_receiver_;
  std::list<InputListener *> input_listeners_;
};
}  // namespace ho_renderer

#endif  // _HORENDERER_INPUT_MANAGER_H_