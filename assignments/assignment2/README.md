Add system calls to the linux kernel.
--------------------------------------
This project is part of the DM510: Operating Systems at Southern University of Denmark.
The goal was to implement a way of sending messages to a linux kernel, and read it as well.

Two test is made; test1 which sends a message as command line argument, then waits for one second, and reads the message from the kernel. test2 which waits (listens) for a message to be send to the kernel, then replaces this message which its own messeage passed as command line argument.

Linux kernel used: Linux 4.15

Download it here: https://www.kernel.org/pub/linux/kernel/v4.x/linux-4.15.tar.gz

SETUP: 
---------
UNZIP:

	gunzip linux-4.15.tar.gz

	tar -xvf linux-4.15.tar

	rm linux-4.15.tar

GET FILESYSTEM:

	cd linux-4.15

	cp /home/daniel/DM510-2018/root_fs .
	
	cd ..
	
	cd sources

	run bashscript ./setup.sh
	
COMPILE KERNEL:

	cd ..
	
	cd linux-4.15

	make defconfig ARCH=um

	make ARCH=um linux
	
COMPILE TESTFILES:
-------------
	
	cd sources
	
	cc test1.c -o test1 -I arch/um/kernel

	cc test2.c -o test2 -I arch/um/kernel

RUN (virtual linux):
--------
	./linux
    or
	./linux con1=xterm con2=xterm
	
	login: root

	mkdir /mnt/tmp

	mount none /mnt/tmp -t hostfs -o /home/<user>/dm510
	
	cd /mnt/tmp/sources/
	
	./test1 "this is a message"
	./test2 "this is also a message"
	




	



