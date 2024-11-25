#include "Memory.h"
#include <iostream>
#include <stdexcept>

Memory::Memory(int dataSize, int programOffset) : memory(dataSize+ programOffset, 0) 
{
    Offset = programOffset;
}

void Memory::LoadData(const std::vector<int>& initialData) {
    if (initialData.size() > memory.size()) {
        throw std::out_of_range("Data size exceeds memory capacity.");
    }
    for (size_t i = 0; i < initialData.size(); ++i) {
        memory[i] = initialData[i];
    }
}

void Memory::LoadProgram(const std::vector<uint32_t>& program, size_t offset) {
    if (offset + program.size() > memory.size()) {
        throw std::out_of_range("Program size exceeds memory capacity with the given offset.");
    }
    for (size_t i = 0; i < program.size(); ++i) {
        memory[offset + i] = program[i];
    }
}

Instruction Memory::FetchInstruction(int pc) {
    if (pc < 0 || static_cast<size_t>(pc+Offset) >= memory.size()) {
        throw std::out_of_range("Program counter is out of memory bounds.");
    }
    uint32_t binaryInstruction = memory[pc+Offset];
    Instruction instruction(binaryInstruction);
    std::cout << "Fetched instruction: " << instruction.ToString() << std::endl;
    return instruction;
}
