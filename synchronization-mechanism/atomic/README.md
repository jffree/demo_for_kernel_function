tomic

##### 简介

* **原子操作的定义：**

*操作是单个指令执行，中间不能中断，且避免其他CPU访问同一存储单元*

* **kernel 中的原子操作的种类：**

1. 整数操作

2. 位操作 

##### 整数操作

* 相关文件

```c
include/asm/atomic.h
include/linux/types.h
include/asm-generic/atomic.h
```

* 数据结构定义

```
typedef struct {
	int counter;
} atomic_t;
```

*新版本的 kernel 中已经放弃了使用 `volatile` 来修饰 `counter` 变量，请参考 `Documentation/atomic_ops.txt` 和 `Documentation/volatile-considered-harmful.txt` 文件*

* 主要函数（通过宏实现，值得学习）

```c
//include/asm-generic/atomic.h
#define ATOMIC_INIT(i)	{ (i) }  //初始化一个原子变量

#define atomic_read(v)	READ_ONCE((v)->counter)   //读取一个原子变量 v 的值
static inline void atomic_add(int i, atomic_t *v); //原子变量 v 加 i

#define atomic_set(v, i) WRITE_ONCE(((v)->counter), (i)) //设定一个原子变量 v 的值为 i
static inline int atomic_add_return(int i, atomic_t *v); //宏实现，我这里是简写；原子变量 v 加 i，并返回相加后的原子变量值

static inline void atomic_add(int i, atomic_t *v); //原子变量 v 减 i
static inline int atomic_sub_return(int i, atomic_t *v); //宏实现，我这里是简写；原子变量 v 减 i，并返回相减后的原子变量值

static inline void atomic_inc(atomic_t *v); //原子变量 v 加 1
static inline void atomic_dec(atomic_t *v); //源自变量 v 减 1

#define atomic_dec_return(v)		atomic_sub_return(1, (v)) //减 1 并返回新值
#define atomic_inc_return(v)		atomic_add_return(1, (v)) //加 1 并返回新值

#define atomic_sub_and_test(i, v)	(atomic_sub_return((i), (v)) == 0) //减 i 并判断返回值是否为0
#define atomic_dec_and_test(v)		(atomic_dec_return(v) == 0) //减 1 并判断返回值是否为0
#define atomic_inc_and_test(v)		(atomic_inc_return(v) == 0) //加 1 并判断返回值是否为0

static inline int atomic_add_negative(int i, atomic_t *v); //加i，判断返回值是否小于 0，小于0为真
```

**atmoic_t 还可以进行（|、 &、 ^）操作，请看源文件**

##### 位操作

* 相关文件：

```c
include/linux/bitops.h
include/asm-generic/bitops  //文件夹
include/asm-generic/bitops.h
```

* 主要函数

```c
//include/asm-generic/bitops//atomic.h

static inline void set_bit(int nr, volatile unsigned long *addr);    //将addr地址的nr位置为1  
static inline void clear_bit(int nr, volatile unsigned long *addr);  //将addr地址的nr位清0  
static inline void change_bit(int nr, volatile unsigned long *addr);  //对addr地址的nr位反置  
static inline int test_and_set_bit(int nr, volatile unsigned long *addr);    //将addr地址的nr位置为1，并返回此位原始值（0或1）  
static inline int test_and_clear_bit(int nr, volatile unsigned long *addr); //将addr地址的nr清0，并返回此位原始值（0或1）  
static inline int test_and_change_bit(int nr, volatile unsigned long *addr); //将addr地址的nr位反置，并返回此位原始值（0或1）  
```


##### 参考

[三言两语聊Kernel：atomic](http://laoar.net/blogs/361/)

[Linux 设备驱动--- 并发 与 竞态 --- atomic_t --- atomic_dec_and_test --- 原子操作 ](http://blog.csdn.net/yikai2009/article/details/8650221)


