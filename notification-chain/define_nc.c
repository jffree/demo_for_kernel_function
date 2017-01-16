#include <linux/notifier.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h> /* printk() */
#include <linux/fs.h> /* everything() */

#define TESTCHAIN_INIT 0x52U
static RAW_NOTIFIER_HEAD(test_chain);  //定义一个 raw 类型的通知链

/* define our own notifier_call_chain */
static int call_test_notifiers(unsigned long val, void *v)  //当有事情发生时，调用此函数通知子系统（执行通知链上的节点的回调程序）
{
    return raw_notifier_call_chain(&test_chain, val, v);
}
EXPORT_SYMBOL(call_test_notifiers);

/* define our own notifier_chain_register func */
 static int register_test_notifier(struct notifier_block *nb) //将一个子系统注册到 test_chain 通知链中
{
    int err;
    err = raw_notifier_chain_register(&test_chain, nb);

    if(err)
        goto out;

out:
    return err;
}

EXPORT_SYMBOL(register_test_notifier);

static int __init test_chain_0_init(void)
{
    printk(KERN_DEBUG "init the  test_chain define module\n");
    return 0;
}

static void __exit test_chain_0_exit(void)
{
    printk(KERN_DEBUG "Goodbye to test_chain define module\n");
}

module_init(test_chain_0_init);
module_exit(test_chain_0_exit);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("fishOnFly");

