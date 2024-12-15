#include "Assembler.h"
#include <bitset>

bool Assembler::isValidCommand(const std::string& cmdType) {
    return cmdType == "LOAD" || cmdType == "STORE" || cmdType == "ADD" ||
        cmdType == "JUMP_IF" || cmdType == "JUMP" || cmdType == "HALT" ||
        cmdType == "LOAD_SIZE" || cmdType == "INC";
}

uint32_t Assembler::generateInstruction(const std::string& cmdType, uint32_t operand1, uint32_t operand2, uint32_t operand3) {
    uint32_t binaryInstruction = 0;

    if (cmdType == "LOAD") {
        binaryInstruction = (0u << 13) | (operand1 << 8) | (operand2 << 4) | operand3;
    }
    else if (cmdType == "STORE") {
        binaryInstruction = (1u << 13) | (operand1 << 8) | (operand2 << 4) | operand3;
    }
    else if (cmdType == "ADD") {
        binaryInstruction = (2u << 13) | (operand1 << 8) | (operand2 << 4) | operand3;
    }
    else if (cmdType == "JUMP_IF") {
        binaryInstruction = (3u << 13) | (operand1 << 8) | (operand2 << 4) | operand3;
    }
    else if (cmdType == "JUMP") {
        binaryInstruction = (4u << 13) | (operand1 << 8);
    }
    else if (cmdType == "HALT") {
        binaryInstruction = (5u << 13);
    }
    else if (cmdType == "LOAD_SIZE") {
        binaryInstruction = (6u << 13) | (operand1 << 8);
    }
    else if (cmdType == "INC") {
        binaryInstruction = (7u << 13) | (operand1 << 8);
    }
    else {
        throw std::invalid_argument("Unknown command: " + cmdType);
    }

    std::cout << "Added instruction " << cmdType
        << " as " << std::bitset<16>(binaryInstruction) << std::endl;

    return binaryInstruction;
}

uint32_t Assembler::parseOperand(const std::string& operand, int commandIndex, int operandIndex) {
    try {
        return std::stoul(operand);
    }
    catch (const std::invalid_argument&) {
        if (labelTable.find(operand) != labelTable.end()) {
            return labelTable[operand];
        }

        unresolvedLabels.emplace_back(operand, commandIndex, operandIndex);
        return 0; 
    }
}

void Assembler::resolveLabels(std::vector<uint32_t>& machineCode) {
    for (const auto& unresolved : unresolvedLabels) {
        const std::string& label = std::get<0>(unresolved);
        int commandIndex = std::get<1>(unresolved);
        int operandIndex = std::get<2>(unresolved);

        if (labelTable.find(label) == labelTable.end()) {
            throw std::runtime_error("Unresolved label: " + label);
        }

        uint32_t resolvedAddress = labelTable[label];
        uint32_t instruction = machineCode[commandIndex];

        if (operandIndex == 0) {
            machineCode[commandIndex] = (instruction & 0xFFF0) | resolvedAddress;
        }
        else if (operandIndex == 1) {
            machineCode[commandIndex] = (instruction & 0xFF0F) | (resolvedAddress << 4);
        }
        else if (operandIndex == 2) {
            machineCode[commandIndex] = (instruction & 0xFFF0) | resolvedAddress;
        }
    }
}

std::vector<uint32_t> Assembler::Assemble(const std::vector<std::string>& instructions) {
    std::vector<uint32_t> machineCode;
    int commandIndex = 0;

    for (const auto& line : instructions) {
        std::string trimmedLine = line;
        trimmedLine.erase(0, trimmedLine.find_first_not_of(" \t"));
        trimmedLine.erase(trimmedLine.find_last_not_of(" \t") + 1);

        if (trimmedLine.empty()) continue;

        if (trimmedLine.back() == ':') {
            std::string label = trimmedLine.substr(0, trimmedLine.size() - 1);
            if (labelTable.find(label) != labelTable.end()) {
                throw std::runtime_error("Label already defined: " + label);
            }
            labelTable[label] = commandIndex;
            continue;
        }

        std::istringstream iss(trimmedLine);
        std::string cmdType;
        iss >> cmdType;

        if (!isValidCommand(cmdType)) {
            throw std::runtime_error("Unknown command: " + cmdType);
        }

        std::string operand1, operand2, operand3;
        iss >> operand1 >> operand2 >> operand3;

        uint32_t op1 = operand1.empty() ? 0 : parseOperand(operand1, commandIndex, 0);
        uint32_t op2 = operand2.empty() ? 0 : parseOperand(operand2, commandIndex, 1);
        uint32_t op3 = operand3.empty() ? 0 : parseOperand(operand3, commandIndex, 2);

        std::cout << "Генерируем  команду из cmdType=" << cmdType << " operand1=" << operand1 << " operand2=" << operand2 << " operand3=" << operand3 << " commandIndex= " << commandIndex << std::endl;
        uint32_t binaryInstruction = generateInstruction(cmdType, op1, op2, op3);
        machineCode.push_back(binaryInstruction);
        commandIndex++;
    }

    resolveLabels(machineCode);

    return machineCode;
}
