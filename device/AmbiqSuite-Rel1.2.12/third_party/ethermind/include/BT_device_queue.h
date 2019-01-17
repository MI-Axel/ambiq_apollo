
/**
 *  \file BT_device_queue.h
 *
 *  Module Header File for Device Queue module.
 */

/*
 *  Copyright (C) 2014. Mindtree Ltd.
 *  All rights reserved.
 */

#ifndef _H_BT_DEVICE_QUEUE_
#define _H_BT_DEVICE_QUEUE_

/* ----------------------------------------------- Header File Inclusion */
#include "BT_common.h"

/* ----------------------------------------------- Type Definition */
typedef UCHAR DEVICE_HANDLE;

typedef UCHAR DEVICE_LINK_TYPE;

#define DEVICE_HANDLE_INIT_VAL     0xFF

#define DEVICE_HANDLE_INIT(hndl)\
        (hndl) = DEVICE_HANDLE_INIT_VAL

#define DQ_LINK_NONE                    0x00
#define DQ_LE_LINK                      0x02
#define DQ_LINK_ANY                     0xFF

/* ----------------------------------------------- Function Declarations */
#ifdef __cplusplus
extern "C"{
#endif

/** Init routine */
void em_device_queue_init ( void );

/** Activating routine */
void device_queue_bt_init ( void );

/** Shutdown routine */
void device_queue_bt_shutdown ( void );

/** Enqueue routine */
API_RESULT device_queue_alloc
           (
               /* OUT */ DEVICE_HANDLE    * hndl, /* Device Handle */
               /* IN */  BT_DEVICE_ADDR         * addr  /* Remote Device to be added*/
           );


/* Delete routine */
API_RESULT device_queue_free
           (
               /* IN */ DEVICE_HANDLE    * hndl /* Device to be removed */
           );

/* Search routine */
API_RESULT device_queue_search_remote_addr
           (
               /* OUT */ DEVICE_HANDLE     * hndl,/* Device Reference */
               /* IN */  BT_DEVICE_ADDR    * addr /* Remote Device to be searched*/
           );

/* Fetch Remote Device Address */
API_RESULT device_queue_get_remote_addr
           (
               /* IN */  DEVICE_HANDLE     * hndl, /* Device Reference */
               /* OUT */ BT_DEVICE_ADDR    * addr  /* Remote Device Address */
           );

/* Fetch Device Address Only */
API_RESULT device_queue_get_remote_addr_only
           (
               /* IN */  DEVICE_HANDLE    * hndl, /* Device Reference */
               /* OUT */ UCHAR            * addr  /* Remote Device Address */
           );

/* Set remote addr routine */
API_RESULT device_queue_set_remote_addr
           (
               /* IN */ DEVICE_HANDLE     * hndl, /* Device Reference */
               /* IN */ BT_DEVICE_ADDR    * addr  /* Remote Device to be set */
           );

/* Fetch Local Device Address */
API_RESULT device_queue_get_local_addr
           (
               /* IN */  DEVICE_HANDLE     * hndl, /* Device Reference */
               /* OUT */ BT_DEVICE_ADDR    * addr  /* Device's address */
           );

/* Set local addr routine */
API_RESULT device_queue_set_local_addr
           (
               /* IN */ DEVICE_HANDLE     * hndl, /* Device Reference */
               /* IN */ BT_DEVICE_ADDR    * addr  /* Local Device to be set*/
           );

API_RESULT device_queue_set_curr_addr_type
           (
               /* IN */ UCHAR    * addr,/* Local Device to be set*/
               /* IN */ UCHAR    type
           );

#ifdef __cplusplus
};
#endif

#endif /* _H_BT_DEVICE_QUEUE_ */

