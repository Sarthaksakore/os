#include<iostream> 
using namespace std; 

// Method to allocate memory to blocks as per Custom Best Fit algorithm 
void customBestFit(int blockSize[], int m, int processSize[], int n) 
{ 
    // Stores block id of the block allocated to a process 
    int allocation[n]; 

    // Initially no block is assigned to any process 
    for (int i = 0; i < n; i++) 
        allocation[i] = -1; 

    // Pick each process and find suitable blocks 
    // according to its size and assign to it 
    for (int i = 0; i < n; i++) 
    { 
        // Find the best fit block for the current process 
        int bestIdx = -1; 
        for (int j = 0; j < m; j++) 
        { 
            if (blockSize[j] >= processSize[i]) 
            { 
                if (bestIdx == -1) 
                    bestIdx = j; 
                else if (blockSize[bestIdx] > blockSize[j]) 
                    bestIdx = j; 
            } 
        } 

        // If we could find a block for the current process 
        if (bestIdx != -1) 
        { 
            // Allocate block bestIdx to process i 
            allocation[i] = bestIdx; 

            // Reduce available memory in this block 
            blockSize[bestIdx] -= processSize[i]; 
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

// Driver Method 
int main() 
{ 
    // Different block sizes
    int blockSize[] = {300, 400, 200, 250, 600}; 
    // Different process sizes
    int processSize[] = {150, 300, 250, 200, 450}; 
    int m = sizeof(blockSize) / sizeof(blockSize[0]); 
    int n = sizeof(processSize) / sizeof(processSize[0]); 

    customBestFit(blockSize, m, processSize, n); 

    return 0 ; 
}
