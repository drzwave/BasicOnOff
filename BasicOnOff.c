/* ************BasicOnOff.c***************************************************
 * BasicOnOff provides a very minimal utility to interface to the Z-Wave 
 * SerialAPI and provides a couple of command line commands to turn a light
 * on, off or dim.
 * Z-Wave documentation is at: https://www.silabs.com/support/z-wave
 * SerialAPI documentation: INS12350 Serial API Host Appl. Prg. Guide
 */



#include <stdio.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

void usage() {
    printf("\nBasicOnOff NodeID CMD [options]\n");
    printf("BasicOnOff will send CMD to NodeID over the Z-Wave interface in BasicOnOff.ini\n");
    printf("NodeID is decimal\n");
    printf("If BasicOnOff.ini doesn't exist, the user is prompted to enter it\n");
    printf("Ex: BasicOnOff include - put the Z-Wave interface into inclusion (add) mode and returns the NodeID or 00 if none\n");
    printf("    BasicOnOff Exclude - put the Z-Wave interface into exclusion (remove) mode\n");
    printf("    BasicOnOff 3 on    - Send a Basic ON to node 003\n");
    printf("    BasicOnOff 3 on    - Send a Basic ON to node 003\n");
    printf("    BasicOnOff info    - Print details of the Z-Wave network\n");
}

int comport;
int main(int argc, char *argv[]) {
    if (argc<2) {
        usage();
        return(-1);
    }
    comport = open("COM7",
}   // Main
