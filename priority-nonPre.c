#include <stdio.h>

#define max 10

void priorityNonPre(int n, int AT[], int BT[], int pri[]);
void display (int n, int AT[], int BT[], int pri[], int WT[], int CT[], int TAT[]);

int main () 
{
    int n;
  
    int AT[max], BT[max], pri[max];  
    printf("\nEnter number of processes : "); 
    scanf("%d", &n);

    for (int i=0; i<n; i++ ) {
        printf("Enter the prioirity, AT, BT of P%d : ", i+1);
        scanf("%d %d %d", &pri[i], &AT[i], &BT[i]);
    }
  
    priorityNonPre (n, AT, BT, pri);
    return 0;
}

void priorityNonPre(int n, int AT[], int BT[], int pri[]) {
    int WT[max]={0}, CT[max]={0}, TAT[max]={0};
    int totalBT=0, oldBT[max];

    for (int i=0; i<n; i++) {
        totalBT += BT[i];
        oldBT[i] = BT[i];
    }

    printf("\n\n\t Priority (Non-Preemptive)\n\n");
    printf(" Gantt chart : ");
    int job, currentTime=0;
    while(totalBT!=0) {
        job=-1;
        
        for(int i=0; i<n; i++) {                        
            if ( (BT[i]!=0) && (AT[i]<=currentTime) ) {     // find which process available
                if (pri[i]<pri[job] || job==-1)             // fimd more prioirty  proces among available ones
                    job = i;
            }
        }         

        if (job == -1) {
            currentTime++;
            continue;
        }
        printf("(%d) P%d ", currentTime, job+1);
        currentTime += BT[job];
        CT[job] = currentTime;
        TAT[job] = CT[job] - AT[job];
        WT[job] = TAT[job] - BT[job];
        totalBT -= BT[job];
        BT[job] = 0;
    }
    printf("(%d)\n", currentTime);
    display(n, AT, oldBT, pri, WT, CT, TAT);
}

void display (int n, int AT[], int BT[], int pri[], int WT[], int CT[], int TAT[])
{
    printf("\n ----------------------------------------------------\n");
    printf("|  Pid  | prior |  AT  |  BT  ||  WT  |  CT  |  TAT  |\n");
    printf("|_______|_______|______|______||______|______|_______|\n");

    float sumWT=0, sumTAT=0;
    for (int i=0; i<n; i++) {
    printf("|  P%d   |  %2d   |  %2d  |  %2d  ||  %2d  |  %2d  |  %2d   |\n", i+1, pri[i], AT[i], BT[i], WT[i], CT[i], TAT[i]);
        sumWT += WT[i];
        sumTAT += TAT[i];
    }
    printf(" ----------------------------------------------------\n");
    printf("\nAvg WT : %.1f\n", sumWT/n);
    printf("Avg TAT : %.1f\n", sumTAT/n);
}