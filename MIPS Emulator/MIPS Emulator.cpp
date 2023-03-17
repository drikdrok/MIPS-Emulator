#include <iostream>
#include <vector>
#include "R-Types.h"
#include "I-Types.h"
#include "helperFunctions.h"
#include "J-Types.h"
#include "syscall.h";

uint32_t PC = 0;
uint32_t REGS[32];
uint32_t IMEM[16384] = {
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
}; // 2^14


//SYSCALL = 0x0000000C

uint32_t DMEM[16384];

std::vector<std::string> printLog;

bool running = true;

bool detailedOutput = true;

using namespace std;


int fetchInstruction() {
    return IMEM[PC];
}

void decodeAndExecute(uint32_t instruction) {
    //DECODE

    if (instruction == 0) {
        cout << "0 instruction reached. Terminating program..." << endl;
        running = false;
        return;
    }
    else if (instruction == 0x0000000C) { // SYSCALL
        SYSCALL();
        return;
    }

    printInBinary(instruction);

    int opcode = instruction >> 26;
   
    if (detailedOutput) std::cout << "Opcode: " << opcode << std::endl;

    if (opcode == 0) { // R-type
        int mask = 31; // 31 = 11111 
        int rs = (instruction >> 21) & mask; //Shift 21 and get the last 5 bits
        int rt = (instruction >> 16) & mask;
        int rd = (instruction >> 11) & mask;
        int shamt = (instruction >> 6) & mask;
        int funct = instruction & 63;

        if (detailedOutput) {
            std::cout << "rs: " << rs << std::endl;
            std::cout << "rt: " << rt << std::endl;
            std::cout << "rd: " << rd << std::endl;
            std::cout << "shamt: " << shamt << std::endl;
            std::cout << "funct: " << funct << std::endl;
        }

        exec_RTYPE(rs, rt, rd, shamt, funct);
    }
    else if (isI_Type(opcode)) { // Addi
        int mask = 31; // 31 = 11111 
        int rs = (instruction >> 21) & mask; //Shift 21 and get the last 5 bits
        int rt = (instruction >> 16) & mask;
        short immediate = instruction & (int)pow(2, 16)-1; // Ask Balkind why no 0x00001111
        
        if (detailedOutput) {
            std::cout << "rs: " << rs << std::endl;
            std::cout << "rt: " << rt << std::endl;
            std::cout << "immediate: " << immediate << std::endl;
        }
        
        printShortInBinary(immediate);

        exec_ITYPE(opcode, rs, rt, immediate);
    }
    else {
        int address = instruction & 0b00000011111111111111111111111111;
        exec_JTYPE(opcode, address);
    }

    if (detailedOutput) cout << "--------" << endl;
}

int main()
{

    REGS[29] = 16380; // $sp

    while (running) {
        int instruction = fetchInstruction();
        decodeAndExecute(instruction);
        PC++;
    }

    cout << "---------" << endl;
    cout << "Final register states: " << endl;
    for (int i = 0; i < 32; i++) {
        cout << i << ": " << REGS[i] << endl;
    }
    cout << "---------" << endl;
    cout << "Final memory states:" << endl;
    for (int i = 0; i < 16384; i++) {
        if (DMEM[i] != 0) {
            cout << i << ": " << DMEM[i] << endl;
        }
    }
    cout << "---------" << endl;
    cout << "Print log:" << endl;
    for (auto& v : printLog) {
        cout << v << endl;
    }

    std::cin.get();

    return 0;
}
