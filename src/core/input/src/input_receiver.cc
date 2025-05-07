#include "core/input/include/input_receiver.h"

#include <algorithm>

namespace ho_renderer {
InputReceiver::InputReceiver() { ResetKeyStatus(); }
InputReceiver::~InputReceiver() = default;

void InputReceiver::ResetKeyStatus() {
  std::fill(input_status_.begin(), input_status_.end(), false);
}
void InputReceiver::UpdateKeyStatus(Input key, bool status) {
  input_status_[key] = status;
}
void InputReceiver::SetPrevMouseCoordinate(int x, int y) {
  prev_mouse_x_ = x;
  prev_mouse_y_ = y;
}
void InputReceiver::SetCurrentMouseCoordinate(int x, int y) {
  current_mouse_x_ = x;
  current_mouse_y_ = y;
}
void InputReceiver::UpdateMouseCoordinate(int x, int y) {
  SetPrevMouseCoordinate(current_mouse_x_, current_mouse_y_);
  SetCurrentMouseCoordinate(x, y);
}

bool InputReceiver::IsPressed(Input key) const { return input_status_[key]; }
int InputReceiver::GetMouseX() const { return current_mouse_x_; }
int InputReceiver::GetMouseY() const { return current_mouse_y_; }
int InputReceiver::GetMouseDeltaX() {
  // Set prev_mouse_x_ to current_mouse_x_ so that the next delta_x becomes 0.
  // This prevents a constant delta_x from being returned when the event handler
  // is not called due to no events occurring while the left mouse button is
  // held down.
  int tmp = prev_mouse_x_;
  prev_mouse_x_ = current_mouse_x_;
  return current_mouse_x_ - tmp;
}
int InputReceiver::GetMouseDeltaY() {
  int tmp = prev_mouse_y_;
  prev_mouse_y_ = current_mouse_y_;
  return current_mouse_y_ - tmp;
}
}  // namespace ho_renderer