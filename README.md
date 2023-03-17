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



