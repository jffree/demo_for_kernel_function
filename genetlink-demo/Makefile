obj-m += demo_genetlink_kern.o
KID := /lib/modules/`uname -r`/build
PWD := $(shell pwd)

all:
	make -C $(KID) M=$(PWD) modules
	gcc -o demo_genetlink_user demo_genetlink_user.c

clean:
	rm -rf *.o *.cmd *.ko *.mod.c *.symvers *.order *.mod.o demo_genetlink_user .*cmd .tmp_versions
