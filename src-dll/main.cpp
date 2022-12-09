#define DLL_EXPORT
#include "export.h"

void hello() { OutputDebugString(TEXT("HELLO\n")); }

BOOL WINAPI DllMain(_In_ HMODULE /*hinstDLL*/, _In_ DWORD /*fdwReason*/,
                    _In_ LPVOID /*lpvReserved*/) {
  return TRUE;
}
