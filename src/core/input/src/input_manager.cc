#include "core/input/include/input_manager.h"

#include "core/input/include/input_listener.h"
#include "tools/include/debug.h"

namespace ho_renderer {
InputManager::InputManager() = default;
;
InputManager::~InputManager() = default;

void InputManager::HandleInputs(float delta_time) {
  for (auto listener_itr = input_listeners_.begin();
       listener_itr != input_listeners_.end(); listener_itr++) {
    (*listener_itr)->Update(input_receiver_, delta_time);
  }
}

void InputManager::AddInputListener(InputListener *input_listener) {
  ASSERT_MSG(
      input_listener != nullptr,
      "InputManager::AddInputListener Error : input_listener must be not null");
  input_listeners_.push_back(input_listener);
}
void InputManager::DeleteInputListener(InputListener *input_listener) {
  ASSERT_MSG(input_listener != nullptr,
             "InputManager::DeleteInputListener Error : input_listener must be "
             "not null");
  auto listener_itr = input_listeners_.begin();
  while (listener_itr != input_listeners_.end()) {
    ASSERT_MSG(*listener_itr != input_listener,
               "InputManager::DeleteInputListener Error : input_listener "
               "wasn't enrolled ");
    if (*listener_itr == input_listener) {
      input_listeners_.erase(listener_itr);
      return;
    }
    listener_itr = std::next(listener_itr);
  }
}

InputReceiver *InputManager::GetInputReceiverPointer() {
  return &input_receiver_;
}
}  // namespace ho_renderer