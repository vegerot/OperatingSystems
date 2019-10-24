obj-m += lkm_hello1.o
obj-m += main.o
KDIR ?= /lib/modules/$(shell uname -r)/build


all:
	@echo $(KDIR)
	make -C $(KDIR) M=$(PWD) modules
clean:
	make -C $(KDIR) M=$(PWD) clean
