#include "windows/include/windows_app.h"

#include <commctrl.h>
#include <windows.h>
#include <windowsx.h>

#include <cstdint>

#include "app/res/resource.h"
#include "core/input/include/input_receiver.h"
#include "windows/include/key_macro.h"

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

  hWindow_ = CreateWindow(
      lpszWndClassName, NULL, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
      clientSize.right - clientSize.left, clientSize.bottom - clientSize.top,
      NULL, (HMENU)NULL, hInstance, NULL);
  SetWindowTextW(hWindow_, L"HO Renderer");
  ShowWindow(hWindow_, nCmdShow);

  BITMAPINFO bmi = {};
  bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  bmi.bmiHeader.biWidth = screen_width_;
  bmi.bmiHeader.biHeight = -screen_height_;
  bmi.bmiHeader.biPlanes = 1;
  bmi.bmiHeader.biBitCount = 32;
  bmi.bmiHeader.biCompression = BI_RGB;
  window_dc_ = GetDC(hWindow_);
  SetBkMode(window_dc_, TRANSPARENT);
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
  RECT clientRect;
  POINT mouse_pt;
  switch (iMessage) {
    case WM_CREATE:
      break;
    case WM_LBUTTONDOWN:
      GetClientRect(hWnd, &clientRect);
      mouse_pt.x = GET_X_LPARAM(lParam);
      mouse_pt.y = GET_Y_LPARAM(lParam);
      if (!PtInRect(&clientRect, mouse_pt)) {
        break;
      }
      input_sender_.MousePressed(ho_renderer::Input::kMOUSE_LBUTTON, mouse_pt.x,
                                 mouse_pt.y);
      SetCapture(hWnd);
      break;
    case WM_LBUTTONUP:
      mouse_pt.x = GET_X_LPARAM(lParam);
      mouse_pt.y = GET_Y_LPARAM(lParam);
      input_sender_.MouseReleased(ho_renderer::Input::kMOUSE_LBUTTON,
                                  mouse_pt.x, mouse_pt.y);
      break;
    case WM_RBUTTONDOWN:
      GetClientRect(hWnd, &clientRect);
      mouse_pt.x = GET_X_LPARAM(lParam);
      mouse_pt.y = GET_Y_LPARAM(lParam);
      if (!PtInRect(&clientRect, mouse_pt)) {
        break;
      }
      input_sender_.MousePressed(ho_renderer::Input::kMOUSE_RBUTTON, mouse_pt.x,
                                 mouse_pt.y);
      SetCapture(hWnd);
      break;
    case WM_RBUTTONUP:
      mouse_pt.x = GET_X_LPARAM(lParam);
      mouse_pt.y = GET_Y_LPARAM(lParam);
      input_sender_.MouseReleased(ho_renderer::Input::kMOUSE_RBUTTON,
                                  mouse_pt.x, mouse_pt.y);
      break;
    case WM_MOUSEMOVE:
      if ((wParam & MK_LBUTTON) || (wParam & MK_RBUTTON)) {
        mouse_pt.x = GET_X_LPARAM(lParam);
        mouse_pt.y = GET_Y_LPARAM(lParam);
        input_sender_.MouseMoved(mouse_pt.x, mouse_pt.y);
      }
      break;
    case WM_KEYDOWN:
      // send input
      switch (wParam) {
        case VK_F1:
          input_sender_.KeyPressed(ho_renderer::Input::kKEY_F1);
          break;
        case VK_F2:
          input_sender_.KeyPressed(ho_renderer::Input::kKEY_F2);
          break;
        case VK_F3:
          input_sender_.KeyPressed(ho_renderer::Input::kKEY_F3);
          break;
        case VK_F4:
          input_sender_.KeyPressed(ho_renderer::Input::kKEY_F4);
          break;
        case VK_F5:
          input_sender_.KeyPressed(ho_renderer::Input::kKEY_F5);
          break;
        case VK_F6:
          input_sender_.KeyPressed(ho_renderer::Input::kKEY_F6);
          break;
        case VK_F7:
          input_sender_.KeyPressed(ho_renderer::Input::kKEY_F7);
          break;
        case VK_F8:
          input_sender_.KeyPressed(ho_renderer::Input::kKEY_F8);
          break;
        case VK_F9:
          input_sender_.KeyPressed(ho_renderer::Input::kKEY_F9);
          break;
        case VK_NUM_0:
          input_sender_.KeyPressed(ho_renderer::Input::kKEY_NUM_0);
          break;
        case VK_NUM_1:
          input_sender_.KeyPressed(ho_renderer::Input::kKEY_NUM_1);
          break;
        case VK_NUM_2:
          input_sender_.KeyPressed(ho_renderer::Input::kKEY_NUM_2);
          break;
        case VK_NUM_3:
          input_sender_.KeyPressed(ho_renderer::Input::kKEY_NUM_3);
          break;
        case VK_NUM_4:
          input_sender_.KeyPressed(ho_renderer::Input::kKEY_NUM_4);
          break;
        case VK_NUM_5:
          input_sender_.KeyPressed(ho_renderer::Input::kKEY_NUM_5);
          break;
        case VK_NUM_6:
          input_sender_.KeyPressed(ho_renderer::Input::kKEY_NUM_6);
          break;
        case VK_NUM_7:
          input_sender_.KeyPressed(ho_renderer::Input::kKEY_NUM_7);
          break;
        case VK_NUM_8:
          input_sender_.KeyPressed(ho_renderer::Input::kKEY_NUM_8);
          break;
        case VK_NUM_9:
          input_sender_.KeyPressed(ho_renderer::Input::kKEY_NUM_9);
          break;
        case VK_LEFT:
          input_sender_.KeyPressed(ho_renderer::Input::kKEY_LEFT);
          break;
        case VK_RIGHT:
          input_sender_.KeyPressed(ho_renderer::Input::kKEY_RIGHT);
          break;
        case VK_UP:
          input_sender_.KeyPressed(ho_renderer::Input::kKEY_UP);
          break;
        case VK_DOWN:
          input_sender_.KeyPressed(ho_renderer::Input::kKEY_DOWN);
          break;
        case VK_DELETE:
          input_sender_.KeyPressed(ho_renderer::Input::kKEY_DELETE);
          break;
        case VK_NEXT:
          input_sender_.KeyPressed(ho_renderer::Input::kKEY_PAGEDOWN);
          break;
        case VK_Q:
          input_sender_.KeyPressed(ho_renderer::Input::kKEY_Q);
          break;
        case VK_W:
          input_sender_.KeyPressed(ho_renderer::Input::kKEY_W);
          break;
        case VK_E:
          input_sender_.KeyPressed(ho_renderer::Input::kKEY_E);
          break;
        case VK_A:
          input_sender_.KeyPressed(ho_renderer::Input::kKEY_A);
          break;
        case VK_S:
          input_sender_.KeyPressed(ho_renderer::Input::kKEY_S);
          break;
        case VK_D:
          input_sender_.KeyPressed(ho_renderer::Input::kKEY_D);
          break;
      }
      break;
    case WM_KEYUP:
      // send input
      switch (wParam) {
        case VK_F1:
          input_sender_.KeyReleased(ho_renderer::Input::kKEY_F1);
          break;
        case VK_F2:
          input_sender_.KeyReleased(ho_renderer::Input::kKEY_F2);
          break;
        case VK_F3:
          input_sender_.KeyReleased(ho_renderer::Input::kKEY_F3);
          break;
        case VK_F4:
          input_sender_.KeyReleased(ho_renderer::Input::kKEY_F4);
          break;
        case VK_F5:
          input_sender_.KeyReleased(ho_renderer::Input::kKEY_F5);
          break;
        case VK_F6:
          input_sender_.KeyReleased(ho_renderer::Input::kKEY_F6);
          break;
        case VK_F7:
          input_sender_.KeyReleased(ho_renderer::Input::kKEY_F7);
          break;
        case VK_F8:
          input_sender_.KeyReleased(ho_renderer::Input::kKEY_F8);
          break;
        case VK_F9:
          input_sender_.KeyReleased(ho_renderer::Input::kKEY_F9);
          break;
        case VK_NUM_0:
          input_sender_.KeyReleased(ho_renderer::Input::kKEY_NUM_0);
          break;
        case VK_NUM_1:
          input_sender_.KeyReleased(ho_renderer::Input::kKEY_NUM_1);
          break;
        case VK_NUM_2:
          input_sender_.KeyReleased(ho_renderer::Input::kKEY_NUM_2);
          break;
        case VK_NUM_3:
          input_sender_.KeyReleased(ho_renderer::Input::kKEY_NUM_3);
          break;
        case VK_NUM_4:
          input_sender_.KeyReleased(ho_renderer::Input::kKEY_NUM_4);
          break;
        case VK_NUM_5:
          input_sender_.KeyReleased(ho_renderer::Input::kKEY_NUM_5);
          break;
        case VK_NUM_6:
          input_sender_.KeyReleased(ho_renderer::Input::kKEY_NUM_6);
          break;
        case VK_NUM_7:
          input_sender_.KeyReleased(ho_renderer::Input::kKEY_NUM_7);
          break;
        case VK_NUM_8:
          input_sender_.KeyReleased(ho_renderer::Input::kKEY_NUM_8);
          break;
        case VK_NUM_9:
          input_sender_.KeyReleased(ho_renderer::Input::kKEY_NUM_9);
          break;
        case VK_LEFT:
          input_sender_.KeyReleased(ho_renderer::Input::kKEY_LEFT);
          break;
        case VK_RIGHT:
          input_sender_.KeyReleased(ho_renderer::Input::kKEY_RIGHT);
          break;
        case VK_UP:
          input_sender_.KeyReleased(ho_renderer::Input::kKEY_UP);
          break;
        case VK_DOWN:
          input_sender_.KeyReleased(ho_renderer::Input::kKEY_DOWN);
          break;
        case VK_DELETE:
          input_sender_.KeyReleased(ho_renderer::Input::kKEY_DELETE);
          break;
        case VK_NEXT:
          input_sender_.KeyReleased(ho_renderer::Input::kKEY_PAGEDOWN);
          break;
        case VK_Q:
          input_sender_.KeyReleased(ho_renderer::Input::kKEY_Q);
          break;
        case VK_W:
          input_sender_.KeyReleased(ho_renderer::Input::kKEY_W);
          break;
        case VK_E:
          input_sender_.KeyReleased(ho_renderer::Input::kKEY_E);
          break;
        case VK_A:
          input_sender_.KeyReleased(ho_renderer::Input::kKEY_A);
          break;
        case VK_S:
          input_sender_.KeyReleased(ho_renderer::Input::kKEY_S);
          break;
        case VK_D:
          input_sender_.KeyReleased(ho_renderer::Input::kKEY_D);
          break;
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