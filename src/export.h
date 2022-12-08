#pragma once
#ifdef DLL_EXPORT
#define DECL_SPEC __declspec(dllexport)
#else
#define DECL_SPEC
#endif

#ifdef __cplusplus
extern "C" {
#endif

DECL_SPEC void hello();

#ifdef __cplusplus
}
#endif
