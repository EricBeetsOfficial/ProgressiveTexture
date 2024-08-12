#if defined(__CYGWIN32__)
    #define INTERFACE_API __stdcall
    #define INTERFACE_EXPORT __declspec(dllexport)
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN64) || defined(WINAPI_FAMILY)
    #define INTERFACE_API __stdcall
    #define INTERFACE_EXPORT __declspec(dllexport)
#elif defined(__MACH__) || defined(__ANDROID__) || defined(__linux__) || defined(LUMIN)
    #define INTERFACE_API
    #define INTERFACE_EXPORT __attribute__ ((visibility ("default")))
#else
    #define INTERFACE_API
    #define INTERFACE_EXPORT
#endif