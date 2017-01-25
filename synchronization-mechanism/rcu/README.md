#### RCU

![](http://www.wowotech.net/content/uploadfile/201512/8180fbe55bc857b2d0208565308c932420151203045708.gif)

* rwlock允许多个reader并发，因此，在上图中，三个rwlock reader愉快的并行执行。当rwlock writer试图进入的时候（红色虚线），只能spin，直到所有的reader退出临界区。一旦有rwlock writer在临界区，任何的reader都不能进入，直到writer完成数据更新，立刻临界区。绿色的reader thread们又可以进行愉快玩耍了。rwlock的一个特点就是确定性，白色的reader一定是读取的是old data，而绿色的reader一定获取的是writer更新之后的new data。

* RCU和传统的锁机制不同，当RCU updater进入临界区的时候，即便是有reader在也无所谓，它可以长驱直入，不需要spin。同样的，即便有一个updater正在临界区里面工作，这并不能阻挡RCU reader的步伐。由此可见，RCU的并发性能要好于rwlock，特别如果考虑cpu的数目比较多的情况，那些处于spin状态的cpu在无谓的消耗，多么可惜，随着cpu的数目增加，rwlock性能不断的下降。RCU reader和updater由于可以并发执行，因此这时候的被保护的数据有两份，一份是旧的，一份是新的，对于白色的RCU reader，其读取的数据可能是旧的，也可能是新的，和数据访问的timing相关，当然，当RCU update完成更新之后，新启动的RCU reader（绿色block）读取的一定是新的数据。


#### API

**对于reader，RCU的操作包括：**

1. rcu_read_lock，用来标识RCU read side临界区的开始。

2. rcu_dereference，该接口用来获取RCU protected pointer。reader要访问RCU保护的共享数据，当然要获取RCU protected pointer，然后通过该指针进行dereference的操作。

3. rcu_read_unlock，用来标识reader离开RCU read side临界区

**对于writer，RCU的操作包括：**

1. rcu_assign_pointer。该接口被writer用来进行removal的操作，在witer完成新版本数据分配和更新之后，调用这个接口可以让RCU protected pointer指向RCU protected data。

2. synchronize_rcu。writer端的操作可以是同步的，也就是说，完成更新操作之后，可以调用该接口函数等待所有在旧版本数据上的reader线程离开临界区，一旦从该函数返回，说明旧的共享数据没有任何引用了，可以直接进行reclaimation的操作。

3. call_rcu。当然，某些情况下（例如在softirq context中），writer无法阻塞，这时候可以调用call_rcu接口函数，该函数仅仅是注册了callback就直接返回了，在适当的时机会调用callback函数，完成reclaimation的操作。这样的场景其实是分开removal和reclaimation的操作在两个不同的线程中：updater和reclaimer。

#### 参考

[Linux内核同步机制之（七）：RCU基础](http://www.wowotech.net/kernel_synchronization/rcu_fundamentals.html)

[Linux 2.6内核中新的锁机制--RCU
](https://www.ibm.com/developerworks/cn/linux/l-rcu/)
