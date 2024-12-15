#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <tuple>
#include <iostream>
#include <sstream>
#include <stdexcept>

class Assembler {
private:
    std::unordered_map<std::string, int> labelTable; 
    std::vector<std::tuple<std::string, int, int>> unresolvedLabels; 

    bool isValidCommand(const std::string& cmdType);
    uint32_t generateInstruction(const std::string& cmdType, uint32_t operand1, uint32_t operand2, uint32_t operand3);
    uint32_t parseOperand(const std::string& operand, int commandIndex, int operandIndex);
    void resolveLabels(std::vector<uint32_t>& machineCode);

public:
    std::vector<uint32_t> Assemble(const std::vector<std::string>& instructions);
};

#endif // ASSEMBLER_H
