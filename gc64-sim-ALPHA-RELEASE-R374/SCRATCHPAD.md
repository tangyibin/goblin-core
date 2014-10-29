RISC-V ISA Simulator : Scratchpad Extensions
============================================

Author  : John Leidel 

Date    : October 29, 2014

Version : (under version control)

About
-------------

The RISC-V Scratchpad Extensions permit an application to perform 
memory operations on a simulated on-chip software-managed 
scratchpad.  The scratchpad is exposed to the application and the
programmer via a compile-time address space [see named address 
spaces in the embedded-C specification].  Memory operations
are snooped within the MMU class and if they fall within 
the specified memory region, the correct scratchpad 
physical storage addresses are utilized.

The simulator relies upon a basic agreement with 
the compiler and/or library infrastructure in order
to enforce the respective memory blocks to reside 
in the correct physical memory space.   

Build Steps
---------------

We assume that the RISCV environment variable is set to the RISC-V tools
install path, and that the riscv-fesvr package is installed there.

    $ mkdir build
    $ cd build
    $ ../configure --prefix=$RISCV --with-fesvr=$RISCV
    $ make
    $ [sudo] make install

You can override the default notion of the 
scratchpad address space at compile time by modifying 
the GC64_BASE_ADDR macro in spike/spike.cc.
Alternatively, you can set a compiler flag 
with: 
$> export CFLAGS=$CFLAGS -DGC64_BASE_ADDR=0x0000000

Compiling and Running a Simple C Program
-------------------------------------------

Install spike (see Build Steps), riscv-gcc, and riscv-pk.

Write a short C program and name it hello.c.  Then, compile it into a RISC-V
ELF binary named hello:

    $ riscv-gcc -o hello hello.c

Now you can simulate the program atop the proxy kernel:

    $ spike pk hello

Modifying the Size of the Scratchpad
-------------------------------------------

Users can modify the default size of the scratchpad at runtime using the '-s' 
option to spike.  This option requires an argument that is the number of bytes in 
the scratchpad.  Note that this currently supports 64-bit address spaces.  

-------------------------------------------

