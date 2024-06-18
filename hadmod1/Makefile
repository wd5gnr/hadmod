obj-m += hadmod1.o

PWD := $(CURDIR)   # not needed in most cases, but useful if using sudo

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

