/*
 *  Chap2Project/Part1/simple.c
 *  
 *  Programming Project Chap.2 Part I
 * 
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

static int __init simple_init(void)
{
    printk(KERN_INFO "Loading Module\n");

    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_INFO "Removing Module\n");
}

module_init(simple_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("108590050");
