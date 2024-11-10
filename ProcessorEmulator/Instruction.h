#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>
#include <bitset>
#include <iostream>

class Instruction {
public:
    uint32_t CmdType;
    uint32_t Operand1;
    uint32_t Operand2;
    uint32_t Operand3;

    Instruction(uint32_t binaryInstruction);
    std::string ToString() const;
};

#endif // INSTRUCTION_H

