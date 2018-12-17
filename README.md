# BasicOnOff
Basic Z-Wave SerialAPI interface to get started

BasicOnOff is a minimal demonstration program to get started with Z-Wave and the SerialAPI using a USB Z-Wave interface. The program is a very simple command line program that will add a node to a Z-Wave network and then turn a switch on or off.

Note that this is a _DEMO_ program! It is *NOT* a full-featured Z-Wave interface. It is meant as a very first step in learning more about Z-Wave and to get a basic understanding of how to interface to Z-Wave devices. The code is provided AS-IS and without support. Please read the comments in the code and figure any problems out yourself.

# Setup
   1. Purchase a UZB3 from Digikey.com - be sure you get the proper frequency for your region (US, EU, ANZ)
   2. Purchase a Z-Wave device - a wall switch or dimmer is ideal - See www.Z-WaveAlliance.org for links to all Z-Wave certified devices
   3. Install gcc if you don't already have it
   4. Execute the BasicOnOff.sh script to compile the program
   5. Plug in the UZB and with wall switch
   6. Identify the /dev/tty (Linux) port for the UZB
   7. BasicOnOff is a command line program:
        - BasicOnOff default            Reset the UZB to factory default
        - BasicOnOff reset              Soft Reset the UZB
        - BasicOnOff include            Add a Node to the Z-Wave network. Returns the decimal value of the NodeID
        - BasicOnOff exclude            Remove a Node 
        - BasicOnOff info               Print details of the Z-Wave network including a list of NodeIDs
        - BasicOnOff <NodeID> on        Send a BASIC ON to NodeID
        - BasicOnOff <NodeID> off       Send a BASIC OFF to NodeID
        - BasicOnOff <NodeID> dim <dim Level> [<Duration>]      Send Dim Level (0-99) to NodeID with optional ramp Duration (0-99 seconds)
        - NodeID is the decimal NodeID of the wall switch or other device
    8. Change the UART_PORT define in the BasicOnOff.c file to use a different UART port

See the code for more details.

Only tested on Linux on a Raspberry Pi. Other platforms will require more work...

- How to get this repository
   - git clone https://<YourUserName>@github.org/DrZWave/BasicOnOff.git <directory_name> - will create a local repository
    - git status -uno - Prints out which files in your local directory have changed or need to be checked in
    - git pull - updates local directory/repository with the main branch
    - git add - adds a file to the repository
    - git commit -a -m "comment goes here" - commits changed files TO YOUR LOCAL REPOSITORY - not to GitHub!
    - git push - pushes your commits up to BitBucket - always do a GIT PULL before committing
    - See the many GIT tutorials for more details

# Contacts
- Eric Ryherd - DrZWave@silabs.com

