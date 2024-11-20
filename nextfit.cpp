#include <iostream>
#include <vector>

using namespace std;


void nextFit(int blockSize[], int m, int processSize[], int n) {
    vector<int> allocation(n, -1);
    int j = 0;
    int t = m - 1;

    // pick each process and find suitable blocks
    // according to its size and assign to it
    for (int i = 0; i < n; i++) {
        // Do not start from beginning
        while (j < m) {
            if (blockSize[j] >= processSize[i]) {
                // Allocate block j to process i
                allocation[i] = j;

                // Reduce available memory in this block.
                blockSize[j] -= processSize[i];

                // Sets a new end point
                t = (j - 1) % m;
                break;
            }
            if (t == j) {
                // Sets a new end point
                t = (j - 1) % m;
                // Breaks the loop after going through all memory blocks
                break;
            }

            // Mod m will help in traversing the
            // blocks from starting block after
            // we reach the end.
            j = (j + 1) % m;
        }
    }

    cout << "\nProcess No.\tProcess Size\tBlock no.\n";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << "\t\t\t\t" << processSize[i] << "\t\t\t\t";
        if (allocation[i] != -1) {
            cout << allocation[i] + 1;
        } else {
            cout << "Not Allocated";
        }
        cout << endl;
    }
}

// Driver program
int main() {
    int blockSize[] = {5, 10, 20};
    int processSize[] = {10, 5, 20};
    int m = sizeof(blockSize) / sizeof(blockSize[0]);
    int n = sizeof(processSize) / sizeof(processSize[0]);
    nextFit(blockSize, m, processSize, n);
    return 0;
}
