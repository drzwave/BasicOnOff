/* ************BasicOnOff.c***************************************************
 * BasicOnOff provides a very minimal utility to interface to the Z-Wave 
 * SerialAPI and provides a couple of command line commands to turn a light
 * on, off or dim.
 * This is JUST A DEMO! It is not intended as a full-featured implementation!
 * This program provides enough functionality to show you how to get 
 * started using Z-Wave at a most basic level.
 * The recommended controller solution is to use Z/IP an Z-Ware as described
 * here: https://www.silabs.com/products/development-tools/software/z-wave/controller-sdk/z-ip-gateway-sdk
 * Z-Wave documentation is at: https://www.silabs.com/support/z-wave
 * SerialAPI documentation: INS12350 Serial API Host Appl. Prg. Guide
 *
 * You will likely have to recompile this code with the proper setting for UART_PORT - see below
 */



#include <stdio.h>
#include <fcntl.h>      /* File Control Definition */
#include <termios.h>    /* Terminal Control Definition */
#include <unistd.h>     /* read/write definition */
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "ZWave.h"      /* Z-Wave defines */

// Typically a UZB is /dev/ttyACM0 and the UART on the Raspberry Pi GPIO pins is /dev/ttyAMA0
//#define UART_PORT "/dev/ttyAMA0"
#define UART_PORT "/dev/ttyACM0"

// RX/TX UART buffer size. Most Z-Wave frames are under 64 bytes.
#define BUF_SIZE 128

void usage() {
    printf("\nBasicOnOff NodeID CMD [options]\n");
    printf("BasicOnOff will send CMD to NodeID over the Z-Wave interface in BasicOnOff.ini\n");
    printf("NodeID is decimal\n");
    printf("Ex: BasicOnOff include - put the Z-Wave interface into inclusion (add) mode and returns the NodeID or 00 if none\n");
    printf("    BasicOnOff exclude - put the Z-Wave interface into exclusion (remove) mode\n");
    printf("    BasicOnOff 3 on    - Send a Basic ON to node 003\n");
    printf("    BasicOnOff 123 off - Send a Basic OFF to node 123\n");
//    printf("    BasicOnOff 012 dim 55 - Send a Basic SET to node 012 with a dim value of 55%\n");
    printf("    BasicOnOff info    - Print details of the Z-Wave network\n");
    printf("    BasicOnOff reset   - Soft Reset the UZB\n");
    printf("    BasicOnOff default - Reset the UZB to factory defaults - deletes the Z-Wave network and picks a new random HomeID\n");
}

int uzb;
char readBuf[BUF_SIZE];
char sendBuf[BUF_SIZE];

unsigned char checksum(char *pkt, int len) { /* returns the checksum of PKT */
    int i;
    int sum=0xff;
    for(i=0;i<len;i++) {
        sum ^= *(pkt+i);
    }
    return(sum&0x0FF);
}

int GetSerial(char *pkt) { /* Get SerialAPI frame from UART. Returns the length of pkt and data in PKT */
    /* strips the SOF/LEN/Type and checksum and ACKs the frame if the checksum is OK */
    int i,j,len,type,index;
    char ack=ACK;
    int searching=true;
    i=0;

    while (searching) {                     // Seach for the SOF is complete when we find the SOF and type fields
        for (j=0; i<1 && j<250; j++) {      // wait up to about 250ms - if waiting for a routed frame this might need to be longer
            i=read(uzb,pkt,1);
            if (i==1 && readBuf[0]!=SOF) i=0;  // drop anything until SOF
            usleep(1000);                   // Wait 1ms
        }
        if (i!=1) {
            return(-1);   // no frame so just return -1
        }
        i=read(uzb,pkt,1);                  // LEN (includes LEN and TYPE)
        len=pkt[0];
        i=read(uzb,pkt,1);                  // TYPE (must be 00 or 01)
        type=pkt[0];
        if (type<=0x01) searching=false;    // TODO could also qualify that LEN is less than 64?
    }
    i=0; index=0;
    for (j=0; j<1000 && index<(len-1); j++) { 
        i=read(uzb,&pkt[index],len);
        if (i<1) {                          // Nothing yet
            usleep(100);                    // Wait 100uS
        }
        if (i>0) {
            index+=i;
        }
    }
    // TODO add the checksum check here
    write(uzb,&ack,1);   // ACK the frame
    return(len-2);      // remove LEN and TYPE
} /* GetSerial */

int SendSerial(const char *pkt,int len) { /* send SerialAPI command PKT of length LEN after encapsulating */
    /* Returns ACK/NAK/CAN if the packet was delivered to the UZB, -1 if no response */
    /* if not ACKed, will try a total of 3 times */
    /* SerialAPI format:
     * SOF      =0x01
     * LEN      =Number of bytes in this frame not including SOF and CHECKSUM (or all bytes-2)
     * Type     =0x00=Request, 0x01=Response
     * FUNCID   =SerialAPI command byte
     * PARAMS(n)=Command parameters and/or data bytes
     * CHECKSUM = XOR of all bytes except SOF. Should be 0 if checksum is OK. NAK is sent if checksum fails.
     */
    char buf[BUF_SIZE];
    int i,j;
    int sendStatus;
    int retry;
    int ack=ACK;
    buf[0]=SOF;
    buf[1]=len+2; // add LEN, TYPE
    buf[2]=REQUEST;
    memcpy(&buf[3],pkt,len);
    buf[len+3]=checksum(&buf[1],len+2);
#ifdef DEBUG // tx debug
    printf("Sending");
    for (i=0;i<(len+4); i++) {
        printf(" %02X",buf[i]);
    }
    printf("\n");
#endif
    for (retry=1;retry<=3;retry++) {    // retry up to 3 times
        tcflush(uzb,TCIFLUSH);  // purge the UART Rx Buffer
        write(uzb,buf,len+4);   // Send the frame to the UZB
        sendStatus=0;
        usleep(10000); // wait 10ms then read the ACK
        sendStatus = read(uzb,readBuf,1);          // Get the ACK/NAK/CAN
        if (sendStatus==1) {
            if (readBuf[0]==ACK) break; // Got the ACK so break
            write(uzb,&ack,1);          // Got something else so try sending an ACK to clear
        }
        sleep(2);      // wait a bit and try again
    }
    if (sendStatus!=1) {
        printf("UART Timeout\r\n");
        return(-1);
    }
    return(readBuf[0]);
} /* SendSerial */

int main(int argc, char *argv[]) { /*****************MAIN*********************/
    struct termios Settings; 
    int ack,len,i,j;
    int NodeID;

    if (argc<2) {
        usage();
        return(-1);
    }

    /* setup the UART to 115200, 8 bits, no parity, 2 stop bit. */
    uzb = open(UART_PORT,O_RDWR | O_NOCTTY | O_NONBLOCK); /* UZB plugged into a Linux machine is normally at /dev/ttyACM0 */
    if (uzb<0) { printf("Error opening %s\n",UART_PORT); return(-1);}
    tcgetattr(uzb,&Settings);
    cfsetispeed(&Settings,B115200);
    cfsetospeed(&Settings,B115200);

    Settings.c_cflag |= CLOCAL; // ignore model control lines
    Settings.c_cflag |= CREAD; // enable receiver
    Settings.c_cflag &= ~PARENB;
    Settings.c_cflag &= ~CSTOPB;
    Settings.c_cflag &= ~CSIZE;
    Settings.c_cflag |= CS8;
    Settings.c_cflag &= ~CRTSCTS;
    Settings.c_iflag &= ~(IXON | IXOFF | IXANY);
    Settings.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    Settings.c_oflag &= ~OPOST;
    Settings.c_cc[VMIN] = BUF_SIZE;
    Settings.c_cc[VTIME] = 1; // wait this many 100mSec if no chars are available yet - need to wait for the ACK 
    if (tcsetattr(uzb,TCSANOW,&Settings)!=0) {
        printf("\n Unable to set UZB attributes");
        return(-2);
    }

    if (strstr("info",argv[1])) { // Get the Z-Wave network info from the UZB
        sendBuf[0]=FUNC_ID_SERIAL_API_GET_INIT_DATA;
        ack=SendSerial(sendBuf,1);
        if (ack!=ACK) {
            printf("Unable to send Z-Wave SerialAPI command API_GET_INIT_DATA %02X",ack);
        } else {
            len=GetSerial(readBuf);
            if (len<20 || readBuf[0]!=FUNC_ID_SERIAL_API_GET_INIT_DATA) {
                printf("Incorrect response = %02X, %02X\n",len,readBuf[0]);
                printf("%02X, %02X\n",readBuf[1],readBuf[2]);
            } else {
                printf("SerialAPI Version=%d\n",readBuf[1]);
                if (readBuf[2]&0x04) printf("Secondary ");
                else                 printf("Primary   ");
                if (readBuf[2]&0x01) printf("Slave      ");
                else                 printf("Controller ");
                if (readBuf[2]&0x08) printf("SIS ");
                else                 printf("    ");
                printf("\nNodes:");
                for (i=0;i<readBuf[3];i++) {
                    for (j=0;j<8;j++) {
                        if (readBuf[i+4]&(1<<j)) {
                            printf(" %03d", i*8+j+1);
                        }
                    }
                }
                printf("\n");
            }
        }
        // Now let's get capabilities
        sendBuf[0]=FUNC_ID_SERIAL_API_GET_CAPABILITIES;
        ack=SendSerial(sendBuf,1);
        if (ack!=ACK) {
            printf("Unable to send Z-Wave SerialAPI command SERIAL_API_GET_CAPABILITIES %02X",ack);
        } else {
            len=GetSerial(readBuf);
            if (len<20 || readBuf[0]!=FUNC_ID_SERIAL_API_GET_CAPABILITIES ) {
                printf("Incorrect response = %02X, %02X\n",len,readBuf[0]);
                printf("%02X, %02X\n",readBuf[1],readBuf[2]);
            } else {
                printf("SerialAPI Ver=%d.%d\n",readBuf[1], readBuf[2]);
                printf("Product Type/Product ID: 0x%x/0x%x\r\n",
                readBuf[5] << 8 | readBuf[6],
                readBuf[7] << 8 | readBuf[8]);
            }
        }
    }   // INFO

    else if (strstr("reset",argv[1])) { // Send a soft reset - takes 1.5s to complete
        sendBuf[0]=FUNC_ID_SERIAL_API_SOFT_RESET;
        ack=SendSerial(sendBuf,1);
        if (ack!=ACK) {
            printf("Unable to send Z-Wave SerialAPI command API_SOFT_RESET %02X",ack);
        } else {
            sleep(1); // The UZB should respond with a START after about 1s
            len=GetSerial(readBuf);
            if (readBuf[0]==FUNC_ID_SERIAL_API_STARTED) {
                printf("UZB softreset complete\n");
            } else {
                printf("UZB softreset failed %02X\n",readBuf[0]);
            }  
        }
    } 

    else if (strstr("default",argv[1])) { // Delete the Z-Wave network and reset to factory defaults
        sendBuf[0]=FUNC_ID_ZW_SET_DEFAULT;
        ack=SendSerial(sendBuf,1);
        if (ack!=ACK) {
            printf("Unable to send Z-Wave SerialAPI command ZW_SET_DEFAULT %02X",ack);
        } else {
            sleep(3);                   // takes ~2.5s for the SetDefault to complete
        }
    }

    else if (strstr("include",argv[1])) { // Enter inclusion mode - return the NodeID and NIF if a node is added
        // Fore more details see the EXCLUDE process which is very similar
        // Inclusion however goes thru PROTOCOL_DONE instead of DONE
        sendBuf[0]=FUNC_ID_ZW_ADD_NODE_TO_NETWORK;
        sendBuf[1]=ADD_NODE_ANY; // any node (ADD_NODE_xx are the same as REMOVE_NODE_xx)
        sendBuf[2]=0xaa; // Callback ID
        ack=SendSerial(sendBuf,3);
        if (ack!=ACK) {
            printf("Unable to send Z-Wave SerialAPI command ZW_ADD_NODE %02X",ack);
            sendBuf[0]=FUNC_ID_SERIAL_API_SOFT_RESET;
            ack=SendSerial(sendBuf,1);          // cleanup
        } else {
            printf("Push Z-Wave button on device\n");
            len=0;
            for (i=0;i<(10*4) && len<1; i++) {           // wait for ~10s for the user to push a button
                len=GetSerial(readBuf);                 // wait for 250ms looking for a command
                if (len>0) {
#ifdef DEBUG
                    printf("\nlen=%d",len);             // enable these to see each step of the callback process
                    for (j=0;j<len;j++) printf(" %02X",readBuf[j]);
#endif
                    if (readBuf[2]==ADD_NODE_STATUS_PROTOCOL_DONE) { // terminate the inclusion process
                        sendBuf[0]=FUNC_ID_ZW_ADD_NODE_TO_NETWORK;
                        sendBuf[1]=ADD_NODE_STOP;
                        sendBuf[2]=0; // Callback ID=NULL to indicate we are done
                        ack=SendSerial(sendBuf,3);
                    } else
                    if (readBuf[2]==ADD_NODE_STATUS_ADDING_SLAVE || readBuf[2]==ADD_NODE_STATUS_ADDING_CONTROLLER) { // The NodeID is valid during this callback
                        printf("Added NodeID=%03d",readBuf[3]); // TODO could print out the NIF here to know more about the device
                        len=0;
                    } else {
                        len=0;
                    }
                }
            }
            if (len>0) {
                printf("\n");
            } else {
                printf("Z-Wave device NOT included\n");
                sendBuf[0]=FUNC_ID_SERIAL_API_SOFT_RESET;
                ack=SendSerial(sendBuf,1);  // cleanup
            }
        }
    } // include

    else if (strstr("exclude",argv[1])) { // Enter exclusion mode - return the NodeID if it was on this network
        // During the exclusion process the controller send send a sequence of callbacks
        // The data coming back is = 0x4B | CallbackID | Status | other data 
        // The typical callback sequence is:
        // 01=controller OK to enter exclusion mode
        // 02=NIF received (button was pushed on a device
        // 03=Slave device being removed (04=controller)
        // 06=Done - must now send a REMOVE_NODE_STOP to terminate exclusion process
        sendBuf[0]=FUNC_ID_ZW_REMOVE_NODE_FROM_NETWORK;
        sendBuf[1]=ADD_NODE_ANY; // any node (ADD_NODE_xx are the same as REMOVE_NODE_xx)
        sendBuf[2]=0xee; // Callback ID
        ack=SendSerial(sendBuf,3);
        if (ack!=ACK) {
            printf("Unable to send Z-Wave SerialAPI command ZW_REMOVE_NODE %02X",ack);
            sendBuf[0]=FUNC_ID_SERIAL_API_SOFT_RESET;
            ack=SendSerial(sendBuf,1);          // cleanup
        } else {
            printf("Push Z-Wave button on device\n");
            len=0;
            for (i=0;i<(10*4) && len<1; i++) {           // wait for ~10s for the user to push a button
                len=GetSerial(readBuf);                 // will wait for 250ms looking for a command
                if (len>0) {
#if 0
                    printf("\nlen=%d",len);             // enable these to see each step of the callback process
                    for (j=0;j<len;j++) printf(" %02X",readBuf[j]);
#endif
                    if (readBuf[2]==ADD_NODE_STATUS_DONE) { // terminate the exclusion process
                        sendBuf[0]=FUNC_ID_ZW_REMOVE_NODE_FROM_NETWORK;
                        sendBuf[1]=ADD_NODE_STOP;
                        sendBuf[2]=0; // Callback ID=NULL to indicate we are done
                        ack=SendSerial(sendBuf,3);
                        printf("\n");
                    } else
                    if (readBuf[2]==ADD_NODE_STATUS_ADDING_SLAVE || readBuf[2]==ADD_NODE_STATUS_ADDING_CONTROLLER) { // The NodeID is valid during this callback
                        printf("Removed NodeID=%03d",readBuf[3]);
                        len=0;
                    } else {
                        len=0;
                    }
                }
            }
            if (len>0) {
                printf("Z-Wave device excluded\n");
            } else {
                printf("Z-Wave device NOT excluded\n");
                sendBuf[0]=FUNC_ID_SERIAL_API_SOFT_RESET;
                ack=SendSerial(sendBuf,1);  // cleanup
            }
        }
    } // exclude

    else if (argc==3 && strstr("on",argv[2])) { // Send a BASIC_ON
            NodeID=atoi(argv[1]);
            printf("nodeID=%d",NodeID);
            sendBuf[0]=FUNC_ID_ZW_SEND_DATA;
            sendBuf[1]=NodeID;
            sendBuf[2]=3; // Length
            sendBuf[3]=0x20; // command class BASIC
            sendBuf[4]=BASIC_SET;
            sendBuf[5]=0xFF; // ON
            sendBuf[6]=TRANSMIT_OPTION_ACK | TRANSMIT_OPTION_AUTO_ROUTE | TRANSMIT_OPTION_EXPLORE; // TXOPTs - use all possible routing options
            sendBuf[7]=0xC0; // callbackID
            ack=SendSerial(sendBuf,8);
            len=GetSerial(readBuf);                 // wait for 250ms - if fails to route this will take longer
            len=0;
            for (i=0;i<7000 && len<1;i++) {     // 2nd callback indicates delivery or not
                len=GetSerial(readBuf);  
                if (len<1) usleep(1000);
            }
            if (len>1 && readBuf[2]==0) printf(" on\n");
            else printf(" failed %02X %02X\n",len, readBuf[2]);
    }  // ON

    else if (argc==3 && strstr("off",argv[2])) { // Send a BASIC_OFF
            NodeID=atoi(argv[1]);
            printf("nodeID=%d",NodeID);
            sendBuf[0]=FUNC_ID_ZW_SEND_DATA;
            sendBuf[1]=NodeID;
            sendBuf[2]=3; // Length
            sendBuf[3]=0x20; // command class BASIC
            sendBuf[4]=BASIC_SET; 
            sendBuf[5]=0x00; // OFF
            sendBuf[6]=TRANSMIT_OPTION_ACK | TRANSMIT_OPTION_AUTO_ROUTE | TRANSMIT_OPTION_EXPLORE; // TXOPTs - use all possible routing options
            sendBuf[7]=0xC1; // callbackID
            ack=SendSerial(sendBuf,8);
            len=GetSerial(readBuf);             // wait for 250ms for the 1st callback which is the ACK that the command is in the radio queue
            len=0;
            for (i=0;i<7000 && len<1;i++) {     // 2nd callback indicates delivery or not
                len=GetSerial(readBuf);  
                if (len<1) usleep(1000);
            }
            if (len>1 && readBuf[2]==0) printf(" off\n");
            else printf(" failed %02X %02X\n",len, readBuf[2]);
    }  // OFF

    // TODO add DIM here...

    else {
        usage();
    }

    close(uzb);
}   /* Main */
