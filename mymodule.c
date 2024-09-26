#include <linux/module.h>
#include <linux/init.h>

/* Meta information  */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("SUSSING GNU/LINUX");

static int __init ModuleInit(void)
{
    printk("Hello, Kernel!\n");
    return 0;   //-1 negative value error
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