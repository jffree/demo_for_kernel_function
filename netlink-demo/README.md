#### 简介

`netlink_demo.h` 为一些宏定义的头文件

`netlink_user.c` 为应用层`NETLINK_TEST`协议的实现

`netlink_kernel.c` 为内核层`NETLINK_TEST`协议的实现

`Makefile` 为生成`netlink_kernel` 内核模块的文件

#### 生成内核模块，并将其插入内核，查看插入信息

```
make
sudo insmod netlink_kernel.ko
kmesg
```

#### 生成应用层可执行文件，执行，并查看内核信息

```
gcc -o netlink_user netlink_user.c
sudo ./netlink_user
dmesg
```
