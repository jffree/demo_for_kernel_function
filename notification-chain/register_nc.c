#include <linux/notifier.h>
#include <linux/module.h>
#include <linux/init.h>

#include <linux/kernel.h> /* printk() */
#include <linux/fs.h> /* everything() */

extern int register_test_notifier(struct notifier_block *nb);
#define TESTCHAIN_INIT 0x52U   //定义一个事件类型

/* realize the notifier_call func */
int test_init_event(struct notifier_block *nb, unsigned long event,
    void *v)  //事件的回调函数
{
    switch(event){
    case TESTCHAIN_INIT:
        printk(KERN_DEBUG "I got the chain event from test_chain: TESTCHAIN_INIT\n");
        break;

    default:
        break;
    }

    return NOTIFY_DONE;
}
/* define a notifier_block */
static struct notifier_block test_init_notifier = {   //定义一个通知链节点
    .notifier_call = test_init_event,
};
static int __init test_chain_1_init(void)
{
    printk(KERN_DEBUG "init test_chain register module\n");
    register_test_notifier(&test_init_notifier); // 由chain_0提供的设施
    return 0;
}

static void __exit test_chain_1_exit(void)
{
  printk(KERN_DEBUG "Goodbye to test_clain register module\n");
}

module_init(test_chain_1_init);
module_exit(test_chain_1_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("fishOnFly");
