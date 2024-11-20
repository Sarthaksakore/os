#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct Process
{
    int id;
    int burst_time;
    int arrival_time;
    bool completed;

}Process;

void sovle(Process processes[],int n)
{
    int rem_time[n];
    int total_burst_time;
    int completion_time[n];

    int current_time = 0;

    for (int i = 0; i < n; i++) {
        rem_time[i] = processes[i].burst_time;
        total_burst_time += processes[i].burst_time;
    }
    while(total_burst_time > 0)
    {
        int shortest_rem_job = -1;
        int minburstTime = 999;

        for (int i = 0; i < n; i++) {
            if (!processes[i].completed && processes[i].arrival_time <= current_time && remaining_time[i] < min_burst_time) {
                shortest_job = i;
                min_burst_time = remaining_time[i];
            }
        }
    }


}
int main()
{
    
    return 0;
}