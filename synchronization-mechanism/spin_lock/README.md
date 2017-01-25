#### spin_lock

*一个执行单元要想访问被自旋锁保护的共享资源，必须先得到锁，在访问完共享资源后，必须释放锁。如果在获取自旋锁时，没有任何执行单元保持该锁，那么将立即得到锁；如果在获取自旋锁时锁已经有保持者，那么获取锁操作将自旋（对锁进行循环探测）在那里，直到该自旋锁的保持者释放了锁。*

#### API

PI的类型 |	spinlock中的定义 |	raw_spinlock的定义
---|---|--- 
定义spin lock并初始化 |	DEFINE_SPINLOCK  |	DEFINE_RAW_SPINLOCK
动态初始化spin lock |	spin_lock_init |	raw_spin_lock_init
获取指定的spin lock |	spin_lock |	raw_spin_lock
获取指定的spin lock同时disable本CPU中断 |	spin_lock_irq |	raw_spin_lock_irq
保存本CPU当前的irq状态，disable本CPU中断并获取指定的spin lock |	spin_lock_irqsave |	raw_spin_lock_irqsave
获取指定的spin lock同时disable本CPU的bottom half |	spin_lock_bh | 	raw_spin_lock_bh
释放指定的spin lock |	spin_unlock |	raw_spin_unlock
释放指定的spin lock同时enable本CPU中断 |	spin_unlock_irq |	raw_spin_unock_irq
释放指定的spin lock同时恢复本CPU的中断状态 |	spin_unlock_irqstore |	raw_spin_unlock_irqstore
获取指定的spin lock同时enable本CPU的bottom half |	spin_unlock_bh |	raw_spin_unlock_bh
尝试去获取spin lock，如果失败，不会spin，而是返回非零值 |	spin_trylock |	raw_spin_trylock
判断spin lock是否是locked，如果其他的thread已经获取了该lock，那么返回非零值，否则返回0 |	spin_is_locked |	raw_spin_is_locked 

#### 参考

[Linux内核同步机制之（四）：spin lock](http://www.wowotech.net/kernel_synchronization/spinlock.html)

[Pthreads并行编程之spin lock与mutex性能对比分析](http://www.parallellabs.com/2010/01/31/pthreads-programming-spin-lock-vs-mutex-performance-analysis/)
