#include <stdio.h>

#define MAX_PROCESS 10

struct Process {
    int id;
    int arrival_time;
    int burst_time;
};

void sjf(struct Process processes[], int n) {
    int remaining_time[MAX_PROCESS];
    int total_burst_time = 0;
    int shortest_job = 0;
    int completion_time[MAX_PROCESS];
    int current_time = 0;

    // Copy burst times to remaining time
    for (int i = 0; i < n; i++) {
        remaining_time[i] = processes[i].burst_time;
        total_burst_time += processes[i].burst_time;
    }

    printf("Gantt Chart:\n");
    while (total_burst_time > 0) {
        int min_burst_time = 9999; // A large number
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && remaining_time[i] > 0 && remaining_time[i] < min_burst_time) {
                shortest_job = i;
                min_burst_time = remaining_time[i];
            }
        }

        // Update current time and remaining time
        current_time++;
        total_burst_time--;
        remaining_time[shortest_job]--;

        if (remaining_time[shortest_job] == 0) {
            completion_time[shortest_job] = current_time;
        }

        printf("| P%d ", processes[shortest_job].id);
    }
    printf("|\n");

    printf("0");
    for (int i = 0; i < current_time; i++) {
        printf("    %d", i + 1);
    }
    printf("\n");

    printf("\nCompletion times:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: %d\n", processes[i].id, completion_time[i]);
    }
}

int main() {
    int n;
    struct Process processes[MAX_PROCESS];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d:\n", i + 1);
        processes[i].id = i + 1;
        printf("Arrival time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst time: ");
        scanf("%d", &processes[i].burst_time);
    }

    sjf(processes, n);

    return 0;
}