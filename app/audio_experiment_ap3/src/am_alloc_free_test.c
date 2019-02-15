#include "am_alloc_free_test.h"

void print_mallinfo() {
        struct mallinfo info = mallinfo();
        am_util_stdio_printf("mallinfo: \r\n\
                        arena:\t\t%d\t(total space in heap)\r\n\
                        ordblks:\t%d\t(number of chunks not in use)\r\n\
                        uordblks:\t%d\t(total amount of space allocated by malloc)\r\n\
                        fordblks:\t%d\t(total amount of space not in use)\r\n\
                        keepcost:\t%d\t(size of topmost memory block)\r\n",
                        info.arena,
                        info.ordblks,
                        info.uordblks,
                        info.fordblks,
                        info.keepcost);
}

void am_alloc_free_test(void) 
{
    print_mallinfo();

    DebugLog("\nAllocating 32K bytes\r\n");
    uint8_t *bytes1 = (uint8_t*)malloc(32000);
    print_mallinfo();

    DebugLog("\nAllocating 16 bytes\r\n");
    uint8_t *bytes2 = (uint8_t*)malloc(16);
    print_mallinfo();

    DebugLog("\nAllocating 64 bytes\r\n");
    uint8_t *bytes3 = (uint8_t*)malloc(64);
    print_mallinfo();

    DebugLog("\nFreeing second allocation of 16 bytes\r\n");
    free(bytes2);
    print_mallinfo();

    DebugLog("\nAllocating 16 bytes again\r\n");
    bytes2 = (uint8_t*)malloc(16);
    print_mallinfo();

    DebugLog("\nFreeing 16 byte allocation again\r\n");
    free(bytes2);
    print_mallinfo();

    DebugLog("\nAllocating 64 bytes\r\n");
    bytes3 = (uint8_t*)malloc(64);
    print_mallinfo();

    DebugLog("\nFreeing first 32 byte allocation\r\n");
    free(bytes1);
    print_mallinfo();

}
