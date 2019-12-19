/* ----------------------------------------------------------------------
** Standard Audio Weaver data types
** ------------------------------------------------------------------- */

#ifndef STANDARD_DEFS_H_
#define STANDARD_DEFS_H_

#ifndef UINT32
//#define UINT32 unsigned int
typedef unsigned int UINT32;
#endif

#ifndef INT32
//#define INT32 int
typedef int INT32;
#endif

#ifdef __ADSP215xx__
#ifndef BOOL
#define BOOL bool
#endif
#else
#ifndef BOOL
#define BOOL INT32
#endif
#endif

#ifndef MAXINT32
#define MAXINT32 ((INT32)0x7fffffffUL)
#endif

#ifndef MININT32
#define MININT32 ((INT32)~MAXINT32)
#endif

#ifndef INT64
//#define INT64 long long
typedef long long INT64;
#endif

#ifndef MAXINT64
#define MAXINT64 ((INT64)0x7ffffffffffffffffULL)
#endif

#ifndef MININT64
#define MININT64 ((INT64)~MAXINT64)
#endif

#ifndef FLOAT32
//#define FLOAT32 float
typedef float FLOAT32;
#endif

#ifndef INT16
//#define INT16 short
typedef short INT16;
#endif

#ifndef UINT16
//#define UINT16 unsigned short
typedef unsigned short UINT16;
#endif

#ifndef INT8
//#define INT8 signed char
typedef signed char INT8;
#endif

#ifndef UINT8
//#define UINT8 unsigned char
typedef unsigned char UINT8;
#endif

/* These definitions on needed for Linux */
#ifndef INT
//#define INT int
typedef int INT;
#endif

#ifndef UINT
#define UINT unsigned int
#endif

#ifndef BYTE
//#define BYTE unsigned char
typedef unsigned char BYTE;
#endif

#ifndef PBYTE
#define PBYTE unsigned char *
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef WORD
#define WORD unsigned short
#endif

#ifndef PWORD
#define PWORD unsigned short *
#endif

#ifndef DWORD
#define DWORD unsigned long
#endif

#ifndef PDWORD
#define PDWORD unsigned long *
#endif

#endif // STANDARD_DEFS_H_
