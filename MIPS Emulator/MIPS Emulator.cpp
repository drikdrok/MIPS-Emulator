#include <iostream>
#include "R-Types.h"
#include "I-Types.h"
#include "helperFunctions.h"
#include "J-Types.h"

uint32_t PC = 0;
uint32_t REGS[32];
uint32_t IMEM[16384] = {
    0x200A0002, // Addi t2, zero, 2
    0x216B0005, // Addi t3, t3, 5
    0x014B4815, // Addu t1, t2, t3
    0x20080016, // Addi t0, zero, 22
    0x11090006, // BEQ t0, t1, line 6 (Jump to line 7 if t1 = 6)
    0x08000000, // Jump to line 0
    0xAFA90000, // SW t1, 0(sp)
    0x00000000,
    0x00000000,
}; // 2^14


//syscal = 0x0000000C

uint32_t DMEM[16384];

bool running = true;

using namespace std;


int fetchInstruction() {
    return IMEM[PC];
}

void decodeAndExecute(int instruction) {
    //DECODE

    if (instruction == 0) {
        cout << "0 instruction reached. Terminating program..." << endl;
        running = false;
        return;
    }

    printInBinary(instruction);

    int opcode = instruction >> 26;
    std::cout << "Opcode: " << opcode << std::endl;

    if (opcode == 0) { // R-type
        int mask = 31; // 31 = 11111 
        int rs = (instruction >> 21) & mask; //Shift 21 and get the last 5 bits
        int rt = (instruction >> 16) & mask;
        int rd = (instruction >> 11) & mask;
        int shamt = (instruction >> 6) & mask;
        int funct = instruction & 63;

        std::cout << "rs: " << rs << std::endl;
        std::cout << "rt: " << rt << std::endl;
        std::cout << "rd: " << rd << std::endl;
        std::cout << "shamt: " << shamt << std::endl;
        std::cout << "funct: " << funct << std::endl;

        exec_RTYPE(rs, rt, rd, shamt, funct);
    }
    else if (isI_Type(opcode)) { // Addi
        int mask = 31; // 31 = 11111 
        int rs = (instruction >> 21) & mask; //Shift 21 and get the last 5 bits
        int rt = (instruction >> 16) & mask;
        int immediate = instruction & (int)pow(2, 15)-1; // Ask Balkind why no 0x00001111
        std::cout << "rs: " << rs << std::endl;
        std::cout << "rt: " << rt << std::endl;
        std::cout << "immediate: " << immediate << std::endl;

        exec_ITYPE(opcode, rs, rt, immediate);
    }
    else {
        int address = instruction & 0x00111111;
        exec_JTYPE(opcode, address);
    }

    cout << "--------" << endl;
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

    std::cin.get();

    return 0;
}
