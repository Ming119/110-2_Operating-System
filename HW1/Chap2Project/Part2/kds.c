/*
 *  Chap2Project/Part2/kds.c
 *  
 *  Programming Project Chap.2 Part II
 * 
 *  108590002 謝宗麟
 *  108590029 朱欣雨
 *  108590049 符芷琪
 *  108590050 李浩銘
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/types.h>

struct birthday
{
    int day;
    int month;
    int year;
    struct list_head list;
};

static LIST_HEAD(birthday_list);

static int __init kds_init(void)
{
    printk(KERN_INFO "Loading Module\n");

    // Create a linked list containing five `struct_birthday` elements
    struct birthday *person;
    for (int i = 0; i < 5; i++)
    {
        person = kmalloc(sizeof(*person), GFP_KERNEL);
        person->day = 2;
        person->month = 8;
        person->year = 1995;
        INIT_LIST_HEAD(&person->list);
        list_add_tail(&person->list, &birthday_list);
    }

    // Traverse the linked list and output its contents to the kernel log buffer
    struct birthday *ptr;
    list_for_each_entry(ptr, &birthday_list, list)
    {
        // on each iteration ptr points
        // to the next birth struct

        printk(KERN_INFO "birthday:\n\tday: %d\n\tmonth: %d\n\tyear: %d\n", ptr->day, ptr->month, ptr->year);
    }

    return 0;
}

static void __exit kds_exit(void)
{
    printk(KERN_INFO "Removing Module\n");

    // Delete the elements from the linked list and return the free memory back to the kernel
    struct birthday *ptr, *next;
    list_for_each_entry_safe(ptr, next, &birthday_list, list)
    {
        // on each iteration ptr points
        // to the next birthday struct

        list_del(&ptr->list);
        kfree(ptr);
    }
}

module_init(kds_init);
module_exit(kds_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Kernel Data Structures");