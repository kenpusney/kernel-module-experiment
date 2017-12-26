#obj-m += abckernel.o
#abckernel-objs := start.o stop.o
#obj-m += chardev.o
obj-m += syscall.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean