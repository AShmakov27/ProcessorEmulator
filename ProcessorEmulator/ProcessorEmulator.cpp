#include <iostream>
#include "Processor.h"



int main()
{
    setlocale(LC_ALL, "rus");

    std::vector<int> initialData = { 15, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 10, 10 };
    size_t programOffset = initialData.size();
    Memory memory(20, programOffset);

    memory.LoadData(initialData);


    std::vector<uint32_t> program = {
        0b0000000000100000u, // LOAD R0, [R2]    CmdType: 0, Operand1: 0, Operand2: 2, Operand3: 0
        0b1110000001000000u, // INC R0           CmdType: 7, Operand1: 0, Operand2: 4, Operand3: 0          
        0b1100000111000000u, // LOAD_SIZE R1     CmdType: 6, Operand1: 1, Operand2: 12, Operand3: 0
        0b0000000001000010u, // LOAD R0, [R2]    CmdType: 0, Operand1: 0, Operand2: 4, Operand3: 2
        0b0100000000110001u, // ADD R0, R3       CmdType: 2, Operand1: 0, Operand2: 3, Operand3: 1
        0b1110000001000000u, // INC R0           CmdType: 7, Operand1: 0, Operand2: 4, Operand3: 0
        0b0110001000111000u, // JUMP_IF R2 == R3 CmdType: 3, Operand1: 2, Operand2: 3, Operand3: 8         
        0b1110000001000000u, // INC R0           CmdType: 7, Operand1: 0, Operand2: 4, Operand3: 0
        0b0011100100001000u, // STORE R0, [9]    CmdType: 1, Operand1: 9, Operand2: 0, Operand3: 8
        0b1010000000000000u  // HALT             CmdType: 5, Operand1: 0, Operand2: 0, Operand3: 0
    };


    memory.LoadProgram(program, programOffset);

    Processor processor(memory);
    processor.executeProgram();

    return 0;
}