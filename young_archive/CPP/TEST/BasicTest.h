/////////////////////////////////////////////////////////////////////////////////
// basic testing

#define eq(a, b) \
    if ((a) == (b)) success("equal"); \
    else error("test equal failed")

#define neq(a, b) if ((a) != (b)) success("not equal"); \
    else error("test not equal failed")

#define expectT(condition) if (condition) success("expect true"); \
    else error("expect true")

#define expectF(condition) if (!(condition)) success("expect false"); \
    else error("expect false")

#define notNull(obj) if ((obj) != NULL) success("no zero"); \
    else error("no zero")

/////////////////////////////////////////////////////////////////////////////////
// almost precision testing

#define almost_eq_precision(a, b, eps) \
    if (fabs((a)-(b))<eps) success(join("almost equal with precision ", eps));\
    else error(join("almost equal with precision ", eps))

#define almost_eq(a, b) \
    if (fabs((a)-(b))<0.0001) success("almost equal with precision 0.0001");\
    else error("almost equal with precision 0.0001")

/////////////////////////////////////////////////////////////////////////////////
// array testing

#define arr_eq(arrA, arrB, len) \
    bool __arrA##arrB_eq__ = true; \
    for (size_t i=0; i<len; i++) { \
        if (arrA[i] != arrB[i]) { __arrA##arrB_eq__ = false; break;} \
    } \
    if (__arrA##arrB_eq__) success("array equal"); else error("array equal")

#define arr_neq(arrA, arrB, len) \
    bool __arrA##arrB_neq__ = true; \
    for (size_t i=0; i<len; i++) { \
        if (arrA[i] != arrB[i]) { __arrA##arrB_neq__ = false; break;} \
    } \
    if (!__arrA##arrB_neq__) success("array not equal"); else error("array not equal")

#define arr_almost_eq(arrA, arrB, len) \
    bool __arrA##arrB_almost_eq__ = true; \
    for (size_t i=0; i<len; i++) { \
        if (fabs(arrA[i] - arrB[i])>0.0001) { __arrA##arrB_almost_eq__ = false; break;} \
    } \
    if (__arrA##arrB_almost_eq__) success("array almost equal with precision 0.0001");\
    else error("array almost equal with precision 0.0001")

#define arr_almost_eq_precision(arrA, arrB, len, precision) \
    bool __arrA##arrB_almost_eq_precision__ = true; \
    for (size_t i=0; i<len; i++) { \
        if (fabs(arrA[i] - arrB[i])>precision) { __arrA##arrB_almost_eq_precision__ = false; break;} \
    } \
    if (__arrA##arrB_almost_eq_precision__) success(join("array almost equal with precision ", precision));\
    else error(join("array almost equal with precision ", precision))

/////////////////////////////////////////////////////////////////////////////////
// exception testing

#define with_exception_start() try

#define with_exception_end(e) \
    catch (e err) { \
        success(join("with exception ", e));} \
    catch(...) { \
        error(join("with exception ", e)); \
    }
