#pragma once
#include <iostream>
uint32_t TEST_EVERYTHING[16384] = {
    0x200A0002, // Addi t2, zero, 2
    0x216B0005, // Addi t3, t3, 5
    0x014B4815, // Addu t1, t2, t3
    0x20080016, // Addi t0, zero, 22
    0x11090006, // BEQ t0, t1, line 6 (Jump to line 7 if t1 = 6)
    0x08000000, // Jump to line 0
    0xAFA90000, // SW t1, 0(sp)
    0x23BDFFFF, // Addi sp sp -1
    0xAFA90000, // SW t1, 0(sp)
    0x8FB80000, // LW t8, 0(sp)
    0x20840001, // addi a0, a0, 1
    0x20420009, // addi v0, v0, 9
    0x0000000C, // SYSCALL
    0x00000000,
}; // 2^14


uint32_t FIB[16384] = {
    0x2084000A, // addi a0 a0 10   (Find 10th Fibonacci number)
    0x0C000007, // JAL FIB (line 7)
    0x00022020, // add a0 zero v0
    0x20040001, // addi a0 zero 1 (print int)
    0x0000000C, // SYSCALL
    0x2004000A, // addi a0 zero 10 (exit)
    0x0000000C, // SYSCALL
    0x23BDFFFD, // addi sp sp -3 (BEGIN FIB(int x))        Line 7
    0xAFBF0002, // sw ra 2(sp)
    0xAFB00001, // sw s0 1(sp)
    0xAFB10000, // sw s1 0(sp)
    0x00048020, // add s0 zero a0
    0x20020001, // addi v0 zero 1
    0x20080002, // addi t0 zero 2
    0x0110482A, // slt t1 t0 s0
    0x11200017, // beq t1 zero fibexit (Line 23)
    0x11280017, // beq t1 t0 fibexit
    0x2204FFFF, // addi a0 s0 -1
    0x0C000007, // JAL FIB      Line 18
    0x00028820, // add s1 zero v0
    0x2204FFFE, // addi a0 s0 -2
    0x0C000007, // JAL FIB
    0x02221020, // add v0 s1 v0
    0x8FBF0002, // lw ra 2(sp) //FIB EXIT
    0x8FB00001, // lw s0 1(sp)
    0x8FB10000, // lw s1 0(sp)
    0x23BD0003, // addi sp sp 3
    0x03E00008, // JR RA 
};