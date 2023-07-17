if defined __cplusplus

    #define _CRT_BEGIN_C_HEADER            \
        __pragma(pack(push, _CRT_PACKING)) \
        extern "C" {

    #define _CRT_END_C_HEADER \
        }                     \
        __pragma(pack(pop))
#else

    #define _CRT_BEGIN_C_HEADER            \
        __pragma(pack(push, _CRT_PACKING))

    #define _CRT_END_C_HEADER \
        __pragma(pack(pop))

#endif

#if !defined (CT_BEGIN_NAMESPACES) && !defined (CT_END_NAMESPACES)
#define CT_BEGIN_NAMESPACES namespace CT {
#define CT_END_NAMESPACES }
#endif

