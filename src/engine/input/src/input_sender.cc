#include "engine/input/include/input_sender.h"

#include <cassert>
#include <string>

#include "app/include/debug.h"

namespace ho_renderer {
InputSender::InputSender() = default;
InputSender::~InputSender() = default;

void InputSender::EnrollReceiver(InputReceiver* input_receiver) {
  input_receiver_ = input_receiver;
}

void InputSender::KeyPressed(InputKey key) {
  if (input_receiver_ == nullptr) {
    return;
  }
  input_receiver_->UpdateKeyStatus(key, true);
}
void InputSender::KeyReleased(InputKey key) {
  if (input_receiver_ == nullptr) {
    return;
  }
  input_receiver_->UpdateKeyStatus(key, false);
}
}  // namespace ho_renderer