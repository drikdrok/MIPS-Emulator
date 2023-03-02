#include <iostream>
uint32_t PC = 0;
uint32_t REGS[32];
uint32_t IMEM[16384] = {
    0x214A0001, // Addi t2, t2, 1
    0x216B0005, // Addi t3, t3, 5
    0x014B4815 // Addu t1, t2, t3
}; // 2^14
uint32_t DMEM[16384];

bool running = true;

using namespace std;

void printInBinary(int num) {
    cout << num << " in binary is: ";
    for (int i = 0; i < 32; i++) {
        std::cout << ((num >> (31-i)) & 1);
    }
    cout << endl;
}

void exec_ADDU(int rd, int rs, int rt) {
    cout << "Execute ADDU" << endl;
    REGS[rd] = REGS[rs] + REGS[rt];
}

void exec_ADDI(int rs, int rt, int immediate) {
    cout << "Execute ADDI" << endl;
    REGS[rs] = REGS[rt] + immediate;
}


int fetchInstruction() {
    return IMEM[PC];
}

void exec_RTYPE(int rs, int rt, int rd, int shamt, int funct) {
    switch (funct)
    {
    case 21:
        exec_ADDU(rd, rs, rt);
        return;

    default:
        cout << "ERROR: Invalid Funct Code!" << endl;
        break;
    }
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
    else if (opcode == 8) { // Addi
        int mask = 31; // 31 = 11111 
        int rs = (instruction >> 21) & mask; //Shift 21 and get the last 5 bits
        int rt = (instruction >> 16) & mask;
        int immediate = instruction & (int)pow(2, 15)-1; // Ask Balkind why no 0x00001111
        std::cout << "rs: " << rs << std::endl;
        std::cout << "rt: " << rt << std::endl;
        std::cout << "immediate: " << immediate << std::endl;

        exec_ADDI(rs, rt, immediate);
    }

    cout << "--------" << endl;
}

int main()
{
    
    //int instruction = 0x014B4815; // Addu t1, t2, t3
    //int instruction = 0x21290001; // Addi t1, t1, 1


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

    std::cin.get();

    return 0;
}
