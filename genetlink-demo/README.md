#### generic netlink 实例


#### 生成内核模块和应用层的可执行程序，并将内核模块其插入内核，查看插入信息

```
make
sudo insmod demo_genetlink_kern.ko
dmesg
```

#### 执行应用层程序，并查看内核信息

```
suod  ./demo_genetlink_user
dmesg
```

#### 卸载内核模块，观察内核信息，执行清理步骤

```
rmmod demo_genetlink_kern
dmesg
make clean
```

#### 注
*此demo取自：https://github.com/luckyapple1028/demo-genetlink.git*，我个人加了一点注释
