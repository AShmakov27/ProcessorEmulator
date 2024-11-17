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
        reg[op1] = memory.memory[reg[op2]];  // Загрузка данных из памяти в регистр
        std::cout << "Загрузка в регистр " << op1 << " значение " << memory.memory[reg[op2]] << std::endl;
        break;

    case STORE:
        std::cout << "Значение из R" << op2 << " (" << reg[op2] << ") записано в " << op1 << " элемент памяти." << std::endl;
        memory.memory[op1] = reg[op2];  // Сохранение данных из регистра в память
        break;

    case ADD:
        reg[op3] = reg[op1] + reg[op2];  // Сложение двух регистров с результатом в третий регистр
        std::cout << "Сложение: R" << op1 << " + R" << op2 << " = " << reg[op3] << std::endl;
        break;

    case HALT:
        std::cout << "Остановка программы" << std::endl;
        return false;

    case JUMP:
        std::cout << "Переход" << std::endl;
        pc = (int)op1;  // Переход к указанному адресу
        break;

    case JUMP_IF:
        if (reg[op1] == reg[op2]) {
            pc = (int)op3;  // Переход по адресу, если условие выполнено
        }
        break;

    case INC:
        reg[op1] += 1;  // Увеличение значения регистра на 1
        std::cout << "Увеличен регистр R" << op1 << " до " << reg[op1] << std::endl;
        break;

    case LOAD_SIZE:
        reg[op1] = memory.memory[0] + 1;  // Загружаем размер массива в регистр
        std::cout << "Загружен размер массива: " << reg[op1] << " в R" << op1 << std::endl;
        break;

    default:
        std::cerr << "Неизвестная команда: " << cmdType << std::endl;
        break;
    }

    std::cout << "PC: " << pc << "\nРегистры: ";
    for (int i = 0; i < 4; i++) {
        std::cout << "R" << i << ": " << reg[i] << " ";
    }
    std::cout << "\nПамять: ";
    for (const auto& data : memory.memory) {
        std::cout << data << " ";
    }
    std::cout << std::endl;

    return true;
}
