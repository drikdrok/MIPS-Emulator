#pragma once
#include <iostream>

extern uint32_t PC;
extern uint32_t REGS[32];
extern uint32_t IMEM[16384];
extern uint32_t DMEM[16384];

using namespace std;

void exec_JUMP(int address) {
	PC = address - 1;
	cout << "Jump to line " << address << endl;
}

void exec_JTYPE(int opcode, int address) {
	if (opcode == 2) { // Jump
		exec_JUMP(address);
	}
}