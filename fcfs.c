#include<stdio.h>

struct Process {
    int process_id;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

void calculateTimes(struct Process processes[], int n) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int current_time = 0;

    printf("\nGantt Chart:\n");
    printf("|");
    for (int i = 0; i < n; i++) {
        printf(" P%d |", processes[i].process_id);
    }
    
    printf("\n");

    printf("0    ");
    for (int i = 0; i < n; i++) {
        
        processes[i].completion_time = current_time + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;

        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time; 

        current_time = processes[i].completion_time;

        
        printf("%d    ", processes[i].completion_time);
    }
    printf("\n");

    float avg_waiting_time = (float) total_waiting_time / n;
    float avg_turnaround_time = (float) total_turnaround_time / n;

    printf("\nProcess\t Burst Time\t Completion Time\t Turnaround Time\t Waiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t  %d\t\t %d\t\t\t %d\t\t\t %d\n", processes[i].process_id,
               processes[i].burst_time, processes[i].completion_time,
               processes[i].turnaround_time, processes[i].waiting_time);
    }

    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    printf("Enter Burst Time for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i].process_id = i + 1;
        printf("Process %d:\n", processes[i].process_id);
        
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
    }

    calculateTimes(processes, n);

    return 0;
}