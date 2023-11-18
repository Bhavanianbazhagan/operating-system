#include <stdio.h>
struct Process 
{
    int id;           
    int priority;     
    int burst_time;   
};

void priorityScheduling(struct Process processes[], int n)  
{
	int i,j;
    for ( i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (processes[j].priority < processes[j + 1].priority) {
                // Swap the processes
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    int waiting_time[n], turnaround_time[n];
    waiting_time[0] = 0;
    turnaround_time[0] = processes[0].burst_time;
    for (i = 1; i < n; i++) {
        waiting_time[i] = waiting_time[i - 1] + processes[i - 1].burst_time;
        turnaround_time[i] = waiting_time[i] + processes[i].burst_time;
    }

    float avg_waiting_time = 0, avg_turnaround_time = 0;
    for (i = 0; i < n; i++) {
        avg_waiting_time += waiting_time[i];
        avg_turnaround_time += turnaround_time[i];
    }
    avg_waiting_time /= n;
    avg_turnaround_time /= n;
    printf("\nProcess\tPriority\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].priority,
               processes[i].burst_time, waiting_time[i], turnaround_time[i]);
    }

    printf("\nAverage Waiting Time: %.2f", avg_waiting_time);
    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time);
}

int main() {
    int n,i;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process processes[n];
    for (i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter priority for process %d: ", i + 1);
        scanf("%d", &processes[i].priority);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
    }
    
    priorityScheduling(processes, n);

    return 0;
}

