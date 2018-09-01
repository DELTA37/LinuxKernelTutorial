#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#define SUCCESS (0)


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kasparyants George");
MODULE_DESCRIPTION("A simple Linux driver");
MODULE_VERSION("0.1");


extern int mod1_exp_func(int i);

static int __init mod1_init(void) {
    pr_info("Initializing mod2\n");
    pr_info("Calling exported function in mod1\n");
    mod1_exp_func(3);
    return SUCCESS;
}

static void __exit mod1_exit(void) {}

module_init(mod1_init);
module_exit(mod1_exit);