#pragma once
#include <iostream>
#include <vector>

using namespace std;

void printInBinary(int num) {
    cout << num << " in binary is: ";
    for (int i = 0; i < 32; i++) {
        std::cout << ((num >> (31 - i)) & 1);
    }
    cout << endl;
}


vector<int> iTypes = {4, 8, 9, 35, 43};
bool isI_Type(int opcode) {
    for (int i = 0; i < iTypes.size(); i++) 
        if (opcode == iTypes[i])
            return true;
    return false;
}