# [2966473] 110-2 Operating System

## Homework Assignment #1

### Programming Project

#### Chap.2 Linux Kernel Modules

#### Team Member
- 108590002 
- 108590029 
- 108590049 
- 108590050 李浩銘

Part I: Creating, loading, and removing kernel modules
- Assignment: Proceed through the steps described above to create the kernel module and to load and unload the module. Be sure to check the counters of the kernel log buffer using *dmesg* to ensure you have properly followed the steps.

Part II: Creating, traversing, and deleting kernel data structures
- In the module entry point, create a linked list containing five *struct_birthday* elements. Traverse the linked list and output its contents to the kernel log buffer. Invoke the *dmesg* command to ensure the list is properly constructed once the kernel module has been loaded.
- In the module exit point, delete the elements from the linked list and return the free memory back to the kernel. Again, invoke the *dmesg* command to check that the list has been removed once the kernel module has been unloaded.

