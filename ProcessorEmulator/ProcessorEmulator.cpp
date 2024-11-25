#include <iostream>
#include "Processor.h"

int main()
{
    setlocale(LC_ALL, "rus");

    std::vector<int> initialData = { 15, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 10, 10 }; //сумма 120
    size_t programOffset = initialData.size();
    Memory memory(20, programOffset);

    memory.LoadData(initialData);

    std::vector<uint32_t> program = {
        0b0000000000100000u, // LOAD R0, [R2]    CmdType: 0, Operand1: 0, Operand2: 2, Operand3: 0
        0b1110001000000000u, // INC R2           CmdType: 7, Operand1: 2, Operand2: 0, Operand3: 0          
        0b1100001100000000u, // LOAD_SIZE R3     CmdType: 6, Operand1: 1, Operand2: 0, Operand3: 0
        0b0000000100100000u, // LOAD R1, [R2]    CmdType: 0, Operand1: 1, Operand2: 2, Operand3: 0
        0b0100000000010000u, // ADD R0, R1       CmdType: 2, Operand1: 0, Operand2: 1, Operand3: 0
        0b1110001000000000u, // INC R2           CmdType: 7, Operand1: 2, Operand2: 0, Operand3: 0 
        0b0110001000111000u, // JUMP_IF R2 == R3 CmdType: 3, Operand1: 2, Operand2: 3, Operand3: 8         
        0b1000001100000000u, // JUMP             CmdType: 4, Operand1: 3, Operand2: 0, Operand3: 0
        0b0010100100001000u, // STORE R0, [9]    CmdType: 1, Operand1: 9, Operand2: 0, Operand3: 0
        0b1010000000000000u  // HALT             CmdType: 5, Operand1: 0, Operand2: 0, Operand3: 0
    };

    memory.LoadProgram(program, programOffset);

    Processor processor(memory);
    processor.executeProgram();

    return 0;
}