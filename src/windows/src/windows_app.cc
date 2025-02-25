#define VK_Q 0x51
#define VK_W 0x57
#define VK_E 0x45
#define VK_A 0x41
#define VK_S 0x53
#define VK_D 0x44

#include "windows/include/windows_app.h"

#include <windows.h>

#include <cstdint>

#include "app/res/resource.h"
#include "engine/include/input_receiver.h"

WindowsApp::WindowsApp(HINSTANCE hInstance, const int screen_width,
                       const int screen_height)
    : hInstance_(hInstance),
      screen_width_(screen_width),
      screen_height_(screen_height),
      is_running_(true),
      ho_renderer_(screen_width, screen_height) {}
WindowsApp::~WindowsApp() = default;

bool WindowsApp::IsRunning() const { return is_running_; }

void WindowsApp::InitializeApp(HINSTANCE hInstance, int nCmdShow,
                               LPCSTR lpszWndClassName) {
  hInstance_ = hInstance;
  WNDCLASSEX stWndClass;
  HWND hMainWnd;
  memset(&stWndClass, 0, sizeof(stWndClass));
  stWndClass.cbSize = sizeof(WNDCLASSEX);
  stWndClass.cbClsExtra = 0;
  stWndClass.cbWndExtra = 0;
  stWndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
  stWndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
  stWndClass.hIcon = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICON1),
                                      IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
  if (!stWndClass.hIcon) {
    DWORD error = GetLastError();
    printf("LoadImage failed! Error code: %lu\n", error);
  }
  stWndClass.hIconSm = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICON1),
                                        IMAGE_ICON, 16, 16, LR_SHARED);
  stWndClass.hInstance = hInstance;
  stWndClass.lpfnWndProc = (WNDPROC)(WindowsApp::WndProc);
  stWndClass.lpszClassName = lpszWndClassName;
  stWndClass.lpszMenuName = NULL;
  stWndClass.style = CS_OWNDC;

  RegisterClassEx(&stWndClass);

  RECT clientSize = {0, 0, screen_width_, screen_height_};
  DWORD dwStyle = WS_OVERLAPPEDWINDOW;

  AdjustWindowRect(&clientSize, dwStyle, FALSE);

  hMainWnd = CreateWindow(
      lpszWndClassName, NULL, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
      clientSize.right - clientSize.left, clientSize.bottom - clientSize.top,
      NULL, (HMENU)NULL, hInstance, NULL);
  SetWindowTextW(hMainWnd, L"HO Renderer");
  ShowWindow(hMainWnd, nCmdShow);
  hWindow_ = hMainWnd;

  BITMAPINFO bmi = {};
  bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  bmi.bmiHeader.biWidth = screen_width_;
  bmi.bmiHeader.biHeight = -screen_height_;
  bmi.bmiHeader.biPlanes = 1;
  bmi.bmiHeader.biBitCount = 32;
  bmi.bmiHeader.biCompression = BI_RGB;
  window_dc_ = GetDC(hWindow_);
  memory_dc_ = CreateCompatibleDC(window_dc_);
  std::uint32_t* color_buffer = nullptr;
  created_bitmap_ = CreateDIBSection(memory_dc_, &bmi, DIB_RGB_COLORS,
                                     (void**)&color_buffer, NULL, 0);
  default_bitmap_ = (HBITMAP)SelectObject(memory_dc_, created_bitmap_);

  input_sender_.EnrollReceiver(
      ho_renderer_.GetInputManager().GetInputReceiverPointer());
  ho_renderer_.Initialize();
  ho_renderer_.InjectExternalColorBuffer(color_buffer);
}

void WindowsApp::ProcessMessages(MSG& Message) {
  while (PeekMessage(&Message, 0, 0, 0, PM_REMOVE)) {
    if (Message.message == WM_QUIT) {
      is_running_ = false;
      break;
    }
    TranslateMessage(&Message);
    DispatchMessage(&Message);
  }
}

void WindowsApp::Run() {
  ho_renderer_.PreUpdate();
  ho_renderer_.Update();
  ho_renderer_.Render();
  ho_renderer_.PostUpdate();
  // swap buffer
  BitBlt(window_dc_, 0, 0, screen_width_, screen_height_, memory_dc_, 0, 0,
         SRCCOPY);
  // draw message
  char char_buf[10];
  snprintf(char_buf, sizeof(char_buf), "FPS : %d", ho_renderer_.GetFPS());
  TextOut(window_dc_, 10, 10, char_buf, strlen(char_buf));
}

void WindowsApp::Quit() {
  DeleteObject(default_bitmap_);
  DeleteObject(created_bitmap_);
  ReleaseDC(hWindow_, window_dc_);
  ReleaseDC(hWindow_, memory_dc_);
}

LRESULT CALLBACK WindowsApp::WndProc(HWND hWnd, UINT iMessage, WPARAM wParam,
                                     LPARAM lParam) {
  switch (iMessage) {
    case WM_CREATE:
      break;
    case WM_KEYDOWN:
      // send input
      switch (wParam) {
        case VK_F1:
          input_sender_.KeyPressed(ho_renderer::InputKey::kKEY_F1);
          break;
        case VK_F2:
          input_sender_.KeyPressed(ho_renderer::InputKey::kKEY_F2);
          break;
        case VK_F3:
          input_sender_.KeyPressed(ho_renderer::InputKey::kKEY_F3);
          break;
        case VK_F4:
          input_sender_.KeyPressed(ho_renderer::InputKey::kKEY_F4);
          break;
        case VK_F5:
          input_sender_.KeyPressed(ho_renderer::InputKey::kKEY_F5);
          break;
        case VK_F6:
          input_sender_.KeyPressed(ho_renderer::InputKey::kKEY_F6);
          break;
        case VK_F7:
          input_sender_.KeyPressed(ho_renderer::InputKey::kKEY_F7);
          break;
        case VK_F8:
          input_sender_.KeyPressed(ho_renderer::InputKey::kKEY_F8);
          break;
        case VK_F9:
          input_sender_.KeyPressed(ho_renderer::InputKey::kKEY_F9);
          break;
        case VK_F11:
          input_sender_.KeyPressed(ho_renderer::InputKey::kKEY_F11);
          break;
        case VK_LEFT:
          input_sender_.KeyPressed(ho_renderer::InputKey::kKEY_LEFT);
          break;
        case VK_RIGHT:
          input_sender_.KeyPressed(ho_renderer::InputKey::kKEY_RIGHT);
          break;
        case VK_UP:
          input_sender_.KeyPressed(ho_renderer::InputKey::kKEY_UP);
          break;
        case VK_DOWN:
          input_sender_.KeyPressed(ho_renderer::InputKey::kKEY_DOWN);
          break;
        case VK_DELETE:
          input_sender_.KeyPressed(ho_renderer::InputKey::kKEY_DELETE);
          break;
        case VK_NEXT:
          input_sender_.KeyPressed(ho_renderer::InputKey::kKEY_PAGEDOWN);
          break;
        case VK_Q:
          input_sender_.KeyPressed(ho_renderer::InputKey::kKEY_Q);
          break;
        case VK_W:
          input_sender_.KeyPressed(ho_renderer::InputKey::kKEY_W);
          break;
        case VK_E:
          input_sender_.KeyPressed(ho_renderer::InputKey::kKEY_E);
          break;
        case VK_A:
          input_sender_.KeyPressed(ho_renderer::InputKey::kKEY_A);
          break;
        case VK_S:
          input_sender_.KeyPressed(ho_renderer::InputKey::kKEY_S);
          break;
        case VK_D:
          input_sender_.KeyPressed(ho_renderer::InputKey::kKEY_D);
          break;
      }
      break;
    case WM_KEYUP:
      // send input
      switch (wParam) {
        case VK_F1:
          input_sender_.KeyReleased(ho_renderer::InputKey::kKEY_F1);
          break;
        case VK_F2:
          input_sender_.KeyReleased(ho_renderer::InputKey::kKEY_F2);
          break;
        case VK_F3:
          input_sender_.KeyReleased(ho_renderer::InputKey::kKEY_F3);
          break;
        case VK_F4:
          input_sender_.KeyReleased(ho_renderer::InputKey::kKEY_F4);
          break;
        case VK_F5:
          input_sender_.KeyReleased(ho_renderer::InputKey::kKEY_F5);
          break;
        case VK_F6:
          input_sender_.KeyReleased(ho_renderer::InputKey::kKEY_F6);
          break;
        case VK_F7:
          input_sender_.KeyReleased(ho_renderer::InputKey::kKEY_F7);
          break;
        case VK_F8:
          input_sender_.KeyReleased(ho_renderer::InputKey::kKEY_F8);
          break;
        case VK_F9:
          input_sender_.KeyReleased(ho_renderer::InputKey::kKEY_F9);
          break;
        case VK_F11:
          input_sender_.KeyReleased(ho_renderer::InputKey::kKEY_F11);
          break;
        case VK_LEFT:
          input_sender_.KeyReleased(ho_renderer::InputKey::kKEY_LEFT);
          break;
        case VK_RIGHT:
          input_sender_.KeyReleased(ho_renderer::InputKey::kKEY_RIGHT);
          break;
        case VK_UP:
          input_sender_.KeyReleased(ho_renderer::InputKey::kKEY_UP);
          break;
        case VK_DOWN:
          input_sender_.KeyReleased(ho_renderer::InputKey::kKEY_DOWN);
          break;
        case VK_DELETE:
          input_sender_.KeyReleased(ho_renderer::InputKey::kKEY_DELETE);
          break;
        case VK_NEXT:
          input_sender_.KeyReleased(ho_renderer::InputKey::kKEY_PAGEDOWN);
          break;
        case VK_Q:
          input_sender_.KeyReleased(ho_renderer::InputKey::kKEY_Q);
          break;
        case VK_W:
          input_sender_.KeyReleased(ho_renderer::InputKey::kKEY_W);
          break;
        case VK_E:
          input_sender_.KeyReleased(ho_renderer::InputKey::kKEY_E);
          break;
        case VK_A:
          input_sender_.KeyReleased(ho_renderer::InputKey::kKEY_A);
          break;
        case VK_S:
          input_sender_.KeyReleased(ho_renderer::InputKey::kKEY_S);
          break;
        case VK_D:
          input_sender_.KeyReleased(ho_renderer::InputKey::kKEY_D);
          break;
      }
      break;
    case WM_SYSKEYDOWN:
      switch (wParam) {
        case VK_F10:
          input_sender_.KeyPressed(ho_renderer::InputKey::kKEY_F10);
          return 0;  // disable default action
      }
      break;
    case WM_SYSKEYUP:
      switch (wParam) {
        case VK_F10:
          input_sender_.KeyReleased(ho_renderer::InputKey::kKEY_F10);
          return 0;  // disable default action
      }
      break;
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
  }
  return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

ho_renderer::InputSender WindowsApp::input_sender_ = ho_renderer::InputSender();

void WindowsApp::CreateDebugConsole() {
  AllocConsole();

  FILE* fp;
  freopen_s(&fp, "CONIN$", "r", stdin);
  freopen_s(&fp, "CONOUT$", "w", stderr);
  freopen_s(&fp, "CONOUT$", "w", stdout);
  printf("Debug Console Initialized!\n");
}