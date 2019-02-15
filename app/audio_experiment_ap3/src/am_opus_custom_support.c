/* this file contains optimized function needed by opus */

#include "custom_support.h"

void vPortFree(void* ptr)
{
    free(ptr);
}
