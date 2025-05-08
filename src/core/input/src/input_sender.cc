#include "core/input/include/input_sender.h"

#include <cassert>
#include <string>

#include "tools/include/debug.h"

namespace ho_renderer {
InputSender::InputSender() = default;
InputSender::~InputSender() = default;

void InputSender::EnrollReceiver(InputReceiver* input_receiver) {
  ASSERT_MSG(
      input_receiver != nullptr,
      "InputSender::EnrollReceiver Error : input_receiver must be not null");
  input_receiver_ = input_receiver;
}

void InputSender::KeyPressed(Input key) {
  ASSERT_MSG(
      input_receiver_ != nullptr,
      "InputSender::KeyPressed Error : there is no enrolled input receiver");
  if (input_receiver_ == nullptr) {
    return;
  }
  input_receiver_->UpdateKeyStatus(key, true);
}
void InputSender::KeyReleased(Input key) {
  ASSERT_MSG(
      input_receiver_ != nullptr,
      "InputSender::KeyReleased Error : there is no enrolled input receiver");
  if (input_receiver_ == nullptr) {
    return;
  }
  input_receiver_->UpdateKeyStatus(key, false);
}

void InputSender::MousePressed(Input key, int x, int y) {
  ASSERT_MSG(
      input_receiver_ != nullptr,
      "InputSender::MousePressed Error : there is no enrolled input receiver");
  if (input_receiver_ == nullptr) {
    return;
  }
  input_receiver_->UpdateKeyStatus(key, true);
  input_receiver_->SetPrevMouseCoordinate(x, y);
  input_receiver_->SetCurrentMouseCoordinate(x, y);
}
void InputSender::MouseReleased(Input key, int x, int y) {
  ASSERT_MSG(
      input_receiver_ != nullptr,
      "InputSender::MouseReleased Error : there is no enrolled input receiver");
  if (input_receiver_ == nullptr) {
    return;
  }
  input_receiver_->UpdateKeyStatus(key, false);
}
void InputSender::MouseMoved(int x, int y) {
  ASSERT_MSG(
      input_receiver_ != nullptr,
      "InputSender::MouseMoved Error : there is no enrolled input receiver");
  if (input_receiver_ == nullptr) {
    return;
  }
  input_receiver_->UpdateMouseCoordinate(x, y);
}
}  // namespace ho_renderer