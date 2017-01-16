obj-m   := define_nc.o register_nc.o  send_nc.o
KID := /lib/modules/`uname -r`/build
PWD := $(shell pwd)

all:
	make -C $(KID) M=$(PWD) modules

clean:
	rm -rf *.o *.cmd *.ko *.mod.c *.symvers *.order *.mod.o .*cmd .tmp_versions
