#pragma once
#include <iostream>

extern uint32_t PC;
extern uint32_t REGS[32];
extern uint32_t IMEM[16384];
extern uint32_t DMEM[16384];

extern bool detailedOutput;

using namespace std;

void exec_ADDU(int rd, int rs, int rt) {
    if (detailedOutput) cout << "Execute ADDU" << endl;
    REGS[rd] = REGS[rs] + REGS[rt];
}

void exec_SLT(int rd, int rs, int rt) {
    REGS[rd] = REGS[rs] < REGS[rt] ? 1 : 0;
    if (detailedOutput) {
        cout << "Execute SLT" << endl;
        cout << "SLT " << REGS[rs] << " < " << REGS[rt] << endl;
    }
}

void exec_JR(int rd, int rs, int rt) {
    PC = REGS[rs];
    if (detailedOutput) {
        cout << "Execute JR" << endl;
        cout << "Jump to register line " << REGS[rs] << endl;
    }
}

void exec_RTYPE(int rs, int rt, int rd, int shamt, int funct) {
    if (funct == 21) {
        exec_ADDU(rd, rs, rt);
    }
    else if (funct == 32) {
        exec_ADDU(rd, rs, rt);
    }
    else if (funct == 0x2A) {
        exec_SLT(rd, rs, rt);
    }
    else if (funct == 8) {
        exec_JR(rd, rs, rt);
    }
    else{
        cout << "ERROR: Invalid Funct Code!" << endl;
    }
}
