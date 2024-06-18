#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>  // Module metadata
#include <linux/version.h>

MODULE_AUTHOR("Al Williams");
MODULE_DESCRIPTION("Hackaday LKM1");
MODULE_LICENSE("GPLv2");   // many options, GPL, GPLv2, Proprietary, etc.


static char logo[]=
"                                                                                \n"\
"                                                                                \n"\
"                                                                                \n"\
"           #@@@@@@                                            ,@@@@@@           \n"\
"              &@@@@@*                                       &@@@@@,             \n"\
"               @@@@@@%                                     @@@@@@#              \n"\
"   @@       .@@@@@@@@@                                    .@@@@@@@@@       .@#  \n"\
"   &@@@&  /@@@@@@@@@@@@                                   @@@@@@@@@@@@   @@@@*  \n"\
"    @@@@@@@@@@@@@@@@@@@@@#                             @@@@@@@@@@@@@@@@@@@@@,   \n"\
"      &@@@@@@@@@@@@@@@@@@@@@*    ,@@@@@@@@@@@@%     &@@@@@@@@@@@@@@@@@@@@@*     \n"\
"           ,*.  @@@@@@@@@@@/ .@@@@@@@@@@@@@@@@@@@@&  &@@@@@@@@@@#  **           \n"\
"                   @@@@@@, &@@@@@@@@@@@@@@@@@@@@@@@@@, %@@@@@&                  \n"\
"                     ,@& /@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  @@                     \n"\
"                        &@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*                       \n"\
"                       %@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.                      \n"\
"                       @@@@@@       #@@@@@@@.      /@@@@@@                      \n"\
"                      /@@@@&         @@@@@@.         @@@@@                      \n"\
"                      ,@@@@%      (@@@@@@@@@@&*      @@@@@                      \n"\
"                       @@@@@#  @@@@@@@@@@@@@@@@@@%  @@@@@&                      \n"\
"                       /@@@@@@@@@@@@@@@, #@@@@@@@@@@@@@@@                       \n"\
"                     @@ *@@@@@@@@@@@@@& ( @@@@@@@@@@@@@@ .@(                    \n"\
"                  %@@@@@. @@@@@@@@@@@@@@@@@@@@@@@@@@@@% #@@@@@*                 \n"\
"          (%&%((@@@@@@@@@@  @@@@@@@@@@@@@@@@@@@@@@@@% ,@@@@@@@@@@*#&&#/         \n"\
"      @@@@@@@@@@@@@@@@@@@@@@  @@@@@@@@@@@@@@@@@@@@(  @@@@@@@@@@@@@@@@@@@@@&     \n"\
"    @@@@@@@@@@@@@@@@@@@@@     @@@@@@*@@@@@@/%@@@@@&    *@@@@@@@@@@@@@@@@@@@@#   \n"\
"   @@@@.   @@@@@@@@@@@.         ..      .      .          (@@@@@@@@@@#   /@@@*  \n"\
"   @,        %@@@@@@@@                                    .@@@@@@@@.        &#  \n"\
"               ,@@@@@(                                     @@@@@@               \n"\
"             *@@@@@@                                        (@@@@@@             \n"\
"           @@@@@@,                                             %@@@@@@          \n"\
"                                                                                \n"\
"                                                                                ";

static struct proc_dir_entry *proc_entry;
static ssize_t had_read(struct file *f, char __user * user_buffer, size_t count, loff_t * offset)
{
  size_t len;
  if (*offset>0) return 0;  // no seeking, please!
  copy_to_user(user_buffer,logo,len=strlen(logo));  // skipped error check
  *offset=len;
  return len;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,6,0)
static struct proc_ops procop =   // prior to Linux 5.6 you needed file_operations
  {
    .proc_read=had_read
  };
#else
static struct file_operations procop =
  {
    .owner=THIS_MODULE,
    .read=had_read
#endif

static int __init had_init(void)
{
// This is the usual way to do this (don't forget \n and note no comma after KERN_INFO), but...
  printk(KERN_INFO "Hackaday<1> is in control\n");
  proc_entry=proc_create("jollywrencher",0644,NULL,&procop);
  return 0;
}

static void __exit had_exit(void)
{
// ... you can also use the pr_info macro which does the same thing
  pr_info("Returning control of your system to you...\n");
  proc_remove(proc_entry);
}

module_init(had_init);
module_exit(had_exit);
