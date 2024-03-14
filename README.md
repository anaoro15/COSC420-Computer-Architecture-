# COSC420-Computer-Architecture-
Simulator For a Modern Processor System in C++
This program is executing a simulator for a modern processor system. This
system includes:
• A two-way set associative cache memory of 512 bytes.
• Cache blocks of 64 bytes each.
• An additional "victim's cache" capable of holding two blocks.

The primary cache uses the LRU (Least Recently Used) algorithm for replacing lines. When a block is
removed from the main cache, it first goes to the victim's cache before being written back to memory. The victim's cache operates on a FIFO (First In, First Out) basis. A new block entering the victim's cache displaces the oldest block. If an address is needed and not found in the main cache but is in the victim's cache, it's moved back to the main cache (and concurrently removed from the victim's cache). This does not count as a cache miss.

This software will process the file 'data.txt', which simulates cache requests and calculates the total number of misses. The solution should be specific to this task without options for customization like adjustable cache or block sizes.
The file contains 1 million addresses.

Each record in the file has two parts: a Code and an Address (in hexadecimal).
The Code, a single-digit number, is not used in the simulation:
0: Data read address
1: Data write address
2: Instruction fetch address

The Address is the key information for the simulation.
Example Entries in the Data File:
2 415130
0 1010acac
2 415134
Addresses are 32-bit. If an address is shorter, it should be zero-padded.
