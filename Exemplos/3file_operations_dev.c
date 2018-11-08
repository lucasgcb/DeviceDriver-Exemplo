#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Samir Bonho");
MODULE_DESCRIPTION("Driver quee implementa 4 operacoes principais de manipulacao de arquivos - usa a cdev");
MODULE_VERSION("1.0");



dev_t dev = 0;
static struct class *dev_class;
static struct cdev badalhoca_cdev;
 
static int __init badalhoca_driver_init(void);
static void __exit badalhoca_driver_exit(void);
static int badalhoca_open(struct inode *inode, struct file *file);
static int badalhoca_release(struct inode *inode, struct file *file);
static ssize_t badalhoca_read(struct file *filp, char __user *buf, size_t len,loff_t * off);
static ssize_t badalhoca_write(struct file *filp, const char *buf, size_t len, loff_t * off);
 
static struct file_operations fops =
{
.owner          = THIS_MODULE,
.read           = badalhoca_read,
.write          = badalhoca_write,
.open           = badalhoca_open,
.release        = badalhoca_release,
};
 
static int badalhoca_open(struct inode *inode, struct file *file)
{
        printk(KERN_INFO "Driver Open Function Called...!!!\n");
        return 0;
}
 
static int badalhoca_release(struct inode *inode, struct file *file)
{
        printk(KERN_INFO "Driver Release Function Called...!!!\n");
        return 0;
}
 
static ssize_t badalhoca_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
        printk(KERN_INFO "Driver Read Function Called...!!!\n");
        return 0;
}
static ssize_t badalhoca_write(struct file *filp, const char __user *buf, size_t len, loff_t *off)
{
        printk(KERN_INFO "Driver Write Function Called...!!!\n");
        return len;
}
 
 
static int __init badalhoca_driver_init(void)
{
        /*Allocating Major number*/
        if((alloc_chrdev_region(&dev, 0, 1, "badalhoca_Dev")) <0){
                printk(KERN_INFO "Cannot allocate major number\n");
                return -1;
        }
        printk(KERN_INFO "Major = %d Minor = %d \n",MAJOR(dev), MINOR(dev));
 
        /*Creating cdev structure*/
        cdev_init(&badalhoca_cdev,&fops);
        badalhoca_cdev.owner = THIS_MODULE;
        badalhoca_cdev.ops = &fops;
 
        /*Adding character device to the system*/
        if((cdev_add(&badalhoca_cdev,dev,1)) < 0){
            printk(KERN_INFO "Cannot add the device to the system\n");
            goto r_class;
        }
 
        /*Creating struct class*/
        if((dev_class = class_create(THIS_MODULE,"badalhoca_class")) == NULL){
            printk(KERN_INFO "Cannot create the struct class\n");
            goto r_class;
        }
 
        /*Creating device*/
        if((device_create(dev_class,NULL,dev,NULL,"badalhoca_device")) == NULL){
            printk(KERN_INFO "Cannot create the Device 1\n");
            goto r_device;
        }
        printk(KERN_INFO "Device Driver Insert...Done!!!\n");
	return 0;
 
r_device:
        class_destroy(dev_class);
r_class:
        unregister_chrdev_region(dev,1);
        return -1;
}
 
void __exit badalhoca_driver_exit(void)
{
        device_destroy(dev_class,dev);
        class_destroy(dev_class);
        cdev_del(&badalhoca_cdev);
        unregister_chrdev_region(dev, 1);
	printk(KERN_INFO "Device Driver Remove...Done!!!\n");
}
 
module_init(badalhoca_driver_init);
module_exit(badalhoca_driver_exit);
 

