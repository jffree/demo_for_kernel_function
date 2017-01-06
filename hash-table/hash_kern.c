#include <linux/init.h>
#include <linux/module.h>
#include <linux/list.h>

struct q_coef
{
    u8 coef;
    u8 index;
    struct hlist_node hash;
};

#define HASH_NUMBER 26
u8 coef[HASH_NUMBER] = {
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x20, 0x40, 0x80, 0x1d, 0x3a, 0x74, 0xe8, 0xcd, 0x87, 0x13,
};
struct q_coef q_coef_list[HASH_NUMBER];   //哈希表

struct hlist_head hashtbl[HASH_NUMBER];   //哈希链表表头

static inline int hash_func(u8 k)    //哈希算法   f(key) = ((104 * k + 52) % 233) % HASH_NUMBER
{
    int a, b, p, m;
    a = 104;
    b = 52;
    p = 233;
    m = HASH_NUMBER;
    return ((a * k + b) % p) % m;
}

static void hash_init(void)
{
    int i, j;
    for (i = 0 ; i < HASH_NUMBER ; i++) {     //初始化哈希表 q_coef_list，和哈希链表 hashtbl
        INIT_HLIST_HEAD(&hashtbl[i]);
        INIT_HLIST_NODE(&q_coef_list[i].hash);
        q_coef_list[i].coef = coef[i];
        q_coef_list[i].index = i + 1;
    }
    for (i = 0 ; i < HASH_NUMBER ; i++) {   //填充哈希链表  hashtbl
        j = hash_func(q_coef_list[i].coef);
        hlist_add_head(&q_coef_list[i].hash, &hashtbl[j]);     //将q_coef_list[i].bash 变为 hashtb1[j]的头节点
    }
	return ;
}

static void hash_test(void)
{
    int i, j;
    struct q_coef *q;
    for (i = 0 ; i < HASH_NUMBER ; i++) {   //对所有的哈希桶进行循环查找
        j = hash_func(coef[i]);
        hlist_for_each_entry(q, &hashtbl[j], hash) { //hlist_for_each_entry是一个for循环的宏定义，用来遍历hashtbl[j]哈希链表
            if (q->coef == coef[i])
                printk("found: coef=0x%02x index=%d in bucket=%d\n", q->coef, q->index, j);
		}
	}
    return ;
}

int __init htest_init (void)
{
    printk(KERN_INFO "hash table model init...\n");
    hash_init();
    hash_test();
    return 0;
}

void __exit htest_exit (void)
{
    printk(KERN_INFO "hash table model existing...\n");
}

module_init(htest_init);
module_exit(htest_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("simle use for hash table and hash list");
MODULE_AUTHOR("wlw");
