#include <iostream>
#include <vector>
#include <string>

using namespace std;

class VirtualMachine {
private:
    vector<int> memory;
    int general_purpose_register;
    string instruction_register;
    int instruction_counter;
    bool toggle_register;
    vector<string> instruction_set;

public:
    VirtualMachine() {
        memory.resize(200, 0);  // 200 words of main memory
        general_purpose_register = 0;
        instruction_register = "";
        instruction_counter = 0;
        toggle_register = false;
        instruction_set = {"GD", "PD", "LR", "SR", "CR", "BT", "H", "ADD"};
    }

    void load_program(const vector<string>& program) {
        for (size_t i = 0; i < program.size(); ++i) {
            memory[i] = stoi(program[i]);
        }
    }

    bool is_valid_opcode(const string& opcode) {
        for (const auto& instr : instruction_set) {
            if (instr == opcode) {
                return true;
            }
        }
        return false;
    }

    bool is_valid_operand(const string& operand) {
        for (char ch : operand) {
            if (!isdigit(ch)) {
                return false;
            }
        }
        return stoi(operand) < memory.size();
    }

    void execute_program() {
        while (instruction_counter < memory.size()) {
            instruction_register = to_string(memory[instruction_counter]);
            string opcode = instruction_register.substr(0, 2);
            string operand = instruction_register.substr(2);

            if (!is_valid_opcode(opcode)) {
                cerr << "Error: Invalid opcode '" << opcode << "' at address " << instruction_counter << endl;
                break;
            }

            if (!is_valid_operand(operand)) {
                cerr << "Error: Invalid operand '" << operand << "' at address " << instruction_counter << endl;
                break;
            }

            int operand_value = stoi(operand);
            if (opcode == "LR") {
                general_purpose_register = memory[operand_value];
            } else if (opcode == "SR") {
                memory[operand_value] = general_purpose_register;
            } else if (opcode == "GD") {
                cout << "Execute GD" << endl;
            } else if (opcode == "PD") {
                cout << "Data: " << general_purpose_register << endl;
            } else if (opcode == "CR") {
                toggle_register = (general_purpose_register == memory[operand_value]);
            } else if (opcode == "BT") {
                if (toggle_register) {
                    instruction_counter = operand_value - 1;
                }
            } else if (opcode == "H") {
                cout << "Program Halted" << endl;
                break;
            } else if (opcode == "ADD") {
                general_purpose_register += memory[operand_value];
            }

            instruction_counter++;
        }
    }
};

int main() {
    vector<string> program = {
        "LR10",  // Load value from memory address 10
        "ADD20", // Add value from memory address 20 to register
        "PD0",   // Print the register value
        "H"      // Halt
    };

    VirtualMachine vm;
    vm.load_program(program);
    vm.execute_program();

    return 0;
}
