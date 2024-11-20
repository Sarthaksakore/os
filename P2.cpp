#include <iostream>
#include <vector>

using namespace std;

class VirtualMachine {
private:
    vector<int> page_table;
    int page_size;

public:
    VirtualMachine(const vector<int>& pt, int ps) : page_table(pt), page_size(ps) {}

    int convert_va_to_ra(int virtual_address) {
        int page_number = virtual_address / page_size;
        int offset = virtual_address % page_size;

        if (page_number >= page_table.size()) {
            cerr << "Error: Invalid virtual address" << endl;
            return -1;
        }

        int page_frame_number = page_table[page_number];
        int real_address = page_frame_number * page_size + offset;
        return real_address;
    }
};

int main() {
    vector<int> page_table = {11, 23, 5};
    int page_size = 10;
    int virtual_address = 12;

    VirtualMachine vm(page_table, page_size);
    int real_address = vm.convert_va_to_ra(virtual_address);

    if (real_address != -1) {
        cout << "Virtual Address: " << virtual_address << " -> Real Address: " << real_address << endl;
    }

    return 0;
}
