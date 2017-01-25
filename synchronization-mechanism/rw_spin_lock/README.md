#### rw_spin_lock

*`rw_spin_lock`是对 `spin_lock`的一个改进，`spin_lock`无论在任何时刻，都只允许一个 `thread` 进入临界区，但是 `rw_spin_lock`允许多个 `read thread` 进入临界区。*

#### 策略

##### 加锁的逻辑：

1. 假设临界区内没有任何的thread，这时候任何read thread或者write thread可以进入，但是只能是其一。

2. 假设临界区内有一个read thread，这时候新来的read thread可以任意进入，但是write thread不可以进入

3. 假设临界区内有一个write thread，这时候任何的read thread或者write thread都不可以进入

4. 假设临界区内有一个或者多个read thread，write thread当然不可以进入临界区，但是该write thread也无法阻止后续read thread的进入，他要一直等到临界区一个read thread也没有的时候，才可以进入，多么可怜的write thread。

##### unlock的逻辑如下：

1. 在write thread离开临界区的时候，由于write thread是排他的，因此临界区有且只有一个write thread，这时候，如果write thread执行unlock操作，释放掉锁，那些处于spin的各个thread（read或者write）可以竞争上岗。

2. 在read thread离开临界区的时候，需要根据情况来决定是否让其他处于spin的write thread们参与竞争。如果临界区仍然有read thread，那么write thread还是需要spin（注意：这时候read thread可以进入临界区，听起来也是不公平的）直到所有的read thread释放锁（离开临界区），这时候write thread们可以参与到临界区的竞争中，如果获取到锁，那么该write thread可以进入。

#### API


header 1 | header 2
---|---
接口API描述 |	rw spinlock API
定义rw spin lock并初始化 |	DEFINE_RWLOCK
动态初始化rw spin lock |	rwlock_init
获取指定的rw spin lock |	read_lock write_lock
获取指定的rw spin lock同时disable本CPU中断 |	read_lock_irq write_lock_irq
保存本CPU当前的irq状态，disable本CPU中断并获取指定的rw spin lock |	read_lock_irqsave write_lock_irqsave
获取指定的rw spin lock同时disable本CPU的bottom half | read_lock_bh write_lock_bh
释放指定的spin lock | read_unlock write_unlock
释放指定的rw spin lock同时enable本CPU中断 |	read_unlock_irq write_unlock_irq
释放指定的rw spin lock同时恢复本CPU的中断状态 |	read_unlock_irqrestore write_unlock_irqrestore
获取指定的rw spin lock同时enable本CPU的bottom half |	read_unlock_bh write_unlock_bh
尝试去获取rw spin lock，如果失败，不会spin，而是返回非零值 |	read_trylock write_trylock 



#### 参考

[Linux内核同步机制之（五）：Read/Write spin lock](http://www.wowotech.net/kernel_synchronization/rw-spinlock.html)
