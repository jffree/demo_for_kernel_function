obj-m += netlink_kernel.o
KID := /lib/modules/`uname -r`/build
PWD := $(shell pwd)

all:
	make -C $(KID) M=$(PWD) modules

clean:
	rm -rf *.o .cmd *.ko *.mod.c *.symvers *.order *.mod.o
