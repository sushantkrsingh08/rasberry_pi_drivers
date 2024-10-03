#include <linux/module.h>
#include <linux/init.h>
#include <linux/gpio.h>
#include <linux/jiffies.h>
#include <linux/timer.h>

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Johannes 529 GNU/Linux");
MODULE_DESCRIPTION("A simple test for LKM's timer");

/** variable for timer */
static struct timer_list my_timer;

void timer_callback(struct timer_list * data) {
	printk("Timer callback\n");
	gpio_set_value(529, 1); /* Turn LED on */
}

/**
 * @brief This function is called, when the module is loaded into the kernel
 */
static int __init ModuleInit(void) {
	printk("Hello, Kernel!\n");
	/* GPIO 529 init */
	if(gpio_request(529, "rpi-gpio-529")) {
		printk("Can not allocate GPIO 529\n");
		return -1;
	}

	/* Set GPIO 529 direction */
	if(gpio_direction_output(529, 0)) {
		printk("Can not set GPIO 529 to output!\n");
		gpio_free(529);
		return -1;
	}

	/* Turn LED on */
	gpio_set_value(529, 0);

	/* Initialize timer */
	
	timer_setup(&my_timer, timer_callback, 0);
	mod_timer(&my_timer, jiffies + msecs_to_jiffies(1000));
	mod_timer(&my_timer, jiffies + msecs_to_jiffies(2000));
	mod_timer(&my_timer, jiffies + msecs_to_jiffies(3000));
	mod_timer(&my_timer, jiffies + msecs_to_jiffies(4000));
	mod_timer(&my_timer, jiffies + msecs_to_jiffies(5000));
	mod_timer(&my_timer, jiffies + msecs_to_jiffies(6000));
	mod_timer(&my_timer, jiffies + msecs_to_jiffies(7000));
	mod_timer(&my_timer, jiffies + msecs_to_jiffies(8000));
	mod_timer(&my_timer, jiffies + msecs_to_jiffies(1000));

	return 0;
}

/**
 * @brief This function is called, when the module is removed from the kernel
 */
static void __exit ModuleExit(void) {
	printk("Goodbye, Kernel\n");
	gpio_free(529);
	del_timer(&my_timer);
}

module_init(ModuleInit);
module_exit(ModuleExit);