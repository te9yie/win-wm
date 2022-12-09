#pragma once
#include "../result.h"
#include "config.h"

namespace t9::win32 {

/// @brief WNDCLASSEXのラッパー
class WindowClass {
 public:
  using Self = WindowClass;

 private:
  WNDCLASSEX wcex_;

 public:
  WindowClass(WNDPROC lpfnWndProc, HINSTANCE hInstance, LPCTSTR lpszClassName) {
    reset_();
    wcex_.lpfnWndProc = lpfnWndProc;
    wcex_.hInstance = hInstance;
    wcex_.lpszClassName = lpszClassName;
  }

  // clang-format off
  Self& style(UINT value) { wcex_.style = value; return *this; }
  Self& class_extra(int value) { wcex_.cbClsExtra = value; return *this; }
  Self& window_extra(int value) { wcex_.cbWndExtra = value; return *this; }
  Self& icon(HICON value) { wcex_.hIcon = value; return *this; }
  Self& curosr(HCURSOR value) { wcex_.hCursor = value; return *this; }
  Self& background(HBRUSH value) { wcex_.hbrBackground = value; return *this; }
  Self& menu_name(LPCWSTR value) { wcex_.lpszMenuName = value; return *this; }
  Self& icon_small(HICON value) { wcex_.hIconSm = value; return *this; }
  // clang-format on

  Result<ATOM> build() {
    auto atom = RegisterClassEx(&wcex_);
    if (!atom) return none;
    return atom;
  }

 private:
  void reset_() {
    ZeroMemory(&wcex_, sizeof(wcex_));
    wcex_.cbSize = sizeof(wcex_);
    wcex_.hCursor = LoadCursor(0, IDC_ARROW);
    wcex_.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW);
  }
};

/// @brief Window構築
class WindowBuilder {
 public:
  using Self = WindowBuilder;

 private:
  DWORD dwExStyle_ = 0;
  LPCTSTR lpClassName_ = nullptr;
  LPCTSTR lpWindowName_ = nullptr;
  DWORD dwStyle_ = 0;
  int x_ = CW_USEDEFAULT;
  int y_ = CW_USEDEFAULT;
  int nWidth_ = CW_USEDEFAULT;
  int nHeight_ = CW_USEDEFAULT;
  HWND hWndParent_ = 0;
  HMENU hMenu_ = 0;
  HINSTANCE hInstance_ = 0;
  LPVOID lpParam_ = nullptr;

 public:
  WindowBuilder(LPCTSTR lpClassName, LPCTSTR lpWindowName, HINSTANCE hInstance)
      : lpClassName_(lpClassName),
        lpWindowName_(lpWindowName),
        dwStyle_(WS_OVERLAPPEDWINDOW),
        hInstance_(hInstance) {}

  // clang-format off
  Self& ex_style(DWORD value) { dwExStyle_ = value; return *this; }
  Self& style(DWORD value) { dwStyle_ = value; return *this; }
  Self& x(int value) { x_ = value; return *this; }
  Self& y(int value) { y_ = value; return *this; }
  Self& width(int value) { nWidth_ = value; return *this; }
  Self& height(int value) { nHeight_ = value; return *this; }
  Self& parent(HWND value) { hWndParent_ = value; return *this; }
  Self& menu(HMENU value) { hMenu_ = value; return *this; }
  Self& param(LPVOID value) { lpParam_ = value; return *this; }
  // clang-format on

  Result<HWND> build() {
    auto hWnd = CreateWindowEx(dwExStyle_, lpClassName_, lpWindowName_,
                               dwStyle_, x_, y_, nWidth_, nHeight_, hWndParent_,
                               hMenu_, hInstance_, lpParam_);
    return hWnd;
  }
};

}  // namespace t9::win32
