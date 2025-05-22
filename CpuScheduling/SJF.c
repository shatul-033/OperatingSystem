#include <stdio.h>

#define MAX 100

int main() {
    int n, i, j;
    int at[MAX], bt[MAX], ct[MAX], wt[MAX], tat[MAX], rt[MAX], start_time[MAX], completed[MAX];
    int min, index;
    float avg_wt = 0, avg_tat = 0, avg_rt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("P[%d] Arrival Time: ", i+1);
        scanf("%d", &at[i]);
        printf("P[%d] Burst Time: ", i+1);
        scanf("%d", &bt[i]);
        completed[i] = 0;
    }

    int t = 0, completed_count = 0;

    while(completed_count < n) {
        min = 99999;
        index = -1;

        for(i = 0; i < n; i++) {
            if(at[i] <= t && completed[i] == 0 && bt[i] < min) {
                min = bt[i];
                index = i;
            }
        }

        if(index != -1) {
            start_time[index] = t;
            t += bt[index];
            ct[index] = t;
            tat[index] = ct[index] - at[index];
            wt[index] = tat[index] - bt[index];
            rt[index] = start_time[index] - at[index];
            completed[index] = 1;
            completed_count++;
        } else {
            t++; // Idle time
        }
    }

    printf("\nP#\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for(i = 0; i < n; i++) {
        avg_wt += wt[i];
        avg_tat += tat[i];
        avg_rt += rt[i];
        printf("P[%d]\t%d\t%d\t%d\t%d\t%d\t%d\n", i+1, at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
    }

    printf("\nAverage Waiting Time: %.2f", avg_wt/n);
    printf("\nAverage Turnaround Time: %.2f", avg_tat/n);
    printf("\nAverage Response Time: %.2f\n", avg_rt/n);

    return 0;
}
// gcc sjf_pre_rt.c -o sjf_pre_rt
// ./sjf_pre_rt
