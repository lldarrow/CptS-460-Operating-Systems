VFD=mtximage

as86 -o  ts.o  ts.s
bcc  -c -ansi  t.c
ld86 -d -o mtx ts.o t.o mtxlib /usr/lib/bcc/libc.a

echo mount $VFD on /mnt
sudo mount -o loop $VFD /mnt

sudo rm /mnt/boot/*
sudo cp mtx /mnt/boot

sudo umount /mnt

echo ready to go?

#wait for input
read dummy

echo booting...
qemu-system-i386 -fda mtximage -no-fd-bootchk
