#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/uaccess.h>


#define SUCCESS (0)
#define DEVICE_NAME ("kaspar")

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kasparyants George");
MODULE_DESCRIPTION("A simple Linux driver");
MODULE_VERSION("0.1");


static char *name = "world";
module_param(name, charp, S_IRUGO);
MODULE_PARM_DESC(name, "The name to display in /var/log/kern.log");


static int major_number;
static int __initdata device_is_opened = 0;


static ssize_t device_read(struct file*, char __user*, size_t, loff_t*);
static ssize_t device_write(struct file*, const char __user*, size_t, loff_t*);
static int device_release(struct inode*, struct file*);
static int device_open(struct inode*, struct file*);


static struct file_operations fops = {
  .owner = THIS_MODULE,
  .read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};


static int __init kaspar_init(void) {
  major_number = register_chrdev(0, DEVICE_NAME, &fops);
  if (major_number < 0) {
    printk(KERN_INFO "Cannot register device\n");
    return major_number;
  }
  printk(KERN_INFO "Registered device %s\n", DEVICE_NAME);
  printk(KERN_INFO "I was assigned major number %d. To talk to\n", major_number);
	printk(KERN_INFO "the driver, create a dev file with\n");
	printk(KERN_INFO "'mknod /dev/%s c %d 0'.\n", DEVICE_NAME, major_number);
	printk(KERN_INFO "Try various minor numbers. Try to cat and echo to\n");
	printk(KERN_INFO "the device file.\n");
	printk(KERN_INFO "Remove the device file and module when done.\n");
  return 0;
}


static void __exit kaspar_exit(void) {
  unregister_chrdev(major_number, DEVICE_NAME);
  printk(KERN_INFO "Unregistered device %s\n", DEVICE_NAME);
}


static int device_open(struct inode* inode, struct file* file) {
	static int counter = 0;

  if (device_is_opened) {
    printk(KERN_INFO "Cannot open device %s\n", DEVICE_NAME);
    return -EBUSY;
  }
  counter++;
  device_is_opened++;
  try_module_get(THIS_MODULE);
  printk(KERN_INFO "Opened device %s\n", DEVICE_NAME);
  return SUCCESS;
}

static int device_release(struct inode *inode, struct file *file) {
  device_is_opened--;
  module_put(THIS_MODULE);
  printk(KERN_INFO "Closed device %s\n", DEVICE_NAME);
  return SUCCESS;
}

static ssize_t device_read(struct file *filp,	char *buffer,	size_t length, loff_t * offset) {
  return 0;
}

static ssize_t device_write(struct file *filp, const char *buff, size_t len, loff_t * off) {
  printk(KERN_ALERT "Sorry, this operation isn't supported.\n");
  return -EINVAL;
}

module_init(kaspar_init);
module_exit(kaspar_exit);