
// All C headers have a common prologue and epilogue, to enclose the header in
// an extern "C" declaration when the header is #included in a C++ translation
// unit and to push/pop the packing.
#if defined __cplusplus

    #define _CRT_BEGIN_C_HEADER            \
        __pragma(pack(push, _CRT_PACKING)) \
        extern "C" {

    #define _CRT_END_C_HEADER \
        }                     \
        __pragma(pack(pop))

#elif defined __midl

    #define _CRT_BEGIN_C_HEADER                         \
        cpp_quote("__pragma(pack(push, _CRT_PACKING))") \
        cpp_quote("extern \"C\" {")

    #define _CRT_END_C_HEADER            \
        cpp_quote("}")                   \
        cpp_quote("__pragma(pack(pop))")

#else

    #define _CRT_BEGIN_C_HEADER            \
        __pragma(pack(push, _CRT_PACKING))

    #define _CRT_END_C_HEADER \
        __pragma(pack(pop))

#endif

_CRT_BEGIN_C_HEADER
----------------------------
#define _CRT_WARNING(description)                   \
    message("" __FILE__ "(" _CRT_STRINGIZE(__LINE__) ") : warning CRT0000 : " _CRT_STRINGIZE(description))











