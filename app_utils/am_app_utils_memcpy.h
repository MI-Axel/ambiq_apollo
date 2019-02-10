#ifndef AM_APP_UTILS_MEMCPY_H
#define AM_APP_UTILS_MEMCPY_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

extern void sysFastMemCopy( uint8_t *pDest, uint8_t *pSrc, uint32_t len );

#define MEMCOPY(pDst,pSrc,len) \
      (len) < 16 ? memcpy(pDst,pSrc,len) : sysFastMemCopy(pDst,pSrc,len);


















#endif
