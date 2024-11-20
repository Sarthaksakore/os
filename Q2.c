#include <stdio.h>

#define PAGE_TABLE_SIZE 3

int convert_va_to_ra(const int page_table[], int page_size, int virtual_address) {
    int page_number = virtual_address / page_size;
    int offset = virtual_address % page_size;

    if (page_number >= PAGE_TABLE_SIZE) {
        printf("Error: Invalid virtual address\n");
        return -1;
    }

    int page_frame_number = page_table[page_number];
    int real_address = page_frame_number * page_size + offset;
    return real_address;
}

int main() {
    int page_table[PAGE_TABLE_SIZE] = {11, 23, 5};
    int page_size = 10;
    int virtual_address = 12;

    int real_address = convert_va_to_ra(page_table, page_size, virtual_address);

    if (real_address != -1) {
        printf("Virtual Address: %d -> Real Address: %d\n", virtual_address, real_address);
    }

    return 0;
}
