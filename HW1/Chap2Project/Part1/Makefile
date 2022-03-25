KERNEL_DIR := /lib/modules/$(shell uname -r)/build
MODULE_NAME := simple
obj-m += $(MODULE_NAME).o
ccflags-y += -std=gnu11

all:
	make -C $(KERNEL_DIR) M=$(PWD) modules

clean:
	make -C $(KERNEL_DIR) M=$(PWD) clean

install:
	sudo insmod $(MODULE_NAME).ko

uninstall:
	sudo rmmod $(MODULE_NAME).ko

.PHONY:
	clean install uninstall