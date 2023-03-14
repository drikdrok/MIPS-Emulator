#pragma once
#include <iostream>

extern uint32_t PC;
extern uint32_t REGS[32];
extern uint32_t IMEM[16384];
extern uint32_t DMEM[16384];

using namespace std;

void exec_ADDI(int rs, int rt, int immediate) {
    cout << "Execute ADDI" << endl;
    REGS[rt] = REGS[rs] + immediate;
}

void exec_BEQ(int rs, int rt, int immediate) {
    cout << "Execute BEQ" << endl;
    cout << REGS[rs] << ", " << REGS[rt] << endl;
    if (REGS[rs] == REGS[rt]) {
        PC = immediate - 1;
        cout << "Branched to line " << immediate << endl;
    }
}

void exec_SW(int rs, int rt, int immediate) {
    cout << "Execute SW" << endl;
    DMEM[REGS[rs] + immediate] = REGS[rt];
}

void exec_ITYPE(int opcode, int rs, int rt, int immediate) {
    if (opcode == 4) {
        exec_BEQ(rs, rt, immediate);
    }
    else if (opcode == 8) {
        exec_ADDI(rs, rt, immediate);
    }
    else {
        cout << "ERROR: Invalid OpCode! " << opcode << endl;
    }
}