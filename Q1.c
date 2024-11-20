#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MEMORY_SIZE 200

typedef struct {
    int memory[MEMORY_SIZE];
    int general_purpose_register;
    char instruction_register[10];
    int instruction_counter;
    int toggle_register;
    const char* instruction_set[7];
} VirtualMachine;

void initialize_vm(VirtualMachine* vm) {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        vm->memory[i] = 0;
    }
    vm->general_purpose_register = 0;
    vm->instruction_register[0] = '\0';
    vm->instruction_counter = 0;
    vm->toggle_register = 0;
    vm->instruction_set[0] = "GD";
    vm->instruction_set[1] = "PD";
    vm->instruction_set[2] = "LR";
    vm->instruction_set[3] = "SR";
    vm->instruction_set[4] = "CR";
    vm->instruction_set[5] = "BT";
    vm->instruction_set[6] = "H";
}

int is_valid_opcode(VirtualMachine* vm, const char* opcode) {
    for (int i = 0; i < 7; i++) {
        if (strcmp(vm->instruction_set[i], opcode) == 0) {
            return 1;
        }
    }
    return 0;
}

int is_valid_operand(const char* operand) {
    for (int i = 0; operand[i] != '\0'; i++) {
        if (!isdigit(operand[i])) {
            return 0;
        }
    }
    int value = atoi(operand);
    return value >= 0 && value < MEMORY_SIZE;
}

void execute_program(VirtualMachine* vm, const char program[][10], int program_size) {
    while (vm->instruction_counter < program_size) {
        strcpy(vm->instruction_register, program[vm->instruction_counter]);
        char opcode[3];
        char operand[8];
        strncpy(opcode, vm->instruction_register, 2);
        opcode[2] = '\0';
        strcpy(operand, vm->instruction_register + 2);

        if (!is_valid_opcode(vm, opcode)) {
            printf("Error: Invalid opcode '%s' at address %d\n", opcode, vm->instruction_counter);
            break;
        }

        if (!is_valid_operand(operand)) {
            printf("Error: Invalid operand '%s' at address %d\n", operand, vm->instruction_counter);
            break;
        }

        int operand_value = atoi(operand);
        if (strcmp(opcode, "LR") == 0) {
            vm->general_purpose_register = vm->memory[operand_value];
        } else if (strcmp(opcode, "SR") == 0) {
            vm->memory[operand_value] = vm->general_purpose_register;
        } else if (strcmp(opcode, "GD") == 0) {
            printf("Execute GD\n");
        } else if (strcmp(opcode, "PD") == 0) {
            printf("Data: %d\n", vm->memory[operand_value]);
        } else if (strcmp(opcode, "CR") == 0) {
            vm->toggle_register = (vm->general_purpose_register == vm->memory[operand_value]);
        } else if (strcmp(opcode, "BT") == 0) {
            if (vm->toggle_register) {
                vm->instruction_counter = operand_value - 1;
            }
        } else if (strcmp(opcode, "H") == 0) {
            printf("Program Halted\n");
            break;
        }

        vm->instruction_counter++;
    }
}

int main() {
    const char program[][10] = {
        "LR50",  // Potential invalid operand
        "SR999", // Invalid operand
        "GDXX",  // Invalid opcode
        "PD10",
        "CR20",
        "BT5",
        "H"
    };

    VirtualMachine vm;
    initialize_vm(&vm);
    execute_program(&vm, program, sizeof(program) / sizeof(program[0]));

    return 0;
}
