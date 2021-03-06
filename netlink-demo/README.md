#### 简介

`netlink_demo.h` 为一些宏定义的头文件

`netlink_user.c` 为应用层`NETLINK_TEST`协议的实现

`netlink_kernel.c` 为内核层`NETLINK_TEST`协议的实现

`Makefile` 为生成`netlink_kernel` 内核模块的文件

#### 生成内核模块，并将其插入内核，查看插入信息

```
make
sudo insmod netlink_kernel.ko
dmesg
```

#### 生成应用层可执行文件，执行，并查看内核信息

```
gcc -o netlink_user netlink_user.c
sudo ./netlink_user
dmesg
```

#### 卸载内核模块，执行清理步骤

```
sudo rmmod netlink_kernel
dmesg
make clean
rm -f netlink_user
```

#### 关于用户层源码中A、B、C处 `*pid`的解释

> 注意代码注释中的A、B、C三处分别设置了pid。首先解释一下什么是pid，网上很多文章把这个字段说成是进程的pid，其实这完全是望文生义。这里的pid和进程pid没有什么关系，仅仅相当于UDP的port。对于UDP来说port和ip标示一个地址，那对我们的NETLINK_TEST协议（注意Netlink本身不是一个协议）来说，pid就唯一标示了一个地址。所以你如果用进程pid做为标示当然也是可以的。当然同样的pid对于NETLINK_TEST协议和内核定义的其他使用Netlink的协议是不冲突的（就像TCP的80端口和UDP的80端口）。

> 下面分析这三处设置pid分别有什么作用，首先A和B位置的比较好理解，这是在地址（sockaddr_nl）上进行的设置，就是相当于设置源地址和目的地址（其实是端口），只是注意B处设置pid为0，0就代表是内核，可以理解为内核专用的pid，那么用户进程就不能用0做为自己的pid吗？这个只能说如果你非要用也是可以的，只是会产生一些问题，后面在分析。接下来看为什么C处的消息头仍然需要设置pid呢？这里首先要知道一个前提：内核不会像UDP一样根据我们设置的原、目的地址为我们构造消息头，所以我们不在包头写入我们自己的地址（pid），那内核怎么知道是谁发来的报文呢？当然如果内核只是处理消息不需要回复进程的话舍不设置这个消息头pid都可以。

> 所以每个pid的设置功能不同：A处的设置是要设置发送者的源地址，有人会说既然源地址又不会自动填充到报文中，我们为什么还要设置这个，因为你还可能要接收回复啊。就像寄信，你连“门牌号”都没有，即使你在写信时候写上你的地址是100号，对方回信目的地址也是100号，但是邮局发现根本没有这个地址怎么可能把信送到你手里呢？所以A的主要作用是注册源地址，保证可以收到回复，如果不需要回复当然可以简单将pid设置为0；B处自然就是收信人的地址，pid为0代表内核的地址，假如有一个进程在101号上注册了地址，并调用了recvmsg，如果你将B处的pid设置为101，那数据包就发给了另一个进程，这就实现了使用Netlink进行进程间通信；C相当于你在信封上写的源地址，通常情况下这个应该和你的真实地址（A）处注册的源地址相同，当然你要是不想收到回信，又想恶搞一下或者有特殊需求，你可以写成其他进程注册的pid（比如101）。这和我们现实中寄信是一样的，你给你朋友写封情书，把写信人写成你的另一个好基友，然后后果你懂得…

[Linux Netlink基本使用](http://blog.chinaunix.net/uid-15014334-id-5587278.html)
