#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/fs.h>
#include <linux/interrupt.h>
#include "main.h"

MODULE_LICENSE("GPL");

/* stores the original divbyzero handler */
unsigned long orig_divbyzero = 0;

/* stores the count of divzero exceptions */
unsigned long total_count = 0;

/* replace original divbyzero handler with this */
extern void __wrapper_divbyzero(void);

/* You may refer to Intel Sofware Manual for detailed description. */
struct idt_entry
{
	unsigned short lower16; /*lower 16 bits of interrupt handler */
	unsigned short sel;
	unsigned short flags;
	unsigned short higher16; /*higher 16 bits of interrupt handler */
} __attribute__((packed));

struct idt_desc
{
	unsigned short size;   /* size of idt table */
	unsigned long address; /* base address of idt table */
} __attribute__((packed));


/* write the base and size of idt table */
static void imp_load_idt(const struct idt_desc *dtr)
{
    asm volatile("lidt %0"::"m" (*dtr));
}

/* read the base and size of idt table  */
static void imp_store_idt(struct idt_desc *dtr)
{
    asm volatile("sidt %0":"=m" (*dtr));
}

/* Returns the address of routine from idt entry
 */
static unsigned long _read_idt_entry(struct idt_entry *e)
{
	/* NOT_IMPLEMENTED */
	return 0;
}

/* Sets the routine address to addr in an idt entry
 */
static void _write_idt_entry(struct idt_entry *e, unsigned long addr)
{
	/* NOT_IMPLEMENTED */
}

static void stop_tracking_divbyzero(void)
{
	/* stop tracking divbyzero if enabled */
	if (orig_divbyzero != 0)
	{
	/* NOT_IMPLEMENTED */
		orig_divbyzero = 0;
	}
}

static void start_tracking_divbyzero(void)
{
	/* start tracking divbyzero if not enabled */
	if (orig_divbyzero == 0)
	{
	/* NOT_IMPLEMENTED */
	/* Overwrite divbyzero exception handler with
     * __wrapper_divbyzero (defined in wrapper.S)
     */
	}
}

static long device_ioctl(struct file *file, unsigned int ioctl, unsigned long arg)
{
    void __user *argp = (void __user*)arg;

    switch (ioctl)
    {
        case START_DIVBYZERO:
            start_tracking_divbyzero();
            break;
        case STOP_DIVBYZERO:
            stop_tracking_divbyzero();
            break;
        case STATS_DIVBYZERO:
            /* total_count stores the total number of divbyzero
             * exceptions. copy_to_user copies from kernel memory
             * to user memory.
             */
            copy_to_user(argp, &total_count, sizeof(unsigned long));
            break;
        default:
            printk("NOT a valid ioctl\n");
            return 1;
    }
    return 0;
}

static struct file_operations fops = 
{
    .unlocked_ioctl = device_ioctl,
};

int start_module(void)
{
    if (register_chrdev(MAJOR_NUM, MODULE_NAME, &fops) < 0)
    {
        printk("PANIC: aos module loading failed\n");
        return 1;
    }
    printk("aos module loaded sucessfully\n");
    return 0;
}

void exit_module(void)
{
	stop_tracking_divbyzero();
    unregister_chrdev(MAJOR_NUM, MODULE_NAME);
    printk("aos module unloaded sucessfully\n");
}

module_init(start_module);
module_exit(exit_module);
