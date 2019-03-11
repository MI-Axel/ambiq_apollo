/* this file contains system ram management functions */

#include "am_app_utils_syscall.h"


void * _sbrk(int32_t incr)
{
    extern char   end; /* Set by linker.  */
    static char * heap_end = &end;
    char *        prev_heap_end;
    
    if (heap_end == 0) {
        heap_end = & end;
    }

    prev_heap_end = heap_end;
    heap_end += incr;

    // RAM limit check
    configASSERT((uint32_t)heap_end < AM_PART_RAM_LIMIT);

#if AM_MEMORY_DEBUG
    am_util_stdio_printf("_sbrk: Growing memory pool by %d bytes. New span is 0x%X-0x%X (%d bytes)\r\n",
                            incr,
                            (uint32_t)(& end),
                            (uint32_t)(heap_end),
                            (uint32_t)(heap_end) - (uint32_t)(& end));
#endif // AM_MEMORY_DEBUG

    return (void *) prev_heap_end;
}

#if APP_IN_FreeRTOS

void* am_alloc(size_t size)
{
    return pvPortMalloc(size);
}

void* am_free(void* ptr)
{
    vPortFree(ptr);
}

#else
void* am_alloc(size_t size)
{
    return malloc(size);
}

void am_free(void* ptr)
{
    free(ptr);
}

#endif // APP_IN_FreeRTOS
