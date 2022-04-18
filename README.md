# Bi-Directional-IPC
Bi-directional IPC through Shared  Bounded Buffers

To establish an IPC channel with the server through shared memory. Both the server and client programs are invoked through command line, with an integer provided as the key of the shared memory. 
For example:
./project3_server 365 
./client 365 

Here 365 is the key of the shared memory. It serves as a channel identifier. Processes that attach a shared memory segment with the same key will have the corresponding page table entr[ies] mapped to the same physical frame[s].
