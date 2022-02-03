#include <linux/init.h>      // Macros used to mark up functions e.g.,
#include <linux/module.h>    // Core header for loading LKMs into the kernel
#include <linux/kernel.h>    // Contains types, macros, functions for 
#include <linux/errno.h>     // error codes
#include <linux/sched.h>
#include <linux/sched/task.h>
#include <linux/sched/signal.h>

MODULE_LICENSE("GPL");       ///< The license type -- this affects runti
MODULE_AUTHOR("Gricelle");       ///< The author -- visible when you use modinfo
MODULE_DESCRIPTION("A simple KLM ");
MODULE_VERSION("0.1");              ///< The version of the module

static int __init hello_init(void)  // start of module
{
   int i, of;
   struct task_struct *p, v, *ptr, *ptr1;
   
   printk(KERN_INFO "KLM : Welcome\n");

   p = &init_task;
   printk(KERN_INFO "Address of first TCB is %px\n", p); 

   of = (char*)&v.comm - (char*)&v;
   printk(KERN_INFO "Offset of comm field is %x\n", of);
   
   /*
     You can cast a reference to a variable in the task_struct to a void pointer
     and subtract it from by the starting address of the task_struct to find the offset
   */
   of = (void*)&v.min_flt - (void*)&v;
   printk(KERN_INFO "Offset of min_flt field is %x\n", of);
   
   printk(KERN_INFO "first TCB task -> %s id=%i\n", p->comm, p->pid);   
   printk(KERN_INFO "Address of next %px\n", p->tasks.next); 
   ptr = container_of(p->tasks.next, struct task_struct, tasks);
   printk(KERN_INFO "comm %s id=%i\n", ptr->comm, ptr->pid);
   ptr1 = container_of(ptr->tasks.next, struct task_struct, tasks);
   printk(KERN_INFO "comm %s id=%i\n", ptr1->comm, ptr1->pid);
   
// Loop through task struct using the pointers in  "[%i] ->linked list to terminate
   i =0;

  for (p = &init_task ; (p = next_task(p)) != &init_task ; ) {
      printk(KERN_INFO "[%i] -> com=%s id=%i\n", i++, p->comm, p->pid);
      //ptr = container_of(p->tasks.next, struct task_struct, tasks);
   }
   return  0;
}


static void __exit hello_exit(void)
{
    printk(KERN_INFO "KLM: Goodbye\n");
}


module_init(hello_init);
module_exit(hello_exit);
