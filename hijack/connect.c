#include <linux/module.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/syscalls.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/version.h>
#include <linux/socket.h>
#include <uapi/linux/in.h>

// Write Protect Bit (CR0:16)
#define CR0_WP 0x00010000

MODULE_LICENSE("GPL");

void **syscall_table;

unsigned long **find_sys_call_table(void);

asmlinkage long (*orig_sys_connect)(int, struct sockaddr __user *, int);

unsigned long **find_sys_call_table()
{
    unsigned long ptr;
    unsigned long *p;

    for (ptr = (unsigned long)sys_close; ptr < (unsigned long)&loops_per_jiffy; ptr += sizeof(void *))
    {

        p = (unsigned long *)ptr;

        if (p[__NR_close] == (unsigned long)sys_close)
        {
            return (unsigned long **)p;
        }
    }

    return NULL;
}

asmlinkage long my_sys_connect(int fd, struct sockaddr __user * addr, int len)
{
    printk(KERN_DEBUG "Connect to %x\n",((struct sockaddr_in*)addr)->sin_addr);

    return orig_sys_connect(fd, addr, len);
}

static int __init syscall_init(void)
{
    unsigned long cr0;

    printk(KERN_DEBUG "Let's do some magic!\n");

    syscall_table = (void **)find_sys_call_table();

    if (!syscall_table)
    {
        printk(KERN_DEBUG "ERROR: Cannot find the system call table address.\n");
        return -1;
    }

    printk(KERN_DEBUG "Found the sys_call_table at %16lx.\n", (unsigned long)syscall_table);

    cr0 = read_cr0();
    write_cr0(cr0 & ~CR0_WP);

    printk(KERN_DEBUG "Houston! We have full write access to all pages. Proceeding...\n");

    orig_sys_connect = syscall_table[__NR_connect];
    syscall_table[__NR_connect] = my_sys_connect;

    write_cr0(cr0);

    return 0;
}

static void __exit syscall_release(void)
{
    unsigned long cr0;

    printk(KERN_DEBUG "I hate you!\n");

    cr0 = read_cr0();
    write_cr0(cr0 & ~CR0_WP);
    syscall_table[__NR_connect] = orig_sys_connect;
    write_cr0(cr0);
}

module_init(syscall_init);
module_exit(syscall_release);
