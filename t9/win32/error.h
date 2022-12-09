#pragma once
#include "config.h"

namespace t9::win32 {

/// @brief エラー文字列
class ErrorString {
 private:
  // Drop.
  struct Drop {
    void operator()(HLOCAL p) const { LocalFree(p); }
  };
  using Buf = std::unique_ptr<std::remove_pointer_t<HLOCAL>, Drop>;

 private:
  Buf buf_;

 public:
  ErrorString(nullptr_t);
  ErrorString(LPVOID p);

  LPTSTR c_str() const { return reinterpret_cast<LPTSTR>(buf_.get()); }

 public:
  /// @brief エラーコードから文字列への変換
  static ErrorString from_code(DWORD code);
};

}  // namespace t9::win32