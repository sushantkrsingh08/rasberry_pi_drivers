#include <linux/module.h>
#include <linux/init.h>
#include <linux/hrtimer.h>
#include<linux/jiffies.h>

/* Meta information  */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("SUSSING GNU/LINUX");

/* hr timer*/
static struct hrtimer my_hrtimer;
u64 start_t;

static enum hrtimer_restart test_hrtimer_handler(struct hrtimer *timer)
{
    /* Get current time*/
    u64 now_t = jiffies;
    printk("start_t-now_t = %u\n", jiffies_to_msecs(now_t - start_t));
    return HRTIMER_NORESTART;
}

static int __init ModuleInit(void)
{
    printk("Hello, Kernel!\n");
    /* Init of hrtimer*/
    hrtimer_init(&my_hrtimer,CLOCK_MONOTONIC, HRTIMER_MODE_REL);
    my_hrtimer.function = &test_hrtimer_handler;
    start_t = jiffies;
    hrtimer_start(&my_hrtimer, ms_to_ktime(100), HRTIMER_MODE_REL);
    return 0;   //-1 negative value error
}

/*
@brief: when module is removed from the kernel

*/
static void __exit ModuleExit(void)
{   
    hrtimer_cancel(&my_hrtimer);
    printk("Kernel mod exit\n");
}


module_init(ModuleInit);
module_exit(ModuleExit);