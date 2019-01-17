
/**
 *  \file hci_uart.h
 *
 *  This files containes the definitins used by the HCI UART Transport Layer
 */

/*
 *  Copyright (C) 2013. Mindtree Ltd.
 *  All rights reserved.
 */

#ifndef _H_HCI_UART_
#define _H_HCI_UART_

/** --------------------------------- Header File Inclusion */
#include "BT_common.h"


/* ---------------------------------- Global Definitions */
#if defined BT_UART && !defined BT_BCSP
    #define hci_transport_write_data    hci_uart_send_data
#endif /* BT_UART && !BT_BCSP */

#ifdef BT_BCSP
    #define hci_transport_write_data    hci_bcsp_send_data
#endif /* BT_BCSP */


/* ---------------------------------- Function Declarations */
/** HCI UART enable interface */
void hci_uart_enable(void);

/** HCI UART Initialization & Shutdown */
void hci_uart_init (void);
void hci_uart_bt_init (void);
void hci_uart_bt_shutdown (void);

/* HCI UART Send Data */
API_RESULT hci_uart_send_data (UCHAR, UCHAR *, UINT16, UCHAR);
void hci_uart_write_data(UCHAR *, UINT16);

#endif /* _H_HCI_UART_ */

