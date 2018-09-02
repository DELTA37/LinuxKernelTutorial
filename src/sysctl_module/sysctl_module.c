#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sysctl.h>

#define SUCCESS (0)


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kasparyants George");
MODULE_DESCRIPTION("A simple Linux driver");
MODULE_VERSION("0.1");


static int global_var = 1;
static int min_val = 0;
static int max_val = 5;
static struct ctl_table_header* header;


static struct ctl_table child_ctl_table[] = {
  {
    .procname = "sample_value",
    .data = &global_var,
    .maxlen = sizeof(int),
    .mode = 0644,
    .proc_handler = &proc_dointvec_minmax,
    .extra1 = &min_val,
    .extra2 = &max_val
  }, 
  {}
};


static struct ctl_table parent_ctl_table[] = {
  {
    .procname = "kernel",
    .mode = 0555,
    .child = child_ctl_table
  }, 
  {}
};


static int __init sysctl_module_init(void) {
  if (!(header = register_sysctl_table(parent_ctl_table))) {
    printk(KERN_ALERT "Error: Failed to register parent_ctl_table\n");
    return -EFAULT;
  }
  printk(KERN_INFO "Start global_var = %d\n", global_var);
  return SUCCESS;
}


static void __exit sysctl_module_exit(void) {
  unregister_sysctl_table(header);
  printk(KERN_INFO "End global_var = %d\n", global_var);
}


module_init(sysctl_module_init);
module_exit(sysctl_module_exit);
