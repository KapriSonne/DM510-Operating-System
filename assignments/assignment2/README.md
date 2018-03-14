Add system calls to the linux kernel in order to send and retrieve messages.
---------------------------------------------------------------------------

Linux kernel used: Linux 4.15
Download it here: https://www.kernel.org/pub/linux/kernel/v4.x/linux-4.15.tar.gz

SETUP: 
---------
1:	
	gunzip linux-4.15.tar.gz

	tar -xvf linux-4.15.tar

	rm linux-4.15.tar

2:	cd linux-4.15

3:	cp /home/daniel/DM510-2018/root_fs .

4:	make defconfig ARCH=um

5:	make ARCH=um linux

RUN:
--------
6:	./linux
    or
6:	./linux con1=xterm con2=xterm

7:	mkdir /mnt/tmp

8:	mount none /mnt/tmp -t hostfs -o /home/your_imada_login/dm510

9:	cp these files into the kernel:

filename		|	address
------------------------|-----------------------------------------------
talk.h			|	/arch/um/include/asm
talk.c			|	/arch/um/kernel
test1.c			|	anywhere in user-land
test2.c			|	anywhere in user-land
syscall_64.tbl		|	/arch/x86/entry/syscalls/
unistd_64.h		|	/arch/x86/include/generated/uapi/asm/
Makefile		|	/arch/um/kernel/

10:	compile testfiles locally:
~$cc test1.c -I/home/jegyl16/Desktop/fourth_semester/DM501-OS/assignments/assigment_02/dm510/linux-4.15 -o test1
~$cc test2.c -I/home/jegyl16/Desktop/fourth_semester/DM501-OS/assignments/assigment_02/dm510/linux-4.15 -o test2

Now, try it from the virtual linux system :-)


