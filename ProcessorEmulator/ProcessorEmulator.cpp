#include <iostream>
#include "Processor.h"



int main()
{
    setlocale(LC_ALL, "rus");

    // Инициализация данных в памяти
    std::vector<int> initialData = { 15, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 10, 10 };
    size_t programOffset = initialData.size();
    Memory memory(20, programOffset);

    memory.LoadData(initialData);

    // Программа (трехадресные команды)
    std::vector<uint32_t> program = {
        0b0000000000100000u, // LOAD R0, [R2]   -> CmdType: 000 (LOAD), Operand1: 0, Operand2: 2, Operand3: 0
        0b1110000001000000u, // INC R2          -> CmdType: 111 (INC), Operand1: 2, Operand2: 0, Operand3: 0
        0b1100000011000000u, // LOAD_SIZE R3    -> CmdType: 110 (LOAD_SIZE), Operand1: 3, Operand2: 0, Operand3: 0
        0b0000000001000010u, // LOAD R1, [R2]   -> CmdType: 000 (LOAD), Operand1: 1, Operand2: 2, Operand3: 0
        0b0100000001000001u, // ADD R0, R1      -> CmdType: 010 (ADD), Operand1: 0, Operand2: 1, Operand3: 0
        0b1110000001000000u, // INC R2          -> CmdType: 111 (INC), Operand1: 2, Operand2: 0, Operand3: 0
        0b0110000001001110u, // JUMP_IF R2 == R3 -> CmdType: 011 (JUMP_IF), Operand1: 2, Operand2: 3, Operand3: 0
        0b1000000000000000u, // JUMP START      -> CmdType: 100 (JUMP), Operand1: 0, Operand2: 0, Operand3: 0
        0b0011000100001000u, // STORE R0, [9]   -> CmdType: 001 (STORE), Operand1: 0, Operand2: 0, Operand3: 9
        0b1010000000000000u  // HALT            -> CmdType: 101 (HALT), Operand1: 0, Operand2: 0, Operand3: 0
    };


    memory.LoadProgram(program, programOffset);

    // Создание процессора и выполнение программы
    Processor processor(memory);
    processor.executeProgram();

    return 0;
}