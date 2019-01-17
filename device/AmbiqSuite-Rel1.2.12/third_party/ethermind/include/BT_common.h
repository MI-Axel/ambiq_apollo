
/**
 *  \file BT_common.h
 *
 *  \brief This Header file describes common declarations for the
 *  BlueLitE Stack & Profile modules.
 */

/*
 *  Copyright (C) 2014. Mindtree Ltd.
 *  All rights reserved.
 */

#ifndef _H_BT_COMMON_
#define _H_BT_COMMON_

/**
 * \defgroup bt_common_module BT Common
 * \{
 */

/* -------------------------------------------- Header File Inclusion */

/* The EtherMind OS Abstraction */
#include "BT_os.h"

/* The EtherMind Tunable Constant */
#include "BT_limits.h"

/* The Bluetooth Assigned Numbers */
#include "BT_assigned_numbers.h"

/* The EtherMind Error Codes */
#include "BT_error.h"

/* The EtherMind Debug Library */
#include "BT_debug.h"

/* For BT_assert() macro */
#include "BT_assert.h"

/* For Status Flag APIs */
#include "BT_status.h"

#ifdef BT_RACP
/* For RACP APIs */
#include "BT_racp.h"
#endif /* BT_RACP */

/* For btsnoop APIs */
#include "BT_snoop.h"

/* The EtherMind Timer Library */
#include "BT_timer.h"

/* The EtherMind Write Task */
#include "write_task.h"

/* EtherMind Platform Specific Initialization & Shutdown Handlers */
#include "BT_common_pl.h"

#ifdef BT_STORAGE
#include "BT_storage.h"
#endif /* BT_STORAGE */

/* For Memory (leak, corruption) Testing */
#ifdef MEMWATCH
    #include "memwatch.h"
#endif /* MEMWATCH */


/* -------------------------------------------- Global Definitions */

/**
 * \cond ignore_this
 * \{
 */

/* COMMON Debug Macros */
#ifndef COMMON_NO_DEBUG
#define COMMON_ERR(module_id, ...)          BT_debug_error((module_id), __VA_ARGS__)
#else   /* COMMON_NO_DEBUG */
#define COMMON_ERR               BT_debug_null
#endif  /* COMMON_NO_DEBUG */

#ifdef COMMON_DEBUG

#define COMMON_TRC(module_id, ...)          BT_debug_trace((module_id), __VA_ARGS__)
#define COMMON_INF(module_id, ...)          BT_debug_info((module_id), __VA_ARGS__)

#else /* COMMON_DEBUG */

#define COMMON_TRC               BT_debug_null
#define COMMON_INF               BT_debug_null

#endif /* COMMON_DEBUG */

/** \endcond */

/**
 * \defgroup bt_common_defines Defines
 * \{
 */

/**
 * \defgroup bt_common_constants Constants
 * \{
 */

/**
 * \defgroup bt_common_stack_init_states Stack Init States
 * \{
 */

#define STACK_INIT_UNDEFINED                0x00
#define STACK_INIT_ETHERMIND_INIT           0x01
#define STACK_INIT_BT_ON_STARTED            0x02
#define STACK_INIT_BT_ON_COMPLETE           0x03

/** \} */

/* Definition for True/False */
#ifndef BT_FALSE
#define BT_FALSE                                   0
#endif /* BT_FALSE */

#ifndef BT_TRUE
#define BT_TRUE                                    1
#endif /* BT_TRUE */

/* Size of Bluetooth Device Address (BD_ADDR) in number of Octets */
#define BT_BD_ADDR_SIZE                         6
#define BT_BD_ADDR_TYPE_SIZE                    1
#define BT_BD_DEV_ADDR_SIZE                     (BT_BD_ADDR_SIZE + BT_BD_ADDR_TYPE_SIZE)

/* Type Definitions for 16, 32 & 128-bit UUIDs */
#define UUID_16                                 1
#define UUID_32                                 2
#define UUID_128                                4

/* Bluetooth Device Address type masks */
#define BT_RANDOM_ADDR_TYPE_MASK                0xC0
#define BT_STATIC_ADDR_BIT_MASK                 0xC0
#define BT_NON_RESOLV_PVT_ADDR_BIT_MASK         0x00
#define BT_RESOLV_PVT_ADDR_BIT_MASK             0x40

/** \} */

/** \} */

/* -------------------------------------------- Macros */

/**
 * \defgroup bt_common_utility_macros Utility Macros
 * \{
 */

/**
 *  Packing Macros.
 *
 *  Syntax: BT_PACK_<Endian-ness LE/BE>_<no_of_bytes>_BYTE
 *
 *  Usage: Based on the endian-ness defined for each protocol/profile layer,
 *  appropriate packing macros to be used by each layer.
 *
 *  Example: HCI is defined as little endian protocol,
 *  so if HCI defines HCI_PACK_2_BYTE for packing a parameter of size 2 byte,
 *  that shall be mapped to BT_PACK_LE_2_BYTE
 *
 *  By default both the packing and unpaking macros uses pointer to
 *  a single or multi-octet variable which to be packed to or unpacked from
 *  a buffer (unsinged character array).
 *
 *  For the packing macro, another variation is available,
 *  where the single or multi-octet variable itself is used (not its pointer).
 *
 *  Syntax: BT_PACK_<Endian-ness LE/BE>_<no_of_bytes>_BYTE_VAL
 */

/* Little Endian Packing Macros */
#define BT_PACK_LE_1_BYTE(dst, src) \
    { \
        UCHAR val; \
        val = (UCHAR)(*(src)); \
        BT_PACK_LE_1_BYTE_VAL((dst), val); \
    }

#define BT_PACK_LE_1_BYTE_VAL(dst, src) \
    *((UCHAR *)(dst) + 0) = (src);

#define BT_PACK_LE_2_BYTE(dst, src) \
    { \
        UINT16 val; \
        val = (UINT16)(*(src)); \
        BT_PACK_LE_2_BYTE_VAL((dst), val); \
    }

#define BT_PACK_LE_2_BYTE_VAL(dst, src) \
    *((UCHAR *)(dst) + 0) = (UCHAR)(src); \
    *((UCHAR *)(dst) + 1) = (UCHAR)((src) >> 8);

#define BT_PACK_LE_3_BYTE(dst, src) \
    { \
        UINT32 val; \
        val = (UINT32)(*(src)); \
        BT_PACK_LE_3_BYTE_VAL((dst), val); \
    }

#define BT_PACK_LE_3_BYTE_VAL(dst, src) \
    *((UCHAR *)(dst) + 0) = (UCHAR)(src);\
    *((UCHAR *)(dst) + 1) = (UCHAR)((src) >> 8);\
    *((UCHAR *)(dst) + 2) = (UCHAR)((src) >> 16);

#define BT_PACK_LE_4_BYTE(dst, src) \
    { \
        UINT32 val; \
        val = (UINT32)(*(src)); \
        BT_PACK_LE_4_BYTE_VAL((dst), val); \
    }

#define BT_PACK_LE_4_BYTE_VAL(dst, src) \
    *((UCHAR *)(dst) + 0) = (UCHAR)(src);\
    *((UCHAR *)(dst) + 1) = (UCHAR)((src) >> 8);\
    *((UCHAR *)(dst) + 2) = (UCHAR)((src) >> 16);\
    *((UCHAR *)(dst) + 3) = (UCHAR)((src) >> 24);

/* TBD: Update based on 64 Bit, 128 Bit Data Types */
#define BT_PACK_LE_8_BYTE(dst,val)\
        BT_mem_copy ((dst), (val), 8)

#define BT_PACK_LE_16_BYTE(dst,val)\
        BT_mem_copy ((dst), (val), 16)

#define BT_PACK_LE_N_BYTE(dst,val,n)\
        BT_mem_copy ((dst), (val), (n))

/* Big Endian Packing Macros */
#define BT_PACK_BE_1_BYTE(dst, src) \
    { \
        UCHAR val; \
        val = (UCHAR)(*((UCHAR *)(src))); \
        BT_PACK_BE_1_BYTE_VAL((dst), val); \
    }

#define BT_PACK_BE_1_BYTE_VAL(dst, src) \
    *((UCHAR *)(dst) + 0) = (src);

#define BT_PACK_BE_2_BYTE(dst, src) \
    { \
        UINT16 val; \
        val = (UINT16)(*((UINT16 *)(src))); \
        BT_PACK_BE_2_BYTE_VAL((dst), val); \
    }

#define BT_PACK_BE_2_BYTE_VAL(dst, src) \
    *((UCHAR *)(dst) + 1) = (UCHAR)(src); \
    *((UCHAR *)(dst) + 0) = (UCHAR)((src) >> 8);

#define BT_PACK_BE_3_BYTE(dst, src) \
    { \
        UINT32 val; \
        val = (UINT32)(*((UINT32 *)(src))); \
        BT_PACK_BE_3_BYTE_VAL((dst), val); \
    }

#define BT_PACK_BE_3_BYTE_VAL(dst, src) \
    *((UCHAR *)(dst) + 2) = (UCHAR)(src);\
    *((UCHAR *)(dst) + 1) = (UCHAR)((src) >> 8);\
    *((UCHAR *)(dst) + 0) = (UCHAR)((src) >> 16);

#define BT_PACK_BE_4_BYTE(dst, src) \
    { \
        UINT32 val; \
        val = (UINT32)(*((UINT32 *)(src))); \
        BT_PACK_BE_4_BYTE_VAL((dst), val); \
    }

#define BT_PACK_BE_4_BYTE_VAL(dst, src) \
    *((UCHAR *)(dst) + 3) = (UCHAR)(src);\
    *((UCHAR *)(dst) + 2) = (UCHAR)((src) >> 8);\
    *((UCHAR *)(dst) + 1) = (UCHAR)((src) >> 16);\
    *((UCHAR *)(dst) + 0) = (UCHAR)((src) >> 24);

/* TBD: Update based on 64 Bit, 128 Bit Data Types */
#define BT_PACK_BE_8_BYTE(dst,val)\
        BT_mem_copy ((dst), (val), 8)

#define BT_PACK_BE_16_BYTE(dst,val)\
        BT_mem_copy ((dst), (val), 16)

#define BT_PACK_BE_N_BYTE(dst,val,n)\
        BT_mem_copy ((dst), (val), (n))


/**
 *  Unpacking Macros.
 *
 *  Syntax: BT_UNPACK_<Endian-ness LE/BE>_<no_of_bytes>_BYTE
 *
 *  Usage: Based on the endian-ness defined for each protocol/profile layer,
 *  appropriate unpacking macros to be used by each layer.
 *
 *  Example: HCI is defined as little endian protocol,
 *  so if HCI defines HCI_UNPACK_4_BYTE for unpacking a parameter of size 4 byte,
 *  that shall be mapped to BT_UNPACK_LE_4_BYTE
 */

/* Little Endian Unpacking Macros */
#define BT_UNPACK_LE_1_BYTE(dst,src)\
    *((UCHAR *)(dst)) = (UCHAR)(*((UCHAR *)(src)));

#define BT_UNPACK_LE_2_BYTE(dst,src)\
        *((UINT16 *)(dst))  = *((src) + 1); \
        *((UINT16 *)(dst))  = *((UINT16 *)(dst)) << 8; \
        *((UINT16 *)(dst)) |= *((src) + 0);

#define BT_UNPACK_LE_3_BYTE(dst,src)\
        *((UINT32 *)(dst))  = *((src) + 2);\
        *((UINT32 *)(dst))  = (*((UINT32 *)(dst))) << 8;\
        *((UINT32 *)(dst)) |= *((src) + 1);\
        *((UINT32 *)(dst))  = (*((UINT32 *)(dst))) << 8;\
        *((UINT32 *)(dst)) |= *((src) + 0);

#define BT_UNPACK_LE_4_BYTE(dst,src)\
        *((UINT32 *)(dst))  = *((src) + 3);\
        *((UINT32 *)(dst))  = (*((UINT32 *)(dst))) << 8;\
        *((UINT32 *)(dst)) |= *((src) + 2);\
        *((UINT32 *)(dst))  = (*((UINT32 *)(dst))) << 8;\
        *((UINT32 *)(dst)) |= *((src) + 1);\
        *((UINT32 *)(dst))  = (*((UINT32 *)(dst))) << 8;\
        *((UINT32 *)(dst)) |= *((src) + 0);

/* TBD: Update based on 64 Bit, 128 Bit Data Types */
#define BT_UNPACK_LE_8_BYTE(dst,src)\
        BT_mem_copy ((dst), (src), 8)

#define BT_UNPACK_LE_16_BYTE(dst,src)\
        BT_mem_copy ((dst), (src), 16)

#define BT_UNPACK_LE_N_BYTE(dst,src,n)\
        BT_mem_copy ((dst), (src), (n))

/* Big Endian Unpacking Macros */
#define BT_UNPACK_BE_1_BYTE(dst,src)\
    *((UCHAR *)(dst)) = (UCHAR)(*((UCHAR *)(src)));

#define BT_UNPACK_BE_2_BYTE(dst,src)\
        *((UINT16 *)(dst))  = *((src) + 0); \
        *((UINT16 *)(dst))  = *((UINT16 *)(dst)) << 8; \
        *((UINT16 *)(dst)) |= *((src) + 1);

#define BT_UNPACK_BE_3_BYTE(dst,src)\
        *((UINT32 *)(dst))  = *((src) + 0);\
        *((UINT32 *)(dst))  = (*((UINT32 *)(dst))) << 8;\
        *((UINT32 *)(dst)) |= *((src) + 1);\
        *((UINT32 *)(dst))  = (*((UINT32 *)(dst))) << 8;\
        *((UINT32 *)(dst)) |= *((src) + 2);

#define BT_UNPACK_BE_4_BYTE(dst,src)\
        *((UINT32 *)(dst))  = *((src) + 0);\
        *((UINT32 *)(dst))  = (*((UINT32 *)(dst))) << 8;\
        *((UINT32 *)(dst)) |= *((src) + 1);\
        *((UINT32 *)(dst))  = (*((UINT32 *)(dst))) << 8;\
        *((UINT32 *)(dst)) |= *((src) + 2);\
        *((UINT32 *)(dst))  = (*((UINT32 *)(dst))) << 8;\
        *((UINT32 *)(dst)) |= *((src) + 3);

/* TBD: Update based on 64 Bit, 128 Bit Data Types */
#define BT_UNPACK_BE_8_BYTE(dst,src)\
        BT_mem_copy ((dst), (src), 8)

#define BT_UNPACK_BE_16_BYTE(dst,src)\
        BT_mem_copy ((dst), (src), 16)

#define BT_UNPACK_BE_N_BYTE(dst,src,n)\
        BT_mem_copy ((dst), (src), (n))

#define BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER\
       "ADDR: %02X:%02X:%02X:%02X:%02X:%02X"

#define BT_DEVICE_ADDR_ONLY_PRINT_STR(ref)\
        (ref)[0],(ref)[1],(ref)[2],(ref)[3],(ref)[4],(ref)[5]

#define BT_DEVICE_ADDR_FRMT_SPECIFIER\
        "ADDR: %02X:%02X:%02X:%02X:%02X:%02X, TYPE: %02X"

#define BT_DEVICE_ADDR_PRINT_STR(ref)\
        (ref)->addr[0],(ref)->addr[1],(ref)->addr[2],\
        (ref)->addr[3],(ref)->addr[4],(ref)->addr[5],\
        (ref)->type

/* Macro to Copy a BD_ADDR from a Source to Destination */
#define BT_COPY_BD_ADDR_AND_TYPE(dest,src)\
        BT_COPY_TYPE((dest)->type,(src)->type)\
        BT_COPY_BD_ADDR((dest)->addr,(src)->addr)

#define BT_COPY_TYPE(dest,src)\
        (dest) = (src);

#define BT_COMPARE_BD_ADDR_AND_TYPE(addr_a,addr_b)\
        ((BT_COMPARE_TYPE((addr_a)->type,(addr_b)->type)) &&\
         (BT_COMPARE_ADDR((addr_a)->addr,(addr_b)->addr)))

#define BT_COMPARE_TYPE(type_a,type_b)\
        (((type_a) == (type_b))?BT_TRUE:BT_FALSE)

#define BT_COMPARE_ADDR(addr_a,addr_b)\
        ((0 == BT_mem_cmp((addr_a), (addr_b), BT_BD_ADDR_SIZE))?BT_TRUE:BT_FALSE)

#define BT_INIT_BD_ADDR(bd_addr) \
        BT_mem_set ((bd_addr)->addr, 0, BT_BD_ADDR_SIZE); \
        (bd_addr)->type = BT_BD_PUBLIC_ADDRESS_TYPE

#define BT_BD_ADDR(bd_addr) (bd_addr)->addr
#define BT_BD_ADDR_TYPE(bd_addr) (bd_addr)->type

#define BT_COPY_BD_ADDR(dest, src) \
        BT_mem_copy ((dest), (src), BT_BD_ADDR_SIZE);

#define BT_BD_ADDR_IS_NON_ZERO(addr)\
        ((0x00 == (*((addr) + 0) | *((addr) + 1) | *((addr) + 2) | *((addr) + 3) | *((addr) + 4) | *((addr) + 5)))?\
        BT_FALSE:BT_TRUE)

/* Macros to check Bluetooth Device Address type */
#define BT_IS_BD_ADDR_PUBLIC(bd_addr) \
    (BT_BD_PUBLIC_ADDRESS_TYPE == (bd_addr)->type)

#define BT_IS_BD_ADDR_RANDOM(bd_addr) \
    (BT_BD_RANDOM_ADDRESS_TYPE == (bd_addr)->type)

#define BT_IS_BD_ADDR_STATIC(bd_addr) \
    ((BT_IS_BD_ADDR_RANDOM(bd_addr)) && \
     (BT_STATIC_ADDR_BIT_MASK == (BT_RANDOM_ADDR_TYPE_MASK & (bd_addr)->addr[5])))

#define BT_IS_BD_ADDR_NON_RESOLV_PRIVATE(bd_addr) \
    ((BT_IS_BD_ADDR_RANDOM(bd_addr)) && \
     (BT_NON_RESOLV_PVT_ADDR_BIT_MASK == (BT_RANDOM_ADDR_TYPE_MASK & (bd_addr)->addr[5])))

#define BT_IS_BD_ADDR_RESOLV_PRIVATE(bd_addr) \
    ((BT_IS_BD_ADDR_RANDOM(bd_addr)) && \
     (BT_RESOLV_PVT_ADDR_BIT_MASK == (BT_RANDOM_ADDR_TYPE_MASK & (bd_addr)->addr[5])))


#ifndef BT_DISABLE_MUTEX

/* Macro to define a Mutex Variable */
#define BT_DEFINE_MUTEX(mutex) BT_thread_mutex_type mutex;

/* Macro to define a Mutex Variable with a type qualifier */
#define BT_DEFINE_MUTEX_TYPE(type, mutex) type BT_thread_mutex_type mutex;

/* Macro to define a Conditional Variable */
#define BT_DEFINE_COND(cond) BT_thread_cond_type cond;

/* Macro to define a Conditional Variable with a type qualifier */
#define BT_DEFINE_COND_TYPE(type, cond) type BT_thread_cond_type cond;

/*
 *  Macro to Initialize Mutex.
 *  To be used in void function as it returns no error.
 */
#define BT_MUTEX_INIT_VOID(mutex, MODULE)                                \
    if (BT_thread_mutex_init(&(mutex), NULL) < 0)                        \
    {                                                                    \
        COMMON_ERR(                                                      \
        BT_MODULE_ID_##MODULE,                                           \
        "FAILED to Initialize Mutex in " #MODULE ".\n");                 \
        return;                                                          \
    }

/*
 *  Macro to Initialize Mutex.
 *  It returns an error if mutex initialization fails.
 */
#define BT_MUTEX_INIT(mutex, MODULE)                                     \
    if (BT_thread_mutex_init(&(mutex), NULL) < 0)                        \
    {                                                                    \
        COMMON_ERR(                                                      \
        BT_MODULE_ID_##MODULE,                                           \
        "FAILED to Initialize Mutex in " #MODULE ".\n");                 \
        return MODULE##_MUTEX_INIT_FAILED;                               \
    }

/*
 *  Macro to Initialize Conditional Variable.
 *  To be used in void function as it returns no error.
 */
#define BT_COND_INIT_VOID(cond, MODULE)                                  \
    if (BT_thread_cond_init(&(cond), NULL) < 0)                          \
    {                                                                    \
        COMMON_ERR(                                                      \
        BT_MODULE_ID_##MODULE,                                           \
        "FAILED to Initialize Conditional Variable in " #MODULE ".\n");  \
        return;                                                          \
    }

/*
 *  Macro to Initialize Conditional Variable.
 *  It returns an error if conditional variable initialization fails.
 */
#define BT_COND_INIT(cond, MODULE)                                       \
    if (BT_thread_cond_init(&(cond), NULL) < 0)                          \
    {                                                                    \
        COMMON_ERR(                                                      \
        BT_MODULE_ID_##MODULE,                                           \
        "FAILED to Initialize Conditional Variable in " #MODULE ".\n");  \
        return MODULE##_COND_INIT_FAILED;                                \
    }

/*
 *  Locks the Module Specific Mutex which prevents any global variable being
 *  overwritten by any function. It returns an error if mutex lock fails.
 */
#define BT_MUTEX_LOCK(mutex, MODULE)                                 \
    if (BT_thread_mutex_lock(&(mutex)) < 0)                          \
    {                                                                \
        COMMON_ERR(                                                  \
        BT_MODULE_ID_##MODULE,                                       \
        "FAILED to Lock Mutex in " #MODULE ".\n");                   \
        return MODULE##_MUTEX_LOCK_FAILED;                           \
    }

/*
 *  Locks the Module Specific Mutex which prevents any global variable being
 *  overwritten by any function. To be used in void function as it
 *  returns no error.
 */
#define BT_MUTEX_LOCK_VOID(mutex, MODULE)                            \
    if (BT_thread_mutex_lock(&(mutex)) < 0)                          \
    {                                                                \
        COMMON_ERR(                                                  \
        BT_MODULE_ID_##MODULE,                                       \
        "FAILED to Lock Mutex in " #MODULE ".\n");                   \
        return;                                                      \
    }

/*
 *  Locks the Module Specific Mutex which prevents any global variable being
 *  overwritten by any function.
 *  It returns the error 'value' if mutex lock failes.
 */
#define BT_MUTEX_LOCK_RETURN_ON_FAILURE(mutex, MODULE, value)        \
    if (BT_thread_mutex_lock(&(mutex)) < 0)                          \
    {                                                                \
        COMMON_ERR(                                                  \
        BT_MODULE_ID_##MODULE,                                       \
        "FAILED to Lock Mutex in " #MODULE ".\n");                   \
        return (value);                                              \
    }

/*
 *  Locks the Module Specific Mutex which prevents any global variable being
 *  overwritten by any function. On failure, only an Error is logged.
 *  It can be used from both void and non-void functions.
 */
#define BT_MUTEX_LOCK_DONOT_RETURN_ON_FAILURE(mutex, MODULE)         \
    if (BT_thread_mutex_lock(&(mutex)) < 0)                          \
    {                                                                \
        COMMON_ERR(                                                  \
        BT_MODULE_ID_##MODULE,                                       \
        "FAILED to Lock Mutex in " #MODULE ".\n");                   \
    }

/*
 *  Unlocks the Module Specific Mutex which realeses the global variables
 *  to be written into. It returns an error if mutex unlock fails.
 */
#define BT_MUTEX_UNLOCK(mutex, MODULE)                               \
    if (BT_thread_mutex_unlock(&(mutex)) < 0)                        \
    {                                                                \
        COMMON_ERR(                                                  \
        BT_MODULE_ID_##MODULE,                                       \
        "FAILED to Unlock Mutex in " #MODULE ".\n");                 \
        return MODULE##_MUTEX_UNLOCK_FAILED;                         \
    }

/*
 *  Unlocks the Module Specific Mutex which realeses the global variables
 *  to be written into. To be used in void functions as it returns
 *  no error.
 */
#define BT_MUTEX_UNLOCK_VOID(mutex, MODULE)                          \
    if (BT_thread_mutex_unlock(&(mutex)) < 0)                        \
    {                                                                \
        COMMON_ERR(                                                  \
        BT_MODULE_ID_##MODULE,                                       \
        "FAILED to Unlock Mutex in " #MODULE ".\n");                 \
        return;                                                      \
    }

/*
 *  Unlocks the Module Specific Mutex which realeses the global variables
 *  to be written into.
 *  It returns the error 'value' if mutex unlock failes.
 */
#define BT_MUTEX_UNLOCK_RETURN_ON_FAILURE(mutex, MODULE, value)      \
    if (BT_thread_mutex_unlock(&(mutex)) < 0)                        \
    {                                                                \
        COMMON_ERR(                                                  \
        BT_MODULE_ID_##MODULE,                                       \
        "FAILED to Unlock Mutex in " #MODULE ".\n");                 \
        return (value);                                              \
    }

/*
 *  Unlocks the Module Specific Mutex which realeses the global variables
 *  to be written into. On failure, only Error is logged.
 *  It can be used from both void and non-void functions.
 */
#define BT_MUTEX_UNLOCK_DONOT_RETURN_ON_FAILURE(mutex, MODULE)       \
    if (BT_thread_mutex_unlock(&(mutex)) < 0)                        \
    {                                                                \
        COMMON_ERR(                                                  \
        BT_MODULE_ID_##MODULE,                                       \
        "FAILED to Unlock Mutex in " #MODULE ".\n");                 \
    }

#else  /* BT_DISABLE_MUTEX */

/* Macro to define a Mutex Variable */
#define BT_DEFINE_MUTEX(mutex)

/* Macro to define a Mutex Variable with a type qualifier */
#define BT_DEFINE_MUTEX_TYPE(type, mutex)

/* Macro to define a Conditional Variable */
#define BT_DEFINE_COND(cond)

/* Macro to define a Conditional Variable with a type qualifier */
#define BT_DEFINE_COND_TYPE(type, cond)

/*
 *  Macro to Initialize Mutex.
 *  To be used in void function as it returns no error.
 */
#define BT_MUTEX_INIT_VOID(mutex, MODULE)

/*
 *  Macro to Initialize Mutex.
 *  It returns an error if mutex initialization fails.
 */
#define BT_MUTEX_INIT(mutex, MODULE)

/*
 *  Macro to Initialize Conditional Variable.
 *  To be used in void function as it returns no error.
 */
#define BT_COND_INIT_VOID(cond, MODULE)

/*
 *  Macro to Initialize Conditional Variable.
 *  It returns an error if conditional variable initialization fails.
 */
#define BT_COND_INIT(cond, MODULE)

/*
 *  Locks the Module Specific Mutex which prevents any global variable being
 *  overwritten by any function. It returns an error if mutex lock fails.
 */
#define BT_MUTEX_LOCK(mutex, MODULE)

/*
 *  Locks the Module Specific Mutex which prevents any global variable being
 *  overwritten by any function. To be used in void function as it
 *  returns no error.
 */
#define BT_MUTEX_LOCK_VOID(mutex, MODULE)

/*
 *  Locks the Module Specific Mutex which prevents any global variable being
 *  overwritten by any function.
 *  It returns the error 'value' if mutex lock failes.
 */
#define BT_MUTEX_LOCK_RETURN_ON_FAILURE(mutex, MODULE, value)

/*
 *  Locks the Module Specific Mutex which prevents any global variable being
 *  overwritten by any function. On failure, only an Error is logged.
 *  It can be used from both void and non-void functions.
 */
#define BT_MUTEX_LOCK_DONOT_RETURN_ON_FAILURE(mutex, MODULE)

/*
 *  Unlocks the Module Specific Mutex which realeses the global variables
 *  to be written into. It returns an error if mutex unlock fails.
 */
#define BT_MUTEX_UNLOCK(mutex, MODULE)

/*
 *  Unlocks the Module Specific Mutex which realeses the global variables
 *  to be written into. To be used in void functions as it returns
 *  no error.
 */
#define BT_MUTEX_UNLOCK_VOID(mutex, MODULE)

/*
 *  Unlocks the Module Specific Mutex which realeses the global variables
 *  to be written into.
 *  It returns the error 'value' if mutex unlock failes.
 */
#define BT_MUTEX_UNLOCK_RETURN_ON_FAILURE(mutex, MODULE, value)

/*
 *  Unlocks the Module Specific Mutex which realeses the global variables
 *  to be written into. On failure, only Error is logged.
 *  It can be used from both void and non-void functions.
 */
#define BT_MUTEX_UNLOCK_DONOT_RETURN_ON_FAILURE(mutex, MODULE)

#endif /* BT_DISABLE_MUTEX */


#ifndef BT_NO_STATIC_DATA_SIZE

/* Define UCHAR array of size 'BT_STATIC_DATA_SIZE' */
#define BT_DEFINE_STATIC_DATA(data) UCHAR data [BT_STATIC_DATA_SIZE];

#else

#define BT_DEFINE_STATIC_DATA(data)

#endif /* BT_NO_STATIC_DATA_SIZE */

/* Abstractions for bit-wise operation */
#define BT_EXTRACT_BITNUM(val, bitnum)        (((val) >> (bitnum)) & 1)
#define BT_SET_BITNUM(val, bitnum)            ((val) |= (1 << (bitnum)))
#define BT_CLR_BITNUM(val, bitnum)            ((val) &= (~(1 << (bitnum))))

/* Macro to find Minimum and Maximum value */
#define BT_GET_MIN(a, b) \
        (((a) > (b)) ? (b) : (a))

#define BT_GET_MAX(a, b) \
        (((a) > (b)) ? (a) : (b))

/* Unreferenced variable macro to avoid compilation warnings */
#define BT_IGNORE_UNUSED_PARAM(v) (void)(v)

/* Loop for ever */
#define BT_LOOP_FOREVER() for(;;)

/** \} */

/*
 * Module Identifier definitions.
 * Currently used for runtime debug enable/disable scenario.
 * In future, this can be used for other purposes as well,
 * hence these defines are placed under common header file.
 */
/* Page 0 - Bluetooth Protocol Modules */
#define BT_MODULE_PAGE_0                      0x00000000

/* Module - Bit Mask */
#define BT_MODULE_BIT_MASK_HCI                0x00000001
#define BT_MODULE_BIT_MASK_L2CAP              0x00000002
#define BT_MODULE_BIT_MASK_COMMON             0x00000004
#define BT_MODULE_BIT_MASK_DQ                 0x00000008
#define BT_MODULE_BIT_MASK_ATT                0x00000010
#define BT_MODULE_BIT_MASK_SMP                0x00000020
#define BT_MODULE_BIT_MASK_WT                 0x00000040
#define BT_MODULE_BIT_MASK_GATT               0x00000080
#define BT_MODULE_BIT_MASK_GATT_DB            0x00000100
#define BT_MODULE_BIT_MASK_FSM                0x00000200
#define BT_MODULE_BIT_MASK_BCSP               0x00000400
#define BT_MODULE_BIT_MASK_RACP               0x00000800
#define BT_MODULE_BIT_MASK_GAP                0x00001000
#define BT_MODULE_BIT_MASK_TCP_SOCKET         0x00002000

/* Module ID */
#define BT_MODULE_ID_HCI                      (BT_MODULE_PAGE_0 | BT_MODULE_BIT_MASK_HCI)
#define BT_MODULE_ID_L2CAP                    (BT_MODULE_PAGE_0 | BT_MODULE_BIT_MASK_L2CAP)
#define BT_MODULE_ID_COMMON                   (BT_MODULE_PAGE_0 | BT_MODULE_BIT_MASK_COMMON)
#define BT_MODULE_ID_DQ                       (BT_MODULE_PAGE_0 | BT_MODULE_BIT_MASK_DQ)
#define BT_MODULE_ID_ATT                      (BT_MODULE_PAGE_0 | BT_MODULE_BIT_MASK_ATT)
#define BT_MODULE_ID_SMP                      (BT_MODULE_PAGE_0 | BT_MODULE_BIT_MASK_SMP)
#define BT_MODULE_ID_WT                       (BT_MODULE_PAGE_0 | BT_MODULE_BIT_MASK_WT)
#define BT_MODULE_ID_GATT_DB                  (BT_MODULE_PAGE_0 | BT_MODULE_BIT_MASK_GATT_DB)
#define BT_MODULE_ID_GATT                     (BT_MODULE_PAGE_0 | BT_MODULE_BIT_MASK_GATT)
#define BT_MODULE_ID_FSM                      (BT_MODULE_PAGE_0 | BT_MODULE_BIT_MASK_FSM)
#define BT_MODULE_ID_BCSP                     (BT_MODULE_PAGE_0 | BT_MODULE_BIT_MASK_BCSP)
#define BT_MODULE_ID_RACP                     (BT_MODULE_PAGE_0 | BT_MODULE_BIT_MASK_RACP)
#define BT_MODULE_ID_GAP                      (BT_MODULE_PAGE_0 | BT_MODULE_BIT_MASK_GAP)
#define BT_MODULE_ID_TCP_SOCKET               (BT_MODULE_PAGE_0 | BT_MODULE_BIT_MASK_TCP_SOCKET)

/* Page 1 - Classic Profile Modules (Reserved) */
#define BT_MODULE_PAGE_1                      0x10000000


/* Page 2 - GATT based Profile Modules */
#define BT_MODULE_PAGE_2                      0x20000000

/* Page 3 - Utilities Modules */
#define BT_MODULE_PAGE_3                      0x30000000

/* Module - Bit Mask */
#define BT_MODULE_BIT_MASK_STORAGE            0x00000001
#define BT_MODULE_BIT_MASK_STATUS             0x00000002
#define BT_MODULE_BIT_MASK_SNOOP              0x00000004
#define BT_MODULE_BIT_MASK_HT                 0x00000008
#define BT_MODULE_BIT_MASK_AES_CMAC           0x00000010
#define BT_MODULE_BIT_MASK_TRANSPORT          0x00000020
#define BT_MODULE_BIT_MASK_TIMER              0x00000040
#define BT_MODULE_BIT_MASK_FOPS               0x00000080
#define BT_MODULE_BIT_MASK_ASSERT             0x00000100
#define BT_MODULE_BIT_MASK_MUTE               0x00000200
#define BT_MODULE_BIT_MASK_VCOM               0x00000400
#define BT_MODULE_BIT_MASK_AT_CMD             0x00000800
#define BT_MODULE_BIT_MASK_IFACE_TRANSPORT    0x00001000

/* Module ID */
#define BT_MODULE_ID_STORAGE                  (BT_MODULE_PAGE_3 | BT_MODULE_BIT_MASK_STORAGE)
#define BT_MODULE_ID_STATUS                   (BT_MODULE_PAGE_3 | BT_MODULE_BIT_MASK_STATUS)
#define BT_MODULE_ID_SNOOP                    (BT_MODULE_PAGE_3 | BT_MODULE_BIT_MASK_SNOOP)
#define BT_MODULE_ID_HT                       (BT_MODULE_PAGE_3 | BT_MODULE_BIT_MASK_HT)
#define BT_MODULE_ID_AES_CMAC                 (BT_MODULE_PAGE_3 | BT_MODULE_BIT_MASK_AES_CMAC)
#define BT_MODULE_ID_TRANSPORT                (BT_MODULE_PAGE_3 | BT_MODULE_BIT_MASK_TRANSPORT)
#define BT_MODULE_ID_TIMER                    (BT_MODULE_PAGE_3 | BT_MODULE_BIT_MASK_TIMER)
#define BT_MODULE_ID_FOPS                     (BT_MODULE_PAGE_3 | BT_MODULE_BIT_MASK_FOPS)
#define BT_MODULE_ID_ASSERT                   (BT_MODULE_PAGE_3 | BT_MODULE_BIT_MASK_ASSERT)
#define BT_MODULE_ID_MUTE                     (BT_MODULE_PAGE_3 | BT_MODULE_BIT_MASK_MUTE)
#define BT_MODULE_ID_VCOM                     (BT_MODULE_PAGE_3 | BT_MODULE_BIT_MASK_VCOM)
#define BT_MODULE_ID_AT_CMD                   (BT_MODULE_PAGE_3 | BT_MODULE_BIT_MASK_AT_CMD)
#define BT_MODULE_ID_IFACE_TRANSPORT          (BT_MODULE_PAGE_3 | BT_MODULE_BIT_MASK_IFACE_TRANSPORT)

/* -------------------------------------------- Structures/Data Types */

/**
 * \addtogroup bt_common_defines Defines
 * \{
 */

/**
 * \defgroup bt_common_structures Structures
 * \{
 */

/* 128-Bit UUID */
typedef struct
{
    UCHAR byte[16];

} UINT128_ID;


/* The UUID Data Type */
typedef struct
{
    UCHAR uuid_type;

    union
    {
        UINT16 uuid_16;
        UINT32 uuid_32;
        UINT128_ID uuid_128;
    } uuid_union;

} S_UUID;

/* Abstracted Bluetooth Device Address */
typedef struct _BT_DEVICE_ADDR
{
    UCHAR    addr[BT_BD_ADDR_SIZE];

    UCHAR    type;

} BT_DEVICE_ADDR;


/** \} */

/** \} */

/* -------------------------------------------- Function/API Declarations */
#ifdef __cplusplus
extern "C"{
#endif

/**
 * \defgroup bt_common_callback Callback
 * \{
 */

/* Function to trigger indication of Bluetooth ON Complete */
API_RESULT BT_common_bluetooth_on_complete
           (
               void
           );


/** \} */

/**
 * \defgroup bt_common_api API Definitions
 * \{
 */

/**
 * API to initialize BlueLitE Stack. This is the first API that the
 * application should call before any other API. This function
 * initializes all the internal stack modules and creates necessary tasks.
 *
 * \note
 * - After this function, the application should call \ref BT_bluetooth_on
 * - BT_ethermind_init should be called only once during the lifetime of
 *   application. However, application may call \ref BT_bluetooth_on and
 *   \ref BT_bluetooth_off multiple times.
 */
void BT_ethermind_init
     (
         void
     );

/**
 * API to initialize the Bluetooth Hardware. This API should be called after
 * \ref BT_ethermind_init. Application should call other API only after
 * successful completion of Bluetooth ON.
 *
 * \param [in] hci_event_ind_cb Application callback to receive HCI events
 * \param [in] bt_on_complete_cb Application callback to confirm
 *                                      completion of Bluetooth ON procedure
 * \param [in] local_name Name to be for the local device. When other devices
 *                   search, they see this name.
 *
 * \return
 *      \ref API_RESULT on successful start of Bluetooth ON procedure
 *
 * \note This is a non-blocking API that returns immediately after starting
 *       the Bluetooth ON procedure. The completion of the procedure is
 *       notified to the application through
 *       appl_bluetooth_on_complete_cb() callback. The application should
 *       wait for this callback before proceding further.
 */
API_RESULT BT_bluetooth_on
           (
               /* IN */ API_RESULT (* hci_event_ind_cb) (UCHAR, UCHAR *, UCHAR),
               /* IN */ API_RESULT (* bt_on_complete_cb) (void),
               /* IN */ CHAR * local_name
           );

/**
 * API to turn off Bluetooth Hardware. This API should be called after
 * \ref BT_bluetooth_on.
 *
 * \return
 *      \ref API_RESULT on successful Bluetooth OFF
 */
API_RESULT BT_bluetooth_off
           (
               void
           );

#ifdef BT_SUPPORT_GET_STACK_INIT_STATE
/**
 * API to get current state of BlueLitE stack.
 *
 * \param [out] state  State of the stack - one of the states defined in
 *                                         \ref bt_common_stack_init_states
 *
 * \return
 *      \ref API_RESULT on successful retrieval of state.
 */
API_RESULT BT_bluetooth_get_stack_init_state (/* OUT */ UCHAR *state);
#endif /* BT_SUPPORT_GET_STACK_INIT_STATE */

#ifdef __cplusplus
};
#endif

/** \} */

/** \} */

#endif /* _H_BT_COMMON_ */

