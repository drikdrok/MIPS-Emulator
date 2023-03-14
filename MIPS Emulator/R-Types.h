#pragma once
#include <iostream>

extern uint32_t PC;
extern uint32_t REGS[32];
extern uint32_t IMEM[16384];
extern uint32_t DMEM[16384];

using namespace std;

void exec_ADDU(int rd, int rs, int rt) {
    cout << "Execute ADDU" << endl;
    REGS[rd] = REGS[rs] + REGS[rt];
}

void exec_RTYPE(int rs, int rt, int rd, int shamt, int funct) {
    if (funct == 21) {
        exec_ADDU(rd, rs, rt);
    }else{
        cout << "ERROR: Invalid Funct Code!" << endl;
    }
}