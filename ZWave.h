/* Z-Wave SerialAPI defines */

#define SOF     0x01
#define ACK     0x06
#define NAK     0x15
#define CAN     0x18
#define REQUEST     0x00
#define RESPONSE    0x01

#define SERIAL_API_APPL_NODE_ROLE_SET 	 0x01
#define SERIAL_API_APPL_NODE_ROLE_GET 	 0x02
#define SERIAL_API_APPL_NODE_ROLE_REPORT 	 0x03
#define SERIAL_API_APPL_SLAVE_NODE_ROLE_SET 	 0x04
#define SERIAL_API_APPL_SLAVE_NODE_ROLE_GET 	 0x05
#define SERIAL_API_APPL_SLAVE_NODE_ROLE_REPORT 	 0x06
#define SERIAL_API_APPL_NODE_ROLE_UNDEFINED 	 0xFF
#define FUNC_ID_SERIAL_API_GET_INIT_DATA 	 0x02
#define FUNC_ID_SERIAL_API_APPL_NODE_INFORMATION 	 0x03
#define FUNC_ID_APPLICATION_COMMAND_HANDLER 	 0x04
#define FUNC_ID_ZW_GET_CONTROLLER_CAPABILITIES 	 0x05
#define FUNC_ID_SERIAL_API_SET_TIMEOUTS 	 0x06
#define FUNC_ID_SERIAL_API_GET_CAPABILITIES 	 0x07
#define FUNC_ID_SERIAL_API_SOFT_RESET 	 0x08
#define FUNC_ID_ZW_GET_PROTOCOL_VERSION 	 0x09

/* Function ID for startup message */
#define FUNC_ID_SERIAL_API_STARTED                      0x0A
#define FUNC_ID_SERIAL_API_SETUP                        0x0B

#define FUNC_ID_ZW_SET_RF_RECEIVE_MODE 	 0x10
#define FUNC_ID_ZW_SET_SLEEP_MODE 	 0x11
#define FUNC_ID_ZW_SEND_NODE_INFORMATION 	 0x12
#define FUNC_ID_ZW_SEND_DATA 	 0x13
#define FUNC_ID_ZW_SEND_DATA_MULTI 	 0x14
#define FUNC_ID_ZW_GET_VERSION 	 0x15
#define FUNC_ID_ZW_SEND_DATA_ABORT 	 0x16
#define FUNC_ID_ZW_RF_POWER_LEVEL_SET 	 0x17
#define FUNC_ID_ZW_SEND_DATA_META 	 0x18
#define FUNC_ID_ZW_RESERVED_SD 	 0x19
#define FUNC_ID_ZW_RESERVED_SDM 	 0x1A
#define FUNC_ID_ZW_RESERVED_SRI 	 0x1B
#define FUNC_ID_ZW_GET_RANDOM 	 0x1C
#define FUNC_ID_MEMORY_GET_ID 	 0x20
#define FUNC_ID_MEMORY_GET_BYTE 	 0x21
#define FUNC_ID_MEMORY_PUT_BYTE 	 0x22
#define FUNC_ID_MEMORY_GET_BUFFER 	 0x23
#define FUNC_ID_MEMORY_PUT_BUFFER 	 0x24
#define FUNC_ID_SERIAL_API_GET_APPL_HOST_MEMORY_OFFSET 	 0x25
#define FUNC_ID_DEBUG_OUTPUT 	 0x26
#define FUNC_ID_AUTO_PROGRAMMING                       	 0x27
#define FUNC_ID_CLOCK_SET 	 0x30
#define FUNC_ID_CLOCK_GET 	 0x31
#define FUNC_ID_CLOCK_CMP 	 0x32
#define FUNC_ID_RTC_TIMER_CREATE 	 0x33
#define FUNC_ID_RTC_TIMER_READ 	 0x34
#define FUNC_ID_RTC_TIMER_DELETE 	 0x35
#define FUNC_ID_RTC_TIMER_CALL 	 0x36
#define FUNC_ID_ZW_SET_LEARN_NODE_STATE 	 0x40
#define FUNC_ID_ZW_GET_NODE_PROTOCOL_INFO 	 0x41
#define FUNC_ID_ZW_SET_DEFAULT 	 0x42
#define FUNC_ID_ZW_NEW_CONTROLLER 	 0x43
#define FUNC_ID_ZW_REPLICATION_COMMAND_COMPLETE 	 0x44
#define FUNC_ID_ZW_REPLICATION_SEND_DATA 	 0x45
#define FUNC_ID_ZW_ASSIGN_RETURN_ROUTE 	 0x46
#define FUNC_ID_ZW_DELETE_RETURN_ROUTE 	 0x47
#define FUNC_ID_ZW_REQUEST_NODE_NEIGHBOR_UPDATE 	 0x48
#define FUNC_ID_ZW_APPLICATION_UPDATE 	 0x49
#define FUNC_ID_ZW_APPLICATION_CONTROLLER_UPDATE 	 0x49
#define FUNC_ID_ZW_ADD_NODE_TO_NETWORK 	 0x4A
#define FUNC_ID_ZW_REMOVE_NODE_FROM_NETWORK 	 0x4B
#define FUNC_ID_ZW_CREATE_NEW_PRIMARY 	 0x4C
#define FUNC_ID_ZW_CONTROLLER_CHANGE 	 0x4D
#define FUNC_ID_ZW_RESERVED_FN 	 0x4E
#define FUNC_ID_ZW_RESERVED_AR 	 0x4F
#define FUNC_ID_ZW_REQUEST_NODE_INFO 	 0x60
#define FUNC_ID_ZW_REMOVE_FAILED_NODE_ID 	 0x61
#define FUNC_ID_ZW_IS_FAILED_NODE_ID 	 0x62
#define FUNC_ID_ZW_REPLACE_FAILED_NODE 	 0x63
#define FUNC_ID_ZW_GET_ROUTING_MAX 	 0x64
#define FUNC_ID_ZW_SET_ROUTING_MAX 	 0x65
#define FUNC_ID_ZW_IS_PRIMARY_CTRL 	 0x66
#define FUNC_ID_ZW_AES_ECB 	 0x67
#define FUNC_ID_ZW_SET_LEARN_MODE 	 0x50
#define FUNC_ID_ZW_ASSIGN_SUC_RETURN_ROUTE 	 0x51
#define FUNC_ID_ZW_ENABLE_SUC 	 0x52
#define FUNC_ID_ZW_REQUEST_NETWORK_UPDATE 	 0x53
#define FUNC_ID_ZW_SET_SUC_NODE_ID 	 0x54
#define FUNC_ID_ZW_DELETE_SUC_RETURN_ROUTE 	 0x55
#define FUNC_ID_ZW_GET_SUC_NODE_ID 	 0x56
#define FUNC_ID_ZW_SEND_SUC_ID 	 0x57
#define FUNC_ID_ZW_RESERVED_ASR 	 0x58
#define FUNC_ID_ZW_REDISCOVERY_NEEDED 	 0x59
#define FUNC_ID_ZW_EXPLORE_REQUEST_INCLUSION 	 0x5E
#define FUNC_ID_TIMER_START 	 0x70
#define FUNC_ID_TIMER_RESTART 	 0x71
#define FUNC_ID_TIMER_CANCEL 	 0x72
#define FUNC_ID_TIMER_CALL 	 0x73
#define FUNC_ID_GET_ROUTING_TABLE_LINE 	 0x80
#define FUNC_ID_GET_TX_COUNTER 	 0x81
#define FUNC_ID_RESET_TX_COUNTER 	 0x82
#define FUNC_ID_STORE_NODEINFO 	 0x83
#define FUNC_ID_STORE_HOMEID 	 0x84
#define FUNC_ID_LOCK_ROUTE_RESPONSE 	 0x90
#define FUNC_ID_ZW_SEND_DATA_ROUTE_DEMO 	 0x91
#define FUNC_ID_SERIAL_API_TEST 	 0x95
#define FUNC_ID_SERIAL_API_APPL_SLAVE_NODE_INFORMATION 	 0xA0
#define FUNC_ID_APPLICATION_SLAVE_COMMAND_HANDLER 	 0xA1
#define FUNC_ID_ZW_SEND_SLAVE_NODE_INFORMATION 	 0xA2
#define FUNC_ID_ZW_SEND_SLAVE_DATA 	 0xA3
#define FUNC_ID_ZW_SET_SLAVE_LEARN_MODE 	 0xA4
#define FUNC_ID_ZW_GET_VIRTUAL_NODES 	 0xA5
#define FUNC_ID_ZW_IS_VIRTUAL_NODE 	 0xA6
#define FUNC_ID_ZW_RESERVED_SSD 	 0xA7
#define FUNC_ID_APPLICATION_COMMAND_HANDLER_BRIDGE 	 0xA8
#define FUNC_ID_ZW_SEND_DATA_BRIDGE 	 0xA9
#define FUNC_ID_ZW_SEND_DATA_META_BRIDGE 	 0xAA
#define FUNC_ID_ZW_SEND_DATA_MULTI_BRIDGE 	 0xAB
#define FUNC_ID_PWR_SETSTOPMODE 	 0xB0
#define FUNC_ID_PWR_CLK_PD 	 0xB1
#define FUNC_ID_PWR_CLK_PUP 	 0xB2
#define FUNC_ID_PWR_SELECT_CLK 	 0xB3
#define FUNC_ID_ZW_SET_WUT_TIMEOUT 	 0xB4
#define FUNC_ID_ZW_IS_WUT_KICKED 	 0xB5
#define FUNC_ID_ZW_WATCHDOG_ENABLE 	 0xB6
#define FUNC_ID_ZW_WATCHDOG_DISABLE 	 0xB7
#define FUNC_ID_ZW_WATCHDOG_KICK 	 0xB8
#define FUNC_ID_ZW_SET_EXT_INT_LEVEL 	 0xB9
#define FUNC_ID_ZW_RF_POWER_LEVEL_GET 	 0xBA
#define FUNC_ID_ZW_GET_NEIGHBOR_COUNT 	 0xBB
#define FUNC_ID_ZW_ARE_NODES_NEIGHBOURS 	 0xBC
#define FUNC_ID_ZW_TYPE_LIBRARY 	 0xBD
#define FUNC_ID_ZW_SEND_TEST_FRAME 	 0xBE
#define FUNC_ID_ZW_GET_PROTOCOL_STATUS 	 0xBF
#define FUNC_ID_ZW_SET_PROMISCUOUS_MODE 	 0xD0
#define FUNC_ID_PROMISCUOUS_APPLICATION_COMMAND_HANDLER 	 0xD1
#define FUNC_ID_ZW_WATCHDOG_START 	 0xD2
#define FUNC_ID_ZW_WATCHDOG_STOP 	 0xD3
#define FUNC_ID_SERIAL_API_READY 	 0xEF
#define FUNC_ID_PROPRIETARY_0 	 0xF0
#define FUNC_ID_PROPRIETARY_1 	 0xF1
#define FUNC_ID_PROPRIETARY_2 	 0xF2
#define FUNC_ID_PROPRIETARY_3 	 0xF3
#define FUNC_ID_PROPRIETARY_4 	 0xF4
#define FUNC_ID_PROPRIETARY_5 	 0xF5
#define FUNC_ID_PROPRIETARY_6 	 0xF6
#define FUNC_ID_PROPRIETARY_7 	 0xF7
#define FUNC_ID_PROPRIETARY_8 	 0xF8
#define FUNC_ID_PROPRIETARY_9 	 0xF9
#define FUNC_ID_PROPRIETARY_A 	 0xFA
#define FUNC_ID_PROPRIETARY_B 	 0xFB
#define FUNC_ID_PROPRIETARY_C 	 0xFC
#define FUNC_ID_PROPRIETARY_D 	 0xFD
#define FUNC_ID_PROPRIETARY_E 	 0xFE
#define FUNC_ID_ZW_ECHO_REQUEST 	 FUNC_ID_PROPRIETARY_0
#define FUNC_ID_ZW_ECHO_REQUEST_LONG 	 FUNC_ID_PROPRIETARY_1
#define FUNC_ID_UNKNOWN 	 0xFF


/* Mode parameters to ZW_AddNodeToNetwork */
#define ADD_NODE_ANY          1
#define ADD_NODE_CONTROLLER   2
#define ADD_NODE_SLAVE        3
#define ADD_NODE_EXISTING     4
#define ADD_NODE_STOP         5
#define ADD_NODE_STOP_FAILED  6
#define ADD_NODE_RESERVED     7
#define ADD_NODE_HOME_ID      8
#define ADD_NODE_SMART_START  9

/* Callback states from ZW_AddNodeToNetwork */
#define ADD_NODE_STATUS_LEARN_READY          1
#define ADD_NODE_STATUS_NODE_FOUND           2
#define ADD_NODE_STATUS_ADDING_SLAVE         3
#define ADD_NODE_STATUS_ADDING_CONTROLLER    4
#define ADD_NODE_STATUS_PROTOCOL_DONE        5
#define ADD_NODE_STATUS_DONE                 6
#define ADD_NODE_STATUS_FAILED               7
#define ADD_NODE_STATUS_NOT_PRIMARY          0x23

/* Transmit frame option flags */
#define TRANSMIT_OPTION_ACK                     0x01    /* request acknowledge from destination node */
#define TRANSMIT_OPTION_LOW_POWER               0x02    /* transmit at low output power level (1/3 of normal RF range) */
#define TRANSMIT_OPTION_MULTICAST_AS_BROADCAST  0x02    /* The multicast frame should be send as a broadcast */
#ifdef ZW_SLAVE
#define TRANSMIT_OPTION_RETURN_ROUTE            0x04    /* request transmission via return route */
#endif
#define TRANSMIT_OPTION_AUTO_ROUTE              0x04    /* request retransmission via repeater nodes */
/* do not use response route - Even if available */
#define TRANSMIT_OPTION_NO_ROUTE                0x10
/* Use explore frame if needed */
#define TRANSMIT_OPTION_EXPLORE                 0x20

/* Z-Wave Command Classes */
#define COMMAND_CLASS_BASIC                                                              0x20
#define BASIC_SET                                                                        0x01

