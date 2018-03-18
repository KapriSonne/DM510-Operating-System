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

	run bashscript ./setup.sh

	make defconfig ARCH=um

	make ARCH=um linux

RUN:
--------
	./linux
    or
	./linux con1=xterm con2=xterm

	mkdir /mnt/tmp

	mount none /mnt/tmp -t hostfs -o /home/your_imada_login/dm510


Compile test-files locally:
-------------
	cc test1.c -I/home/jegyl16/Desktop/ -o test1

	cc test2.c -I/home/jegyl16/Desktop/ -o test2

Now, try it from the virtual linux system :-)


