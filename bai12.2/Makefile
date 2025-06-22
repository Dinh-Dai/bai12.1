obj-m := dt_reader_driver.o

KDIR := /home/dai/buildroot/output/build/linux-custom
PWD  := $(shell pwd)

CROSS_COMPILE := /home/dai/buildroot/output/host/bin/arm-buildroot-linux-gnueabihf-
ARCH := arm

all:
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

