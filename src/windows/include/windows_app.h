#ifndef _WINDOWS_WINDOWS_APP_H_
#define _WINDOWS_WINDOWS_APP_H_

#include <windows.h>

#include <memory>

#include "app/include/debug.h"
#include "engine/input/include/input_sender.h"
#include "renderer/include/renderer.h"

class WindowsApp {
 public:
  WindowsApp() = delete;
  WindowsApp(const WindowsApp&) = delete;
  WindowsApp(HINSTANCE hInstance, const int screen_width,
             const int screen_height);
  WindowsApp& operator=(const WindowsApp&) = delete;
  ~WindowsApp();

  bool IsRunning() const;

  // regist and create window
  void InitializeApp(HINSTANCE hInstance, int nCmdShow, LPCSTR name);
  // message loop
  void ProcessMessages(MSG& Message);
  // run renderer
  void Run();
  // quit renderer
  void Quit();

  void CreateDebugConsole();

 private:
  static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam,
                                  LPARAM lParam);

  HINSTANCE hInstance_;
  HWND hWindow_;
  HDC window_dc_;
  HDC memory_dc_;
  HBITMAP default_bitmap_;
  HBITMAP created_bitmap_;
  int screen_width_;
  int screen_height_;
  bool is_running_;
  static ho_renderer::InputSender input_sender_;
  ho_renderer::Renderer ho_renderer_;
};

#endif  // _WINDOWS_WINDOWS_APP_H_