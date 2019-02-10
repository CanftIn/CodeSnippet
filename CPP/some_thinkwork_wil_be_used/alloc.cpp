#ifndef CT_THROW_BAD_ALLOC
#define CT_THROW_BAD_ALLOC fprintf(stderr, "out of memory\n"); exit(1);
#endif

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

template<int inst>
class malloc_alloc_template
{
private:
    static void *oom_malloc(size_t);
    
};