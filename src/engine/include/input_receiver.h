#ifndef _HORENDERER_ENGINE_INPUT_RECEIVER_H_
#define _HORENDERER_ENGINE_INPUT_RECEIVER_H_

#include <array>

namespace ho_renderer {
enum InputKey {
  kKEY_ESC = 0,
  kKEY_F1,
  kKEY_F2,
  kKEY_F3,
  kKEY_F4,
  kKEY_F5,
  kKEY_F6,
  kKEY_F7,
  kKEY_F8,
  kKEY_F9,
  kKEY_F10,
  kKEY_F11,
  kKEY_F12,
  kKEY_TILDE,
  kKEY_NUM_1,
  kKEY_NUM_2,
  kKEY_NUM_3,
  kKEY_NUM_4,
  kKEY_NUM_5,
  kKEY_NUM_6,
  kKEY_NUM_7,
  kKEY_NUM_8,
  kKEY_NUM_9,
  kKEY_NUM_0,
  kKEY_MINUS,
  kKEY_EQUAL,
  kKEY_BACKSPACE,
  kKEY_TAB,
  kKEY_Q,
  kKEY_W,
  kKEY_E,
  kKEY_R,
  kKEY_T,
  kKEY_Y,
  kKEY_U,
  kKEY_I,
  kKEY_O,
  kKEY_P,
  kKEY_LBRAKET,
  kKEY_RBRAKET,
  kKEY_BACKSLASH,
  kKEY_CAPSLOCK,
  kKEY_A,
  kKEY_S,
  kKEY_D,
  kKEY_F,
  kKEY_G,
  kKEY_H,
  kKEY_J,
  kKEY_K,
  kKEY_L,
  kKEY_SEMICOLON,
  kKEY_APOSTROPHE,
  kKEY_ENTER,
  kKEY_LSHIFT,
  kKEY_Z,
  kKEY_X,
  kKEY_C,
  kKEY_V,
  kKEY_B,
  kKEY_N,
  kKEY_M,
  kKEY_COMMA,
  kKEY_PERIOD,
  kKEY_SLASH,
  kKEY_RSHIFT,
  kKEY_LCTRL,
  kKEY_LWIN,
  kKEY_LALT,
  kKEY_SPACE,
  kKEY_RALT,
  kKEY_RWIN,
  kKEY_MENU,
  kKEY_RCTRL,
  kKEY_UP,
  kKEY_DOWN,
  kKEY_LEFT,
  kKEY_RIGHT,
  kKEY_INSERT,
  kKEY_HOME,
  kKEY_PAGEUP,
  kKEY_DELETE,
  kKEY_END,
  kKEY_PAGEDOWN,
  LAST_INPUT
};
class InputReceiver {
 public:
  InputReceiver();
  InputReceiver(const InputReceiver&) = delete;
  InputReceiver& operator=(const InputReceiver&) = delete;
  virtual ~InputReceiver();

  void ResetKeyStatus();
  void UpdateKeyStatus(const InputKey key, const bool status);

  bool IsPressed(const InputKey key) const;

 protected:
  std::array<bool, LAST_INPUT> input_status_;
};

}  // namespace ho_renderer
#endif  // _HORENDERER_ENGINE_INPUT_RECEIVER_H_

/*
기존의 문제
input을 queue를 사용하여 저장.
WM_KEYDOWN 메시지가 발생하는 경우 WndProc에서 queue에 input을 저장.
object가 끊기는 문제가 발생함.
왜?
"queue엔 key를 누르는 순간에 해당하는 input만이 삽입됨" -> "key를 누르고 있는 상태"에 대한 처리가 불가능
키를 계속 누르고 있는 경우 사용자가 설정한 frequency에 따라 WM_KEYDOWN 메시지가 발생
이때, WM_KEYDOWN 메시지의 발생 주기가 frame과 일치하지 않을 수 있으며 이로 인해 특정 frame에서만 회전이 발생하는 문제가 생김
*/