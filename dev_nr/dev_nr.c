#include <linux/module.h>
#include <linux/init.h>
/* Meta information  */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("SUSSING GNU/LINUX");
MODULE_DESCRIPTION("Registers a device nr and implement callback options");


/**
@brief: this funciton is called when the device is opended
*/
static int driver_open(struct inode *device_file, struct file *instance) {
    printk("dev_nr-open was called\n");
    return 0;
}


/**
 * @brief This function is called, when the device file is closed
 */
static int driver_close(struct inode *device_file, struct file *instance) {
	printk("dev_nr - close was called!\n");
	return 0;
}


static struct file_operations fops = 
{
    .owner = THIS_MODULE,
    .open = driver_open,
    .release = driver_close,
};

#define MYMAJOR 90

static int __init ModuleInit(void) {
	int retval;
	printk("Hello, Kernel!\n");
	/* register device nr. */
	retval = register_chrdev(MYMAJOR, "my_dev_nr", &fops);
	if(retval == 0) {
		printk("dev_nr - registered Device number Major: %d, Minor: %d\n", MYMAJOR, 0);
	}
	else if(retval > 0) {
		printk("dev_nr - registered Device number Major: %d, Minor: %d\n", retval>>20, retval&0xfffff);
	}
	else {
		printk("Could not register device number!\n");
		return -1;
	}
	return 0;
}



/*
@brief: when module is removed from the kernel

*/
static void __exit ModuleExit(void)
{
    printk("Kernel mod exit\n");
}


module_init(ModuleInit);
module_exit(ModuleExit);