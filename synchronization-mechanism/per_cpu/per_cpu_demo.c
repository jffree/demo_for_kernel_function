#include <linux/init.h>
#include <linux/module.h>
#include <linux/getcpu.h>
#include <linux/smp.h>
#include <linux/delay.h>


DEFINE_PER_CPU(int,count);

int __init percpu_init(void)
{
    unsigned int i;
    printk(KERN_INFO "per_cpu model init...\n");
    for(i=0; i<10; i++){
        printk("When i=%d, we use the %d's cpu %d times.\n", i, smp_processor_id(), get_cpu_var(count)++);
        put_cpu_var(count);
        msleep(1000);//睡眠1s，可能导致其更换CPU
    }
    return 0;
}

void __exit percpu_exit(void)
{
    printk(KERN_INFO "per_cpu model existing...\n");
}

module_init(percpu_init);
module_exit(percpu_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("simle use for hash table and hash percpu");
MODULE_AUTHOR("wlw");
