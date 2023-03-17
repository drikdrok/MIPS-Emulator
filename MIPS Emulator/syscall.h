#pragma once
#include <iostream>
#include <vector>
#include <string>

extern uint32_t PC;
extern uint32_t REGS[32];
extern uint32_t IMEM[16384];
extern uint32_t DMEM[16384];
extern std::vector<std::string> printLog;

extern bool running;

using namespace std;

void SYSCALL() {
	cout << "SYSCALL v0 = " << REGS[4] << endl;
	if (REGS[4] == 1) { // PRINT INT
		printLog.push_back(std::to_string(REGS[2]));
	}
	else if (REGS[4] == 10) { // EXIT
		cout << "SYSCALL EXIT" << endl;
		running = false;
	}

}