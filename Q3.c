#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MEMORY_SIZE 200

// Global variables
int memory[MEMORY_SIZE];
int general_purpose_register = 0;
char instruction_register[10];
int instruction_counter = 0;
bool toggle_register = false;
const char *instruction_set[] = {"GD", "PD", "LR", "SR", "CR", "BT", "H", "ADD"};
int instruction_set_size = 8;

// Function to check if an opcode is valid
bool is_valid_opcode(const char *opcode) {
    for (int i = 0; i < instruction_set_size; i++) {
        if (strcmp(opcode, instruction_set[i]) == 0) {
            return true;
        }
    }
    return false;
}

// Function to check if an operand is valid
bool is_valid_operand(const char *operand) {
    for (int i = 0; operand[i] != '\0'; i++) {
        if (operand[i] < '0' || operand[i] > '9') {
            return false;
        }
    }
    int operand_value = atoi(operand);
    return operand_value < MEMORY_SIZE;
}

// Function to load the program into memory
void load_program(const char *program[], int program_size) {
    for (int i = 0; i < program_size; i++) {
        memory[i] = atoi(program[i]);
    }
}

// Function to execute the program
void execute_program() {
    while (instruction_counter < MEMORY_SIZE) {
        sprintf(instruction_register, "%d", memory[instruction_counter]);
        char opcode[3];
        char operand[10];
        strncpy(opcode, instruction_register, 2);
        opcode[2] = '\0';
        strcpy(operand, instruction_register + 2);

        if (!is_valid_opcode(opcode)) {
            printf("Error: Invalid opcode '%s' at address %d\n", opcode, instruction_counter);
            break;
        }

        if (!is_valid_operand(operand)) {
            printf("Error: Invalid operand '%s' at address %d\n", operand, instruction_counter);
            break;
        }

        int operand_value = atoi(operand);
        if (strcmp(opcode, "LR") == 0) {
            general_purpose_register = memory[operand_value];
        } else if (strcmp(opcode, "SR") == 0) {
            memory[operand_value] = general_purpose_register;
        } else if (strcmp(opcode, "GD") == 0) {
            printf("Execute GD\n");
        } else if (strcmp(opcode, "PD") == 0) {
            printf("Data: %d\n", general_purpose_register);
        } else if (strcmp(opcode, "CR") == 0) {
            toggle_register = (general_purpose_register == memory[operand_value]);
        } else if (strcmp(opcode, "BT") == 0) {
            if (toggle_register) {
                instruction_counter = operand_value - 1;
            }
        } else if (strcmp(opcode, "H") == 0) {
            printf("Program Halted\n");
            break;
        } else if (strcmp(opcode, "ADD") == 0) {
            general_purpose_register += memory[operand_value];
        }

        instruction_counter++;
    }
}

int main() {
    // Program to be loaded into memory
    const char *program[] = {
        "1010",  // LR10: Load value from memory address 10
        "2020",  // ADD20: Add value from memory address 20 to register
        "3000",  // PD0: Print the register value
        "4000"   // H: Halt
    };

    int program_size = sizeof(program) / sizeof(program[0]);

    // Initialize memory
    for (int i = 0; i < MEMORY_SIZE; i++) {
        memory[i] = 0;
    }

    // Pre-load some memory values for the program
    memory[10] = 5;  // Value at memory address 10
    memory[20] = 10; // Value at memory address 20

    // Load and execute the program
    load_program(program, program_size);
    execute_program();

    return 0;
}
