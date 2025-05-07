#include <stdlib.h>
#include <wchar.h>
#include <windows.h>

#include "tools/include/debug.h"
#include "windows/include/windows_app.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpszCmdParam, int nCmdShow) {
  WindowsApp app(hInstance, 600, 600);
#ifdef DEBUG
  app.CreateDebugConsole();
#endif
  app.InitializeApp(hInstance, nCmdShow, "HO RENDERER");
  while (app.IsRunning()) {
    MSG Message;
    app.ProcessMessages(Message);
    app.Run();
  }
  app.Quit();
#ifdef DEBUG
  FreeConsole();
#endif
}
