# MIPS-Emulator
Simple MIPS Emulator created for a Computer Architecture class at UCSB
---
Supported instructions:

<b>R-Types:</b> 
* ADDU
* ADD
* JR
* SLT

<b>I-Types:</b> 
* ADDI 
* BEQ 
* SW  
* LW

<b>J-Types:</b> 
* J 
* JAL

---
# Usage
Write raw assembly hex instructions into the IMEM array in "MIPS Emulator.cpp" 

A converter such as [this one](https://www.eg.bucknell.edu/~csci320/mips_web/) can be helpful when writing programs

You can toggle how much information is shown with the variable 'detailedOutput' - this will make it run a lot faster.

---
# SYSCALL
The instruction SYSCALL has hexcode 0x0000000C

There are 2 supported arguments for SYSCALL:
* a0 = 1: print out $v0 to the printlog (everything will be printed once the program has terminated)
* a0 = 10: exit code (program is terminated)

Alternatively, program will terminate once the last line of code has been executed

