Add system calls to the linux kernel.
--------------------------------------

Linux kernel used: Linux 4.15

Download it here: https://www.kernel.org/pub/linux/kernel/v4.x/linux-4.15.tar.gz

SETUP: 
---------
1:

	gunzip linux-4.15.tar.gz

	tar -xvf linux-4.15.tar

	rm linux-4.15.tar

2:

	cd linux-4.15

	cp /home/daniel/DM510-2018/root_fs .
	
	cd ..
	
	cd sources

	run bashscript ./setup.sh
	
3:

	cd ..
	
	cd linux-4.15

	make defconfig ARCH=um

	make ARCH=um linux

RUN:
--------
	./linux
    or
	./linux con1=xterm con2=xterm
	
	login: root

	mkdir /mnt/tmp

	mount none /mnt/tmp -t hostfs -o /home/<user>/dm510
	
	cd /mnt/tmp/	


TEST:
-------------
	cd ..
	
	cd sources
	
	cc test1.c -o test1 -I arch/um/kernel

	cc test2.c -o test2 -I arch/um/kernel


