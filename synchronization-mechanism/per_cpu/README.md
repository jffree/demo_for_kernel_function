#### generic netlink 实例


#### 生成内核模块和应用层的可执行程序，并将内核模块其插入内核，查看插入信息

```
make
sudo insmod per_cpu_demo.ko
dmesg
```

#### 卸载内核模块，观察内核信息，执行清理步骤

```
rmmod demo_genetlink_kern
dmesg
make clean
```

#### 注

*我写的关于 per_cpu 的文章：https://jffree.github.io/2017/01/20/kernel-%E4%B8%AD%E7%9A%84-per-cpu/
