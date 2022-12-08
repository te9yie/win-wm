#include "t9/win32/error.h"

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
  const auto CLASS_NAME = TEXT("windowclassname");
  const auto WINDOW_NAME = TEXT("Window Manager");

  hello();

  WNDCLASSEX wcex;
  ZeroMemory(&wcex, sizeof(wcex));
  wcex.cbSize = sizeof(wcex);
  wcex.lpfnWndProc = window_proc;
  wcex.hInstance = hInstance;
  wcex.lpszClassName = CLASS_NAME;

  auto atom = RegisterClassEx(&wcex);
  if (!atom) {
    auto error_code = GetLastError();
    auto message = t9::win32::ErrorString::from_code(error_code);
    OutputDebugString(message.c_str());
    MessageBox(0, message.c_str(), TEXT("Error"), MB_OK | MB_ICONERROR);
    return 0;
  }

  auto hWnd = CreateWindowEx(
      0, CLASS_NAME,  // reinterpret_cast<LPCTSTR>(MAKELONG(atom, 0)),
      WINDOW_NAME, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
      CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, hInstance, nullptr);
  if (!hWnd) {
    auto error_code = GetLastError();
    auto message = t9::win32::ErrorString::from_code(error_code);
    OutputDebugString(message.c_str());
    MessageBox(0, message.c_str(), TEXT("Error"), MB_OK | MB_ICONERROR);
    return 0;
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
