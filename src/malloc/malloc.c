#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>


#define SUCCESS (0)


static void* vmem = NULL;
static void* kmem = NULL;
static size_t size = 100;


static int __init virt_init(void) { 
    vmem = (void*)vmalloc(size);
    if (!vmem) {
        printk(KERN_ALERT "Cannot allocate %lu", size);
        return -1;
    }
    kmem = (void*)kmalloc(size, GFP_KERNEL);
    if (!kmem) {
        printk(KERN_ALERT "Cannot allocate %lu", size);
        return -1;
    }
    return SUCCESS; 
}


static void __exit virt_exit(void) {
    vfree(vmem);
    kfree(kmem);
}


module_init(virt_init);
module_exit(virt_exit);