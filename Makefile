obj-m += process_enumerator.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

test:
	sudo dmesg -C
	sudo insmod process_enumerator.ko
	sudo rmmod process_enumerator.ko
	dmesg --level=info

debug:
	sudo dmesg -C
	sudo insmod process_enumerator.ko
	sudo rmmod process_enumerator.ko
	dmesg --level=info,debug
