#include<stdio.h>
void findWaitingTime(int processes[], int n, int bt[], int wt[], int tat[]) 
{
    wt[0] = 0;
    
    int i;
    for ( i = 1; i < n; i++)
        wt[i] = bt[i - 1] + wt[i - 1];
    for (i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}
void findAverageTime(int processes[], int n, int bt[]) {
    int wt[n], tat[n];

    findWaitingTime(processes, n, bt, wt, tat);

    int total_wt = 0, total_tat = 0;
    int i;
    for ( i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
    }

    float avg_wt = (float) total_wt / (float) n;
    float avg_tat = (float) total_tat / (float) n;

    printf("Average Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tat);
}

int main() {

    int n;
     int i;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n];
    int burst_time[n];
   
    printf("Enter burst times for each process:\n");
    for (i = 0; i < n; i++) {
        printf("Burst time for process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
        processes[i] = i + 1; // Process IDs start from 1
    }

    findAverageTime(processes, n, burst_time);

    return 0;
}
