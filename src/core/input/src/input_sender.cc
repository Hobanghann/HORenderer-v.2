#include "core/input/include/input_sender.h"

#include <cassert>
#include <string>

namespace ho_renderer {
InputSender::InputSender() = default;
InputSender::~InputSender() = default;

void InputSender::EnrollReceiver(InputReceiver* input_receiver) {
  input_receiver_ = input_receiver;
}

void InputSender::KeyPressed(Input key) {
  if (input_receiver_ == nullptr) {
    return;
  }
  input_receiver_->UpdateKeyStatus(key, true);
}
void InputSender::KeyReleased(Input key) {
  if (input_receiver_ == nullptr) {
    return;
  }
  input_receiver_->UpdateKeyStatus(key, false);
}

void InputSender::MousePressed(Input key, int x, int y) {
  if (input_receiver_ == nullptr) {
    return;
  }
  input_receiver_->UpdateKeyStatus(key, true);
  input_receiver_->SetPrevMouseCoordinate(x, y);
  input_receiver_->SetCurrentMouseCoordinate(x, y);
}
void InputSender::MouseReleased(Input key, int x, int y) {
  if (input_receiver_ == nullptr) {
    return;
  }
  input_receiver_->UpdateKeyStatus(key, false);
}
void InputSender::MouseMoved(int x, int y) {
  if (input_receiver_ == nullptr) {
    return;
  }
  input_receiver_->UpdateMouseCoordinate(x, y);
}
}  // namespace ho_renderer