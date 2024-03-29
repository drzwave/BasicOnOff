# BasicOnOff
Basic Z-Wave SerialAPI interface to get started on Posix/Linux

BasicOnOff is a minimal demonstration program to get started with Z-Wave and the SerialAPI using a USB or serial Z-Wave interface. The program is a very simple Posix/Linux command line program that will add a node to a Z-Wave network and then turn a switch on or off. It can also provide version information from the SerialAPI node.

Note that this is a _DEMO_ program! It is *NOT* a full-featured Z-Wave interface. It is meant as a very first step in learning more about Z-Wave and to get a basic understanding of how to interface to Z-Wave devices. The code is provided AS-IS and without support. Please read the comments in the code and figure any problems out yourself.

# Setup
   1. Obtain a device running Z-Wave SerialAPI. This could be a UZB (UZB3 or UZB7) or could be a Silabs Wireless Starter Kit (Pro Kit) or other USB development kit flashed with SerialAPI firmware. Make sure your SerialAPI firmware is configured for the appropriate region (US, EU, ANZ)
   2. Purchase a Z-Wave device - a wall switch or dimmer is ideal - See www.Z-WaveAlliance.org for links to all Z-Wave certified devices
   3. Identify the /dev/tty (Posix/Linux) serial port for the SerialAPI device.
   4. Edit the BasicOnOff.c file to properly set the #define UART_PORT to the serial port device name.
   6. Use the included GCC makefile to build the program. "make debug" adds some debug printing.
   7. Power up your Z-Wave device and make sure your SerialAPI device is attached to your host.
   8. BasicOnOff is a command line program:
```
        - BasicOnOff info               Print details of the Z-Wave network including a list of NodeIDs - use this first to check the UZB
        - BasicOnOff default            Reset the UZB to factory default
        - BasicOnOff reset              Soft Reset the UZB
        - BasicOnOff include            Add a Node to the Z-Wave network. Returns the decimal value of the NodeID
        - BasicOnOff exclude            Remove a Node
        - BasicOnOff <NodeID> on        Send a BASIC ON to NodeID
        - BasicOnOff <NodeID> off       Send a BASIC OFF to NodeID
        - BasicOnOff <NodeID> dim <dim Level> [<Duration>]      Send Dim Level (0-99) to NodeID with optional ramp Duration (0-99 seconds)
        - NodeID is the decimal NodeID of the wall switch or other device
```

See the code for more details.

This has been tested running on Mac OSX as well as Raspberry Pi. Tested using a variety of configurations (including UZB2, UZB3, UZB7 and WSTK with ZG23 (BRD4210A) running SerialAPI.

- How to get this repository
   - git clone https://<YourUserName>@github.org/DrZWave/BasicOnOff.git <directory_name> - will create a local repository
    - git status -uno - Prints out which files in your local directory have changed or need to be checked in
    - git pull - updates local directory/repository with the main branch
    - git add - adds a file to the repository
    - git commit -a -m "comment goes here" - commits changed files TO YOUR LOCAL REPOSITORY - not to GitHub!
    - git push - pushes your commits up to BitBucket - always do a GIT PULL before committing
    - See the many GIT tutorials for more details

# Getting Started
    1. Follow the setup procedure above
    2. BasicOnOff info - use this command first to get the UZB to talk to your MCU. It should return something like:
        - SerialAPI Version 7
        - Primary Controller
        - Nodes: 001 002 003 007 042
    3. BasicOnOff default    - Once you can talk to the UZB, it is best to delete the network and start fresh.
    4. BasicOnOff include    - press the button on a Z-Wave device and join the network. Note the NodeID returned
    5. BasicOnOff on or off to the nodeID you just included!

# Contacts
- Eric Ryherd - DrZWave@silabs.com
