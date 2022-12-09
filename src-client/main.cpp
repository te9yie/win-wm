#include "t9/win32/prelude.h"

enum {
  WM_TASKTRAY = WM_APP + 100,
};

LRESULT CALLBACK window_proc(HWND hWnd, UINT uMsg, WPARAM wParam,
                             LPARAM lParam) {
  switch (uMsg) {
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
    default:
      break;
  }
  return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE /*hPrevInstance*/,
                     _In_ LPTSTR /*lpCmdLine*/, _In_ int nCmdShow) {
  const LPTSTR CLASS_NAME = TEXT("windowclassname");
  const LPTSTR WINDOW_NAME = TEXT("Window Manager");

  hello();

  {
    auto r = t9::win32::WindowClass(window_proc, hInstance, CLASS_NAME).build();
    if (!r) {
      auto error_code = GetLastError();
      auto message = t9::win32::ErrorString::from_code(error_code);
      OutputDebugString(message.c_str());
      MessageBox(0, message.c_str(), TEXT("Error"), MB_OK | MB_ICONERROR);
      return 0;
    }
  }

  HWND hWnd = 0;
  {
    auto r =
        t9::win32::WindowBuilder(CLASS_NAME, WINDOW_NAME, hInstance).build();
    if (!r) {
      auto error_code = GetLastError();
      auto message = t9::win32::ErrorString::from_code(error_code);
      OutputDebugString(message.c_str());
      MessageBox(0, message.c_str(), TEXT("Error"), MB_OK | MB_ICONERROR);
      return 0;
    }
    hWnd = r.unwrap();
  }

  ShowWindow(hWnd, nCmdShow);

  {
    MSG msg;
    BOOL r;
    while ((r = GetMessage(&msg, nullptr, 0, 0)) != 0) {
      if (r > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
      }
    }
  }

  return 0;
}
