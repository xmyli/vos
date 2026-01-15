# vos

Hobby UNIX-like kernel for QEMU's AArch64 'virt' platform

### Features
- Memory Management
	- Virtual memory for both kernel space (Higher-half kernel) and user space addresses
	- Buddy allocator for allocation of page frames
	- Slab allocator for allocation of arbitrary kernel objects
- Process Management
	- Interrupt-based preemptive multitasking
	- Round-robin scheduler
	- Common UNIX system calls
- File System
	- Journaling file system based on ext3
	- Block cache, inodes, and file descriptors interface
- Networking
	- TCP, UDP, IP, ARP, and Ethernet protocols implemented from scratch
	- Sockets interface

### System Calls
```c
// Process Management
int fork();
int exec(char *, char **);
int wait();
void exit(int);
int pipe(int *);

// File System
int open(char *, int, int, int);
void close(int);
int copy(int);
size_t read(int, void *, size_t);
size_t write(int, void *, size_t);

// Networking
size_t receive(int, void *, size_t, uint32_t *, uint16_t *);
size_t transmit(int, void *, size_t, uint32_t, uint16_t);
int socket(int);
int bind(int, int);
int connect(int, int, int);
int listen(int);
int accept(int);
```

### Testing
1. `GNU_PREFIX` variable in `Makefile` should be set to a valid compiler toolchain targeting `aarch64-none-elf`.
2. `qemu-system-aarch64` must be installed.
3. `make test` will build and run the kernel.
4. The shell is automatically run, and can be used to execute the user programs:
	- ls
		- List directory contents
	- cat
		- Print content of file to standard output, such as the included testing file `test.txt`
	- pong
		- Testing UDP
	- server
		- Testing TCP
	- client
		- Testing TCP
5. `udp_test.py`, `tcp_server.py`, and `tcp_client.py` can be used along with the included user programs to test networking functionalities.
	- For testing UDP, run:
		1. `pong`
		2. `udp_test.py`
	- For testing TCP, run:
		1. `tcp_server.py`
		2. `client`
		3. `server`
		4. `tcp_client.py`

