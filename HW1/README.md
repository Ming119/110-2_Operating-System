# [2966473] 110-2 Operating System

## Homework Assignment #1

### 108590050 李浩銘

### Written exercises

#### Chap.1
1.9:
*Direct memory access* is used for high-speed I/O devices in order to avoid increasing the CPU’s execution load.

(a) How does the CPU interface with the device to coordinate the transfer?
> The CPU send commands and status requests to the device through some special registers. When those register are writte, the device will notice and take the appropriate action.



(b) How does the CPU know when the memory operations are complete?
> The device will write to the special register or generate an interrupt, to notify the CPU the memory operations are complete.



(c) The CPU is allowed to execute other programs while the DMA controller is transferring data. Does this process interfere with the execution of the user programs? If so, describe what forms of interference are caused.
> This process does interfere with the execution of the user programs. While the DMA is active, any CPU program that would be capable of using all the memory bus cycles could run more slowly.



#### Chap.2
2.7: 
What are the two models of *interprocess communication*? What are the strengths and weakness of the two approaches?
> Shared-memory model and Message-passing model.  

> Strength of `shared-memory`:
> The shared-memory communication is faster than the message-passing communication.

> Weakness of `shared-memory`:
> The shared-memory communication have to prevent two or more processes writing to the same location simultaneously.

> Strength of `message-passing`:
> The message-passing communication is easier to implement than the shared-memory communication.

> Weakness of `message-passing`:
> The message-passing communication have to setup connection, therefore it is slower than shared-memory communication.



2.10: 
What is the main advantage of the *microkernel* approach to system design? How do user programs and system services interact in a microkernel architecture? What are the disadvantages of using the microkernel approach?
> The main advantage of the microkernel is keeping the kernel as small and simple as possible. Therefore, it is easier to maintain. User programs and system services interact in a microkernel architecture by using interprocess communication and conveyed by the operating system. The disadvantages of microkernel is the decreasesing of performance because of the increasing of system function overhead.



#### Chap.3
3.1:
Describe the differences among short-term, medium-term, and long-term scheduling.
> `Short-term scheduling`: Select one of the processes from the ready queue.

> `Medium-term scheduling`: Swap out a process from main memory.

> `Long-term scheduling`: Select a process from the storage pool in the secondary memory and load it into the ready queue in the main memory.



3.11:
What are the benefits and the disadvantages of each of the following? Consider both the system level and the programmer level.

(a) Synchronous and asynchronous communication.
> Synchronous communication allows a rendezvous between the sender and receiver. However, the rendezvous may not be required when the message is delivered asynchronously.

(b) Automatic and explicit buffering
> Automatic buffering ensure that the sender will never have to block while waiting to copy a message, but it will waste the memory.

> Explicit buffering will not waste the memory but the sender may be blocked while waiting for available space in the queue.

(c) Send by copy and send by reference
> Send by copy does not allow the receiver to alter the state of the parameter, but send by reference does.

(d) Fixed-sized and variable-sized messages
> A buffer with a specific size can hold a known number of Fixed-sized messages. However, the number of variable-sized messages that can be held by such a buffer is unknown.



### Programming exercises

#### Programming problems
- [Chap 2.15](./Chap2.15/README.md)
- [Chap 3.14](./Chap3.14/README.md)
- [Chap 3.15](./Chap3.15/README.md)
- [Chap 3.20](./Chap3.20/README.md)

#### Programming projects
- [Chap.2 Project](./Chap2Project/README.md)
- [Chap.3 Project 1](./Chap3Project1/README.md)