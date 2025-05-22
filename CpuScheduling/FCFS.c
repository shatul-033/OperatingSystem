#include <stdio.h>

#define MAX 30

int main() {
    int i, j, n;
    int bt[MAX], at[MAX], wt[MAX], tat[MAX], rt[MAX], ct[MAX], start_time[MAX];
    float awt = 0, atat = 0, art = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter Arrival Time and Burst Time for each process:\n");
    for(i = 0; i < n; i++) {
        printf("P[%d] Arrival Time: ", i+1);
        scanf("%d", &at[i]);
        printf("P[%d] Burst Time: ", i+1);
        scanf("%d", &bt[i]);
    }

    // Sort processes by Arrival Time (FCFS)
    for(i = 0; i < n-1; i++) {
        for(j = i+1; j < n; j++) {
            if(at[i] > at[j]) {
                int temp = at[i]; at[i] = at[j]; at[j] = temp;
                temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
            }
        }
    }

    // First process
    start_time[0] = at[0];
    wt[0] = 0;
    rt[0] = 0;
    tat[0] = bt[0];
    ct[0] = start_time[0] + bt[0];

    // Total time for first process
    awt += wt[0];
    atat += tat[0];
    art += rt[0];

    // Rest of the processes
    for(i = 1; i < n; i++) {
        start_time[i] = ct[i-1]; // Start after previous completes
        if(start_time[i] < at[i]) {
            start_time[i] = at[i]; // If CPU idle
        }

        wt[i] = start_time[i] - at[i];
        rt[i] = wt[i];
        tat[i] = bt[i] + wt[i];
        ct[i] = start_time[i] + bt[i];

        awt += wt[i];
        atat += tat[i];
        art += rt[i];
    }

    // Output
    printf("\nProcess\tAT\tBT\tCT\tWT\tTAT\tRT\n");
    for(i = 0; i < n; i++) {
        printf("P[%d]\t%d\t%d\t%d\t%d\t%d\t%d\n", i+1, at[i], bt[i], ct[i], wt[i], tat[i], rt[i]);
    }

    printf("\nAverage Waiting Time: %.2f", awt / n);
    printf("\nAverage Turnaround Time: %.2f", atat / n);
    printf("\nAverage Response Time: %.2f\n", art / n);

    return 0;
}
