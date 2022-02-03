include <linux/init.h>      // Macros used to mark up functions e.g., __init __exit
#include <linux/module.h>    // Core header for loading LKMs into the kernel
#include <linux/kernel.h>    // Contains types, macros, functions for the kernel - printk()
#include <linux/errno.h>     // error codes
#include <linux/sched.h>
//#include <linux/sched/signal.h>

MODULE_LICENSE("GPL");       ///< The license type -- this affects runtime behavior
MODULE_AUTHOR("Gricelle");       ///< The author -- visible when you use modinfo
MODULE_DESCRIPTION("A simple KLM that cycles through the list of TCB, search in init function.");  ///< The description -- see modinfo
MODULE_VERSION("0.1");              ///< The version of the module

static int __init hello_init(void)
{
   int i, of;
   struct task_struct *p, v, *ptr, *ptr1;
   
   printk(KERN_INFO "KLM : Welcome\n");

   p = &init_task;
   printk(KERN_INFO "Address of first TCB is %px\n", p); 

   of = (char*)&v.comm - (char*)&v;
   printk(KERN_INFO "Offset of comm field is %i\n", of);

   printk(KERN_INFO "first TCB task -> %s id=%i\n", p->comm, p->pid);   

   printk(KERN_INFO "Address of next %px\n", p->tasks.next); 
   ptr = container_of(p->tasks.next, struct task_struct, tasks);
   printk(KERN_INFO "comm %s id=%i\n", ptr->comm, ptr->pid);
   ptr1 = container_of(ptr->tasks.next, struct task_struct, tasks);
   printk(KERN_INFO "comm %s id=%i\n", ptr1->comm, ptr1->pid);


// One way - using a counter , problem  how long is list, but shows us pid =0 , which is swapper task anem
   ptr =p;
   for (i =0; i < 5; i++) {
      printk(KERN_INFO "[%i]->val %s Id=%i\n", i, ptr->comm, ptr->pid);
      ptr = container_of(ptr->tasks.next, struct task_struct, tasks);
   }
   
// Second way to do it using the pointers in linked list to terminate, does not  show swapper as it skips pid=0 since it is a terminator TCB
   i =0;
   for (p = &init_task ; (p = next_task(p)) != &init_task ; ) {
      printk(KERN_INFO "[%i]->com=%s id=%i\n", i++, p->comm, p->pid);
      //ptr = container_of(p->tasks.next, struct task_struct, tasks);
   }
   return 0;
}


static void __exit hello_exit(void)
{
    printk(KERN_INFO "KLM: Goodbye\n");
}


module_init(hello_init);
module_exit(hello_exit);

