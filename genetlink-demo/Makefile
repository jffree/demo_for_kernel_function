obj-m += netlink_ker.o


KID := /lib/modules/`uname -r`/build
PWD := $(shell pwd)

all:
	make -C $(KID) M=$(PWD) modules

clean:
	rm -rf *.o .cmd *.ko *.mod.c .tmp_versions
