//#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
//#include <linux/uaccess.h>
//#include <linux/fs.h>
//#include <linux/proc_fs.h>  // Module metadata
MODULE_AUTHOR("Al Williams");
MODULE_DESCRIPTION("Hackaday LKM");
MODULE_LICENSE("GPLv2");   // many options, GPL, GPLv2, Proprietary, etc.

static int somedata __initdata=0xbeef;  // this is just some static variable available only at init
static int key=0xAA;   // you can override this using insmod
// Note 0644 means that the sysfs entry will be rw-r--r--
module_param(key,int,0644);  // use module_param_named if you want different names internal vs external
MODULE_PARM_DESC(key,"An integer ID unique to this module");

static int __init had_init(void)
{
// This is the usual way to do this (don't forget \n and note no comma after KERN_INFO), but...
  printk(KERN_INFO "Hackaday is in control (%x %x)\n",key,somedata);
  return 0;
}

static void __exit had_exit(void)
{
// ... you can also use the pr_info macro which does the same thing
  pr_info("Returning control of your system to you (%x)!\n",key);
}

module_init(had_init);
module_exit(had_exit);
