#include "error.h"

namespace t9::win32 {

// ErrorString.
ErrorString::ErrorString(nullptr_t) {}
ErrorString::ErrorString(LPVOID p) : buf_(p) {}

/*static*/ ErrorString ErrorString::from_code(DWORD code) {
  LPVOID p = nullptr;
  FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
                    FORMAT_MESSAGE_IGNORE_INSERTS,
                nullptr, code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                reinterpret_cast<LPTSTR>(&p), 0, nullptr);
  if (!p) return nullptr;
  return ErrorString(p);
}

}  // namespace t9::win32