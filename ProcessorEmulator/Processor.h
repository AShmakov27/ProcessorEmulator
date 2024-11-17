#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "Memory.h"
#include "Instruction.h"

class Processor {
private:
    int reg[4] = { 0 };  
    int pc = 0;       

    static const uint32_t LOAD = 0;     // 000
    static const uint32_t STORE = 1;    // 001
    static const uint32_t ADD = 2;      // 010
    static const uint32_t JUMP_IF = 3;  // 011
    static const uint32_t JUMP = 4;     // 100
    static const uint32_t HALT = 5;     // 101
    static const uint32_t LOAD_SIZE = 6;// 110
    static const uint32_t INC = 7;      // 111

    Memory& memory;

public:
    Processor(Memory& mem);
    void executeProgram();

private:
    bool decodeAndExecute(const Instruction& instruction);
};

#endif // PROCESSOR_H

