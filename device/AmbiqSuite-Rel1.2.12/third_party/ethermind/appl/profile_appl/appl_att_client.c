
/**
 *  \file appl_att_client.c
 *
 *  This file contains the ATT client application.
 */

/*
 *  Copyright (C) 2013. Mindtree Ltd.
 *  All rights reserved.
 */

/* --------------------------------------------- Header File Inclusion */
#include "appl_att_client.h"
#include "appl.h"

/* --------------------------------------------- External Global Variables */

/* --------------------------------------------- Exported Global Variables */

/* --------------------------------------------- Static Global Variables */
static ATT_HANDLE appl_att_client_handle;

static UCHAR *print_str = "\n------------------------------\n"\
                   "        ATT CLINET MENU\n"\
                   "------------------------------\n"\
                   "0.   Exit\n"\
                   "1.   Refresh\n\n"\
                   "2.   Exchange MTU Request\n\n"\
                   "10.  Find information Request\n"\
                   "11.  Find by Type Value Request\n"\
                   "20.  Read By Type Request\n"\
                   "21.  Read Request\n"\
                   "22.  Read Blob Request\n"\
                   "23.  Read Multiple request\n"
                   "24.  Read Group Type Request\n"
                   "30.  Write Command \n"\
                   "31.  Write Request \n"\
                   "32.  Prepare Write Request\n"\
                   "33.  Execute Write Request\n"\
                   "34.  Signed Write Request\n\n"\
                   "40.  Handle value confirmation\n\n";

/* --------------------------------------------- Functions */

API_RESULT att_cb
           (
               ATT_HANDLE    * handle,
               UCHAR         att_event,
               API_RESULT    event_result,
               UCHAR         * event_data,
               UINT16        event_datalen
           )
{
    int index, i;
    UINT16 uuid;
    ATT_ATTR_HANDLE attr_handle, handle_1;
    UINT16 arg_len;
    UINT16 mtu;
    UCHAR uuid_arr[16];
    UINT16 offset;
    UCHAR  op_code;

    APPL_TRC
    ("[ATT]:[0x%02X]: Received ATT Event 0x%02X with result 0x%04X",
    *handle,att_event,event_result);

    appl_dump_bytes (event_data, event_datalen);

    switch(att_event)
    {
    case ATT_CONNECTION_IND:
        APPL_TRC (
        "[0x%02X]:Received Connection Indtication, Result 0x%04X!\n",
        *handle,event_result);
        appl_att_client_handle = *handle;
        break;
    case ATT_ERROR_RSP:
        BT_UNPACK_LE_1_BYTE(&op_code,event_data+1);
        BT_UNPACK_LE_2_BYTE(&attr_handle, event_data+2);
        APPL_TRC (
        "Received Error Response, Response code 0x%04X for Opcode 0x%02X , "
        "Handle 0x%04X!\n",event_result,attr_handle,attr_handle);
        break;

    case ATT_XCHNG_MTU_RSP:
        BT_UNPACK_LE_2_BYTE(&mtu, event_data);
        APPL_TRC (
        "Received Exchange MTU Response with Result 0x%04X. MTU Size "
        "= 0x%04X!\n",mtu);
        break;

    case ATT_FIND_INFO_RSP:
        printf ("Received Read Information Response Opcode!\n");

        if(0 < event_datalen)
        {
            if(0x01 == ((UCHAR*)event_data)[0])
            {
                APPL_TRC("\n\n16 bit UUIDs : \n");
                for(index = 1; index<event_datalen; index=index+4)
                {

                    BT_UNPACK_LE_2_BYTE
                    (
                        &attr_handle,
                        ((UCHAR*)event_data+ index)
                    );
                    BT_UNPACK_LE_2_BYTE
                    (
                       &uuid,
                       ((UCHAR*)event_data + index + 2)
                    );
                    APPL_TRC ("Handle : 0x%04X -> ", attr_handle);
                    APPL_TRC ("UUID   : 0x%04X \n", uuid);
                }
            }
            else if(0x02 == ((UCHAR*)event_data)[0])
            {
                for(index = 1; index < event_datalen; index=index+18)
                {
                    APPL_TRC("\n\n128 bit UUIDs : \n");
                    BT_UNPACK_LE_2_BYTE(&attr_handle, (((UCHAR*)event_data) + index));
                    ATT_UNPACK_UUID(uuid_arr, (((UCHAR*)event_data) + index+2), 16);
                    APPL_TRC ("Handle : 0x%04X\n", attr_handle);
                    APPL_TRC ("UUID   : ");

                    appl_dump_bytes(uuid_arr, 16);
                }
            }
            else
            {
                APPL_TRC ("List of handles corrosponding to the Req UUID:\n");

                for(index = 1; index < event_datalen; index=index+2)
                {

                    BT_UNPACK_LE_2_BYTE(&attr_handle, (((UCHAR*)event_data)+ index));
                    APPL_TRC ("Handle : 0x%04X -> \n", attr_handle);

                }

            }
        }
        break;
    case ATT_READ_BY_TYPE_RSP:
        printf ("Received Read Type Response Opcode!\n");

        arg_len = event_data[0];

        event_datalen --;
        event_data++;

        for (index = 0; index < (event_datalen/(arg_len)); index++ )
        {
            BT_PACK_LE_2_BYTE(handle, (event_data + (index * arg_len)));
            printf ("Handle - 0x%04X\n", handle);

            printf ("Handle Value Received - \n");
            appl_dump_bytes(event_data, arg_len-2);
        }
        printf ("\n");
        break;
    case ATT_READ_BY_GROUP_RSP:
        printf ("Received Read Group Type Response Opcode!\n");

        arg_len = event_data[0];

        event_datalen --;
        event_data++;

        for (index = 0; index < (event_datalen/(arg_len)); index++ )
        {
            BT_PACK_LE_2_BYTE(handle, (event_data + (index * arg_len)));
            printf ("Attribute handle - 0x%04X\n", handle);

            BT_PACK_LE_2_BYTE(handle, (event_data + (index * arg_len+2)));
            printf ("Group End handle - 0x%04X\n", handle);

            printf ("Handle Value Received - \n");
            appl_dump_bytes(event_data, arg_len-4);
        }
        printf ("\n");
        break;
    case ATT_FIND_BY_TYPE_VAL_RSP:
        printf ("Received Find by Type Value Response Opcode!\n");

        printf ("Found Handle        End Found Handle\n");
        for (i = 0; i < event_datalen; i+=4)
        {
            BT_PACK_LE_2_BYTE(&attr_handle, (event_data+i));
            BT_PACK_LE_2_BYTE(&handle_1, (event_data+i+2));
            printf ("%04X                  %04X\n", handle, handle_1);
        }
        break;

    case ATT_READ_RSP:
        printf ("Received Read Response Opcode!\n");

        printf ("Handle Value Received - \n");
        appl_dump_bytes(event_data, event_datalen);
        printf ("\n");
        break;

    case ATT_READ_BLOB_RSP:
        printf ("Received Read Response Opcode!\n");
        printf ("Handle Value Received - \n");
        appl_dump_bytes(event_data, event_datalen);
        printf ("\n");
        break;

    case ATT_READ_MULTIPLE_RSP:
        printf ("Received read multiple response Opcode!\n");

        printf ("Byte stream of values received [not seperated by handle]");
        appl_dump_bytes(event_data, event_datalen);
        printf ("\n");
        break;
    case ATT_WRITE_RSP:
        printf ("Received Write Response Opcode!\n");
        break;

    case ATT_WRITE_CMD_TX_COMPLETE:
        printf("Received Write Command Tx Complete (Locally generated)\n");
        appl_dump_bytes(event_data, event_datalen);
        break;

    case ATT_SIGNED_WRITE_CMD_TX_COMPLETE:
        printf("Received Signed Write Command Tx Complete (Locally generated)\n");
        appl_dump_bytes(event_data, event_datalen);
        break;

    case ATT_PREPARE_WRITE_RSP:
        printf ("Prepare Write Response\n");
        BT_PACK_LE_2_BYTE(&attr_handle, event_data);
        printf ("Handle - 0x%04X\n", handle);
        BT_PACK_LE_2_BYTE(&offset, event_data+2);
        printf ("Offset - 0x%04X\n", offset);
        printf ("Handle Value Received - \n");
        appl_dump_bytes(event_data + 4, event_datalen - 4);
        printf ("\n");
        break;

    case ATT_EXECUTE_WRITE_RSP:
        printf ("Received Execute Write Response\n");
        break;

    case ATT_HANDLE_VALUE_NTF:
        printf ("Received HVN\n");
        BT_PACK_LE_2_BYTE(&attr_handle, event_data);
        printf ("Handle - 0x%04X\n", attr_handle);
        printf ("Handle Value Received - \n");
        appl_dump_bytes(event_data + 2, event_datalen - 2);
        printf ("\n");
        break;

    case ATT_HANDLE_VALUE_IND:
        printf ("Received HVI\n");
        BT_PACK_LE_2_BYTE(&attr_handle, event_data);
        printf ("Handle - 0x%04X\n", handle);
        printf ("Handle Value Received - \n");
        appl_dump_bytes(event_data + 2, event_datalen);

        break;
    }
    printf("\n\n");

    return API_SUCCESS;
}

void main_att_client_operations(void)
{
    ATT_FIND_INFO_REQ_PARAM find_info_req_param;
    ATT_FIND_BY_TYPE_VAL_REQ_PARAM find_by_type_val_req_param;
    ATT_READ_BY_TYPE_REQ_PARAM read_by_type_req;
    ATT_READ_REQ_PARAM read_req_param;
    ATT_WRITE_CMD_PARAM write_cmd_param;
    ATT_WRITE_REQ_PARAM write_req_param;
    ATT_PREPARE_WRITE_REQ_PARAM prepare_write_req_param;
    ATT_EXECUTE_WRITE_REQ_PARAM execute_write_req_param;
    ATT_READ_BLOB_REQ_PARAM read_blob_req_param;
    ATT_READ_MULTIPLE_REQ_PARAM read_multiple_req_param;
    ATT_READ_BY_GROUP_TYPE_REQ_PARAM read_by_group_param;

    int data;
    int index;
    INT32 choice;
    UINT16 mtu;
    UINT16 handle_list[20];
    API_RESULT retval;
    UCHAR value[20];
    data = 0;

    while (1)
    {
        printf("%s \n", print_str);
        printf("Enter you choice : ");
        scanf("%d", &choice);
        switch(choice)
        {
        case 0:
            return;
        case 1:
            break;

        case 2: /* Exchange MTU Request */

            printf ("Enter the MTU for the ATT connection\n");
            scanf ("%x", &data);
            mtu = (UINT16)data;

            retval = BT_att_send_mtu_xcnhg_req
                     (
                         &appl_att_client_handle,
                         &mtu
                     );

            printf ("Exchange MTU REQ retval - 0x%04X\n", retval);
            break;

        case 10: /* Find Information Request */
            printf("Enter start handle[HEX] : ");
            scanf("%x", &data);
            find_info_req_param.start_handle = (UINT16) data;
            printf("Enter end handle[HEX] : ");
            scanf("%x", &data);
            find_info_req_param.end_handle = (UINT16) data;


            retval = BT_att_send_find_info_req
                     (
                          &appl_att_client_handle,
                          &find_info_req_param
                      );

            APPL_TRC (
            "Find Information Request Sent with retval 0x%04X\n", retval);

            break;
        case 11: /* Find By Type Value Request */
            printf("Enter start handle[HEX] : ");
            scanf("%x", &data);
            find_by_type_val_req_param.range.start_handle = (UINT16) data;
            printf("Enter end handle[HEX] : ");
            scanf("%x", &data);
            find_by_type_val_req_param.range.end_handle = (UINT16) data;

            printf("Enter 16 Bit UUID[HEX] 16: ");
            scanf("%x", &data);
#ifndef ATT_SUPPORT_128_BIT_UUID
            find_by_type_val_req_param.uuid = (UCHAR) data;
#else /* ATT_SUPPORT_128_BIT_UUID */
            find_by_type_val_req_param.uuid.uuid_16 = (UCHAR) data;
#endif /* ATT_SUPPORT_128_BIT_UUID */

            printf ("Enter the length of the value (decimal)\n");
            scanf ("%d", &find_by_type_val_req_param.value.len);

            printf ("Enter the value [byte by byte space seperated in HEX]: ");
            for (index = 0; index < find_by_type_val_req_param.value.len;
                index++)
            {
                scanf ("%x", &data);
                value[index] = (UCHAR)data;
            }
            find_by_type_val_req_param.value.val = value;

            retval = BT_att_send_find_by_type_val_req
                     (
                         &appl_att_client_handle,
                         &find_by_type_val_req_param
                     );

            APPL_TRC
            ("ATT Find By Type Value Request sent with result 0x%04X\n",retval);
            break;
        case 20: /* Read By Type Request */
            printf("Enter start handle[HEX] : ");
            scanf("%x", &data);
            read_by_type_req.range.start_handle = (ATT_ATTR_HANDLE) data;
            printf("Enter end handle[HEX] : ");
            scanf("%x", &data);
            read_by_type_req.range.end_handle = (ATT_ATTR_HANDLE) data;
#ifdef ATT_SUPPORT_128_BIT_UUID
            printf("Enter uuid type\n\t1 - 16 Bit\t2 - 128 Bit) : ");
            scanf("%x", &data);
            read_by_type_req.uuid_format = (UCHAR) data;
            if (1 == read_by_type_req.uuid_format)
            {
                printf("Enter 16 Bit UUID[HEX] : ");
            }
            else if (2 == read_by_type_req.uuid_format)
            {
                printf("Enter 128 Bit UUID[HEX OCTETS]  : ");
                for (index =0; index < 16; index ++)
                {
                    scanf("%x", &data);
                    read_by_type_req.uuid_128[index] = (UCHAR) data;
                }
            }

#else /* ATT_SUPPORT_128_BIT_UUID */
            read_by_type_req.uuid_format = ATT_16_BIT_UUID_FORMAT;
            printf("Enter 16 Bit UUID[HEX] : ");
            scanf("%x", &data);
            read_by_type_req.uuid = (UINT16) data;
#endif /* ATT_SUPPORT_128_BIT_UUID */

            retval = BT_att_send_read_by_type_req
                     (
                          &appl_att_client_handle,
                          &read_by_type_req
                      );

            APPL_TRC (
            "ATT Read By Type Request sent with retval 0x%04X\n", retval);

            break;

        case 21: /* Read Request */
            printf("Enter handle[HEX] : ");
            scanf("%x", &data);
            read_req_param = (ATT_ATTR_HANDLE) data;

            retval = BT_att_send_read_req
                     (
                          &appl_att_client_handle,
                          &read_req_param
                      );

            APPL_TRC (
            "ATT Read Request sent with retval 0x%04X\n", retval);
            break;
        case 22: /* Read Blob Request */
            printf("Enter handle[HEX] : ");
            scanf("%x", &data);
            read_blob_req_param.handle = (ATT_ATTR_HANDLE) data;
            printf("Enter offset[HEX] : ");
            scanf("%x", &data);
            read_blob_req_param.offset = (ATT_ATTR_HANDLE) data;

            retval = BT_att_send_read_blob_req
                     (
                          &appl_att_client_handle,
                          &write_req_param
                      );

            APPL_TRC (
            "ATT Read Blob Request Result 0x%04X\n", retval);

            break;
        case 23: /* Read Multiple Request */

            printf ("Enter the number of handles [decimal]\n");
            scanf ("%x", &read_multiple_req_param.list_count);

            printf ("Enter the list of handle [HEX] \n");
            for (index = 0; index < read_multiple_req_param.list_count; index++)
            {
                scanf ("%04X", &data);
                handle_list[index] = (ATT_ATTR_HANDLE)data;
            }
            read_multiple_req_param.handle_list = handle_list;

            retval = BT_att_send_read_multiple_req
                     (
                         &appl_att_client_handle,
                         &read_multiple_req_param
                     );

            APPL_TRC
            ("ATT Read Multiple Request sent qih result0x%04X\n", retval);
            break;

        case 24: /* Read By Group Type Request */
            printf("Enter start handle[HEX] : ");
            scanf("%x", &data);
            read_by_group_param.range.start_handle = (ATT_ATTR_HANDLE) data;
            printf("Enter end handle[HEX] : ");
            scanf("%x", &data);
            read_by_group_param.range.end_handle = (ATT_ATTR_HANDLE) data;
#ifdef ATT_SUPPORT_128_BIT_UUID
            printf("Enter UUID Format type\n\t 1 - 16\n\t 2 - 128 Bit\n");
            scanf("%x", &data);
            read_by_group_param.uuid_format = (UCHAR) data;
            if (ATT_16_BIT_UUID_FORMAT == read_by_group_param.uuid_format)
            {
                printf("Enter 16 Bit UUID[HEX] : ");
                scanf("%x", &data);
                read_by_group_param.group_type = (UINT16) data;
            }
            else if (ATT_128_BIT_UUID_FORMAT == read_by_group_param.uuid_format)
            {
                printf("Enter 128 Bit UUID[HEX] : ");
                for (index =0; index < ((0 == uuid_type)? 2 : 16); index ++)
                {
                    scanf("%x", &data);
                    uuid[index] = (UCHAR) data;
                }
            }
#else /* ATT_SUPPORT_128_BIT_UUID */
            printf("Enter 16 Bit UUID[HEX] : ");
            scanf("%x", &data);
            read_by_group_param.group_type = (UINT16) data;
#endif /* ATT_SUPPORT_128_BIT_UUID */
            retval = BT_att_send_read_by_group_req
                     (
                         &appl_att_client_handle,
                         &read_by_group_param
                     );

            APPL_TRC
            ("ATT Read By Group Type Request sent with result 0x%04X\n",
            retval);
            break;

        case 30: /* Write Command */
            printf("Enter handle[HEX] : ");
            scanf("%x", &data);
            write_cmd_param.handle = (ATT_ATTR_HANDLE) data;
            printf("Enter value len[HEX] : ");
            scanf("%x", &write_cmd_param.value.len);
            printf("Enter value[HEX] : ");
            for(index = 0; index < write_cmd_param.value.len; index++)
            {
                scanf("%x", &data);
                value [index] = (UCHAR)data;
            }
            write_cmd_param.value.val = value;

            retval = BT_att_send_write_cmd
                     (
                          &appl_att_client_handle,
                          &write_cmd_param
                      );

            APPL_TRC (
            "ATT Write Command Result - 0x%04X, Actual Value Len = 0x%04X\n",
            retval,write_cmd_param.value.actual_len);
            break;

        case 31: /* Write Request */
            printf("Enter handle[HEX] : ");
            scanf("%x", &data);
            write_req_param.handle = (ATT_ATTR_HANDLE) data;
            printf("Enter value len[HEX] : ");
            scanf("%x", &write_req_param.value.len);
            printf("Enter value[HEX] : ");
            for(index = 0; index < write_req_param.value.len; index++)
            {
                scanf("%x", &data);
                value [index] = (UCHAR)data;
            }
            write_req_param.value.val = value;

            retval = BT_att_send_write_req
                     (
                          &appl_att_client_handle,
                          &write_req_param
                      );

            APPL_TRC (
            "ATT Write Command Result - 0x%04X, Actual Value Len = 0x%04X\n",
            retval,write_req_param.value.actual_len);
            break;


        case 32: /* Prepare Write Request */
            printf("Enter handle[HEX] : ");
            scanf("%x", &data);
            prepare_write_req_param.handle_value.handle = (UINT16) data;

            printf("Enter value offset[HEX] : ");
            scanf("%x", &data);
            prepare_write_req_param.offset = (UINT16) data;

            printf("Enter value len[HEX] : ");
            scanf("%x", &prepare_write_req_param.handle_value.value.len);
            printf("Enter value[HEX] : ");
            for(index = 0;
            index < prepare_write_req_param.handle_value.value.len; index++)
            {
                scanf("%x", &data);
                value[index] = (UCHAR)data;
            }
            prepare_write_req_param.handle_value.value.val = value;

            retval = BT_att_send_prepare_write_req
                     (
                          &appl_att_client_handle,
                          &prepare_write_req_param
                      );

            APPL_TRC (
            "ATT Prepare Write Request Result - 0x%04X\n, Actual Value Len "
            "= 0x%04X\n", retval,
            prepare_write_req_param.handle_value.value.actual_len);
            break;

        case 33: /* Execute Write Request */
            printf("Enter flag\n\t1 - Execute\n\t0-Cancel\n");
            scanf("%x", &data);
            execute_write_req_param.flags = (UCHAR) data;

            retval = BT_att_send_execute_write_req
                     (
                         &appl_att_client_handle,
                         &execute_write_req_param
                     );
            APPL_TRC
            ("ATT Execute Write Request Result - 0x%04X\n",retval);
            break;
        case 34: /* Signed Write Request */
            break;
        case 40: /* Handle Value Confirmation */
            retval = BT_att_send_hndl_val_cnf(&appl_att_client_handle);
            APPL_TRC (
            "ATT Handle Value Confirmation sent with Result 0x%04X\n", retval);
            break;
        default:
            break;
        }

    }

}
