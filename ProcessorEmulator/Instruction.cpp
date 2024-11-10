#include "Instruction.h"

Instruction::Instruction(uint32_t binaryInstruction) {
    CmdType = (binaryInstruction >> 13) & 0x7;   // Биты 15-13
    Operand1 = (binaryInstruction >> 8) & 0xF;   // Биты 11-8
    Operand2 = (binaryInstruction >> 4) & 0xF;   // Биты 7-4
    Operand3 = binaryInstruction & 0xF;          // Биты 3-0

    std::cout << "binaryInstruction: " << std::bitset<16>(binaryInstruction) << std::endl;
}

std::string Instruction::ToString() const {
    return "CmdType: " + std::bitset<3>(CmdType).to_string() +
        ", Operand1: " + std::bitset<4>(Operand1).to_string() +
        ", Operand2: " + std::bitset<4>(Operand2).to_string() +
        ", Operand3: " + std::bitset<4>(Operand3).to_string();
}
