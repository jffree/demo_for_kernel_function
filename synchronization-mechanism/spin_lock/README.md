spin_lock

*一个执行单元要想访问被自旋锁保护的共享资源，必须先得到锁，在访问完共享资源后，必须释放锁。如果在获取自旋锁时，没有任何执行单元保持该锁，那么将立即得到锁；如果在获取自旋锁时锁已经有保持者，那么获取锁操作将自旋（对锁进行循环探测）在那里，直到该自旋锁的保持者释放了锁。*

#### 参考

[Linux内核同步机制之（四）：spin lock](http://www.wowotech.net/kernel_synchronization/spinlock.html)

[Pthreads并行编程之spin lock与mutex性能对比分析](http://www.parallellabs.com/2010/01/31/pthreads-programming-spin-lock-vs-mutex-performance-analysis/)
