#include<bits/stdc++.h> 
using namespace std; 


void customWorstFit(int blockSize[], int m, int processSize[], int n) 
{ 
    // Stores block id of the block allocated to a process 
    int allocation[n]; 

    // Initially no block is assigned to any process 
    memset(allocation, -1, sizeof(allocation)); 

    // Pick each process and find suitable blocks 
    // according to its size and assign to it 
    for (int i = 0; i < n; i++) 
    { 
        // Find the worst fit block for the current process 
        int wstIdx = -1; 
        for (int j = 0; j < m; j++) 
        { 
            if (blockSize[j] >= processSize[i]) 
            { 
                if (wstIdx == -1) 
                    wstIdx = j; 
                else if (blockSize[wstIdx] < blockSize[j]) 
                    wstIdx = j; 
            } 
        } 

        // If we could find a block for the current process 
        if (wstIdx != -1) 
        { 
            // Allocate block wstIdx to process i 
            allocation[i] = wstIdx; 

            // Reduce available memory in this block 
            blockSize[wstIdx] -= processSize[i]; 
        } 
    } 

    cout << "\nProcess No.\tProcess Size\tBlock no.\n"; 
    for (int i = 0; i < n; i++) 
    { 
        cout << " " << i+1 << "\t\t" << processSize[i] << "\t\t"; 
        if (allocation[i] != -1) 
            cout << allocation[i] + 1; 
        else
            cout << "Not Allocated"; 
        cout << endl; 
    } 
} 

// Driver code 
int main() 
{ 
    // Different block sizes
    int blockSize[] = {200, 100, 500, 300, 400}; 
    // Different process sizes
    int processSize[] = {150, 300, 250, 200, 450}; 
    int m = sizeof(blockSize) / sizeof(blockSize[0]); 
    int n = sizeof(processSize) / sizeof(processSize[0]); 

    customWorstFit(blockSize, m, processSize, n); 

    return 0 ; 
} 
