#include <stdio.h>  
#define MAX 20

void fifoPage(int pages, int frame_size, int sequence[]);


int main()  
{
    printf("\n\n\tFIFO Page replacement\n");
    int sequence[MAX];
    int frame_size, pages;
    printf("Enter no of pages : ");
    scanf("%d", &pages);
    printf("Enter sequence : ");
    for (int i=0; i<pages; i++) {
        scanf("%d", &sequence[i]);
    }
    printf("Enter frame size : ");
    scanf("%d", &frame_size);
    
    fifoPage(pages, frame_size, sequence);
    return 0;  
}  


void fifoPage(int pages, int frame_size, int sequence[]) {
    int pageFaults = 0, prevpf=0;
    
    printf("\nInput | Frame1  Frame2  Frame3 ");
    printf(" | Page fault\n");
    
    int temp[MAX];  
    for(int f = 0; f < frame_size; f++) {  
        temp[f] = -1;           // empty frames
    }
    for(int m = 0; m < pages; m++) {
        int s = 0;   
        for(int f = 0; f < frame_size; f++) {   //check page hit
            if(sequence[m] == temp[f]) {  
                s++;    // page HIT
                pageFaults--;  
            }
        } 
        pageFaults++;

        if((pageFaults <= frame_size) && (s == 0))
            temp[m] = sequence[m];

        else if(s == 0)     // page needs to be replaced
            temp[(pageFaults - 1) % frame_size] = sequence[m];     


        printf("\n%2d    |",sequence[m]);
        for(int f = 0; f < frame_size; f++) {  
            if(temp[f] != -1)  
                printf(" %d\t", temp[f]);  
            else  
                printf(" - \t");
        }
        if(pageFaults==prevpf)
            printf("|");
        else
            printf("|  %2d", pageFaults);
        prevpf = pageFaults;
    }  
    printf("\n\nTotal Page Faults:\t%d\n", pageFaults);
}
