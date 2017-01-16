#### notification chain 实例


#### 生成内核模块，并将内核模块其插入内核

```
make
sudo insmod define_nc.ko
sudo insmod register_nc.ko
sudo insmod send_nc.ko
dmesg
```

#### 卸载内核模块，观察内核信息，执行清理步骤

```
sudo rmmod send_nc register_nc define_nc
dmesg
make clean
```

#### 参考
[Linux内核基础--事件通知链(notifier chain) ](http://blog.csdn.net/wuhzossibility/article/details/8079025)
