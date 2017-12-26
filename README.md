Linux Kernel Module examples
========


## Examples

  - `start.c` / `stop.c`: Kernel module in multiple files
  - `chardev.c`: Kernel module to simulate a simple character device
  - `syscall.c`: Kernel module to hijack syscall open.

All code tested under Ubuntu 16.04.

Dependencies:
```bash
apt install linux-headers-$(uname -r) gcc make
```

## Syscall references:

https://syscalls.kernelgrok.com/

