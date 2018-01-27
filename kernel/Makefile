
PWD ?= $(shell pwd)
MODULE_NAME=aos

ifneq ($(KERNELRELEASE),)

$(MODULE_NAME)-y += wrapper.o main.o
obj-m	+= $(MODULE_NAME).o

else

KDIR ?= /lib/modules/`uname -r`/build

default:
	$(MAKE) -C $(KDIR) M=$(PWD)

endif

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
