#ifndef MEMORY_H
#define MEMORY_H

#include <vector>
#include "Instruction.h"

class Memory {
public:
    std::vector<int> memory;
    int Offset;

    Memory(int dataSize, int programOffset);
    void LoadData(const std::vector<int>& initialData);
    void LoadProgram(const std::vector<uint32_t>& program, size_t offset);
    Instruction FetchInstruction(int pc);
};

#endif // MEMORY_H
