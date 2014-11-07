Network-Simulation
==================

Welcome to the 7-Node Network Simulator.
By: Mia Kilborn

MAKING AND RUNNING
==================
MAKE --
1. To build the project, navigate to the root directory of the project (same location as this README file) in a terminal window.
2. Type 'make' on the command line. This will compile 7 executable files stored in the bin/ directory 

RUN --
- To run all nodes in the same window, type 'make run' on the command line. If the project has not been built yet, this command will build the project before running it.
- To run each node in separate windows, open 7 terminal windows and run './bin/n{x}' in each, where {x}  is the node number to execute.
- Note that if not all nodes are started, exiting the program will not run smoothly.

INPUT --
- Input is expected to be of the format 'filename.txt n{x}' and will exit upon bad input.

EXITING --
- If you need to exit the program at any time during execution, the program will catch a ctrl+c signal and end background processes before exiting
- If you can wait 


OTHER NOTES
===========
- When a node prints to the screen, it prints its name and number in square brackets first
- Network delay is between 1 and 2,000 milliseconds
- If the program does not terminate properly, you must manually kill the processes, they called n1 through n7
- Running 'make clean' will empty the bin directory
