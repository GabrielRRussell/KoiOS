# KoiOS
KoiOS is Gabriel Russell's Senior Mastery Project for the Computer Science Major at AAST.

KoiOS is an ambitious project that aims to have a fully functioning operating system by the end of summer 2020.
Developed entirely in C, and Assembly.

# Compiling
You'll need a cross compiler. Adjust the makefile to the location of your i3/686 Cross Compiler in order to compile the project.  
By default, this project is compiled with an i686-elf gcc.ss
Follow along with the instructions on the OSDev wiki, and you should be just fine. GDB is not necessary for this project.

Use *make* to create the .bin file associated with the OS, which can be placed into QEMU using the FDA flag.

Use *make run* to run it in qemu.

Use *make debug* to start GDB while QEMU runs.

# To-Do
- [x] ATA Driver
- [x] Proper FAT32 Support for Bootloader
- [ ] FAT32 Driver for Kernel/Userspace
- [ ] Userspace Execution
- [ ] Multiboot Support


# Thanks
Cfenollosa's OS Tutorial on Github  
OSDev Wiki, Forum  
All the wonderful people in the OSDev Discord Group  
William Atkinson  
