#include "engine/input/include/input_receiver.h"

#include <algorithm>

#include "app/include/debug.h"

namespace ho_renderer {
InputReceiver::InputReceiver() { ResetKeyStatus(); }
InputReceiver::~InputReceiver() = default;

void InputReceiver::ResetKeyStatus() {
  std::fill(input_status_.begin(), input_status_.end(), false);
}
void InputReceiver::UpdateKeyStatus(const InputKey key, const bool status) {
  input_status_[key] = status;
}

bool InputReceiver::IsPressed(const InputKey key) const {
  return input_status_[key];
}
}  // namespace ho_renderer