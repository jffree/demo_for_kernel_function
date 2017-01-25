#### seqock

*在 rw_spin_lock 上更进一步，允许write thread 进行抢占*

#### 机制

##### writer thread的操作

**对于writer thread，获取seqlock操作如下：**

1. 获取锁（例如spin lock），该锁确保临界区只有一个writer进入。

2. sequence counter加一

**释放seqlock操作如下：**

1. 释放锁，允许其他writer thread进入临界区。

2. sequence counter加一（注意：不是减一哦，sequence counter是一个不断累加的counter）

*由上面的操作可知，如果临界区没有任何的writer thread，那么sequence counter是偶数（sequence counter初始化为0），如果临界区有一个writer thread（当然，也只能有一个），那么sequence counter是奇数。*

##### reader thread的操作如下：

1. 获取sequence counter的值，如果是偶数，可以进入临界区，如果是奇数，那么等待writer离开临界区（sequence counter变成偶数）。进入临界区时候的sequence counter的值我们称之old sequence counter。

2. 进入临界区，读取数据

3. 获取sequence counter的值，如果等于old sequence counter，说明一切OK，否则回到step（1） 

#### 参考

[Linux内核同步机制之（六）：Seqlock](http://www.wowotech.net/kernel_synchronization/seqlock.html)

