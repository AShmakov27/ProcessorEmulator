#include <iostream>
#include <fstream>
#include "Processor.h"
#include "Assembler.h"

int main()
{
    setlocale(LC_ALL, "rus");

    std::vector<int> initialData = { 14, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 10}; //сумма 120
    size_t programOffset = initialData.size()+1;
    Memory memory(20, programOffset);

    memory.LoadData(initialData);
    
    /*
    std::vector<uint32_t> program = {
        0b000 0 0000 0010 0000u, // LOAD R0, [R2]    CmdType: 0, Operand1: 0, Operand2: 2, Operand3: 0
        0b111 0 0010 0000 0000u, // INC R2           CmdType: 7, Operand1: 2, Operand2: 0, Operand3: 0          
        0b110 0 0011 0000 0000u, // LOAD_SIZE R3     CmdType: 6, Operand1: 3, Operand2: 0, Operand3: 0
        0b000 0 0001 0010 0000u, // LOAD R1, [R2]    CmdType: 0, Operand1: 1, Operand2: 2, Operand3: 0
        0b010 0 0000 0001 0000u, // ADD R0, R1       CmdType: 2, Operand1: 0, Operand2: 1, Operand3: 0
        0b111 0 0010 0000 0000u, // INC R2           CmdType: 7, Operand1: 2, Operand2: 0, Operand3: 0 
        0b011 0 0010 0011 1000u, // JUMP_IF R2 == R3 CmdType: 3, Operand1: 2, Operand2: 3, Operand3: 8         
        0b100 0 0011 0000 0000u, // JUMP             CmdType: 4, Operand1: 3, Operand2: 0, Operand3: 0
        0b001 0 1001 0000 0000u, // STORE R0, [9]    CmdType: 1, Operand1: 9, Operand2: 0, Operand3: 0
        0b101 0 0000 0000 0000u  // HALT             CmdType: 5, Operand1: 0, Operand2: 0, Operand3: 0
    };
    */
    std::ifstream file("C:/Users/Alex/source/repos/ProcessorEmulator/ProcessorEmulator/program.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }

    std::vector<std::string> programText;
    std::string line;
    while (std::getline(file, line)) {
        programText.push_back(line);
    }
    file.close();

    Assembler assembler;

    std::vector<uint32_t> machineCode = assembler.Assemble(programText);

    memory.LoadProgram(machineCode, programOffset);

    Processor processor(memory);
    processor.executeProgram();

    return 0;
}