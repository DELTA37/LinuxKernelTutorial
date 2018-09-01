#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#define SUCCESS (0)


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kasparyants George");
MODULE_DESCRIPTION("A simple Linux driver");
MODULE_VERSION("0.1");


static int mod1_exp_func(int i) {
    pr_info("%s:%d the value passed in is %d\n", __func__, __LINE__, i);  // == printk(KERN_INFO "", ...)
    return i;
}
EXPORT_SYMBOL(mod1_exp_func); /* export static symbol */


static int __init mod1_init(void) { return SUCCESS; }

static void __exit mod1_exit(void) {}

module_init(mod1_init);
module_exit(mod1_exit);