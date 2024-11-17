#include "Processor.h"
#include <iostream>

Processor::Processor(Memory& mem) : memory(mem) {}

void Processor::executeProgram() {
    bool running = true;
    while (running) {
        if (pc < 0 || pc >= static_cast<int>(memory.memory.size())) {
            std::cerr << "Program counter exceeded program size!" << std::endl;
            break; 
        }
        Instruction instruction = memory.FetchInstruction(pc); 
        running = decodeAndExecute(instruction);  

        if (!running) {
            break; 
        }

        if (instruction.CmdType != JUMP && instruction.CmdType != JUMP_IF) {
            pc++;
        }

        std::cout << std::endl;
    }
}

bool Processor::decodeAndExecute(const Instruction& instruction) {

    uint32_t cmdType = instruction.CmdType;
    uint32_t op1 = instruction.Operand1;
    uint32_t op2 = instruction.Operand2;
    uint32_t op3 = instruction.Operand3;

    switch (cmdType) {
    case LOAD:
        reg[op1] = memory.memory[reg[op2]];  // �������� ������ �� ������ � �������
        std::cout << "�������� � ������� " << op1 << " �������� " << memory.memory[reg[op2]] << std::endl;
        break;

    case STORE:
        std::cout << "�������� �� R" << op2 << " (" << reg[op2] << ") �������� � " << op1 << " ������� ������." << std::endl;
        memory.memory[op1] = reg[op2];  // ���������� ������ �� �������� � ������
        break;

    case ADD:
        reg[op3] = reg[op1] + reg[op2];  // �������� ���� ��������� � ����������� � ������ �������
        std::cout << "��������: R" << op1 << " + R" << op2 << " = " << reg[op3] << std::endl;
        break;

    case HALT:
        std::cout << "��������� ���������" << std::endl;
        return false;

    case JUMP:
        std::cout << "�������" << std::endl;
        pc = (int)op1;  // ������� � ���������� ������
        break;

    case JUMP_IF:
        if (reg[op1] == reg[op2]) {
            pc = (int)op3;  // ������� �� ������, ���� ������� ���������
        }
        break;

    case INC:
        reg[op1] += 1;  // ���������� �������� �������� �� 1
        std::cout << "�������� ������� R" << op1 << " �� " << reg[op1] << std::endl;
        break;

    case LOAD_SIZE:
        reg[op1] = memory.memory[0] + 1;  // ��������� ������ ������� � �������
        std::cout << "�������� ������ �������: " << reg[op1] << " � R" << op1 << std::endl;
        break;

    default:
        std::cerr << "����������� �������: " << cmdType << std::endl;
        break;
    }

    std::cout << "PC: " << pc << "\n��������: ";
    for (int i = 0; i < 4; i++) {
        std::cout << "R" << i << ": " << reg[i] << " ";
    }
    std::cout << "\n������: ";
    for (const auto& data : memory.memory) {
        std::cout << data << " ";
    }
    std::cout << std::endl;

    return true;
}
