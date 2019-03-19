/*
 * File      : sensorytypes.h
 * Purpose   : typedefs and code/data section definitions
 * Project   : any 
 * Platform  : PC simulation of VPC and CSR code 
 *
 * Copyright (C) 2007-2015 Sensory Inc., All Rights Reserved
 *
 * ******* SENSORY CONFIDENTIAL *************
 *
 *****************************************************************************
 */
#ifndef SENSORYTYPES_H_INCLUDED
#define SENSORYTYPES_H_INCLUDED

// define for Sensory logging feature
#define SENSORY_LOGGING

#ifndef BOOL
typedef unsigned char       BOOL;
#endif

// note: UINT, SINT these types are deprecated and only used in tsliceSimPC 
typedef unsigned char       UINT8;   
typedef unsigned short int  UINT16;  
typedef unsigned long int   UINT24;  
typedef unsigned long int   UINT32;  
typedef char                SINT8;   
typedef short int           SINT16;  
typedef long int            SINT24;  
typedef long int            SINT32;  

typedef unsigned char       bool;
typedef unsigned char       b08;  
typedef unsigned short int  b16;  
typedef unsigned long int   b24;  
typedef unsigned long int   b32;  
typedef unsigned char       u08;  
typedef unsigned short int  u16;  
typedef unsigned long int   u24;  
typedef unsigned long int   u32;  
typedef char                s08;  
typedef short int           s16;  
typedef long int            s24;  
typedef long int            s32;  
#ifdef RUNONPC
typedef _int64              s48;
#else 
typedef long long           s48;
#endif

// type needed when doing ptr + offset arithmetic to create ptr 
typedef int                INTFORPTR;

// types needed for C nets and grammars
#ifndef __nn_t
typedef const u16  __nn_t;
#endif

#ifndef __gs_t
typedef const u16  __gs_t;
#endif

#ifndef NULL
#define NULL  (void *) 0
#endif

// needed for compatibility with VPC
#define UCODE
#define IRAM
#define IRAM1
#define RDATA const
#define NDATA const         
#define CONST const

// limits
#define UINT16_MAX (~(~0<<16))
#define INT16_MAX (~(~0<<15))

//----------- platform-specific memory sizes

#define FFT_BUFFER_LEN  512
#define TMP_BUFFER_LEN  240  // 144 will skip first 96 samples of first frame

//----------- platform-specific options for generating debug info 

#define SAVE_SAMPLES      0  // 1 = store microphone samples for review

//----------- debug output defs

#define Trace(x)

#define FDEBUG_FILE     "pcfrontend.dbg"
#define SDEBUG_FILE     "pcsearch.dbg"
#define NDEBUG_FILE     "pcnnet.dbg"

#endif // SENSORYTYPES_H_INCLUDED

