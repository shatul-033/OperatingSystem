#include <stdio.h>

#define MAX 100

int main() {
    int n, i;
    int at[MAX], bt[MAX], rt[MAX], ct[MAX], wt[MAX], tat[MAX], rt_time[MAX];
    int start_time[MAX], is_started[MAX] = {0};
    int completed = 0, t = 0, shortest = -1, min_time = 99999;
    float avg_wt = 0, avg_tat = 0, avg_rt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("P[%d] Arrival Time: ", i+1);
        scanf("%d", &at[i]);
        printf("P[%d] Burst Time: ", i+1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
    }

    while(completed != n) {
        shortest = -1;
        min_time = 99999;

        for(i = 0; i < n; i++) {
            if(at[i] <= t && rt[i] > 0 && rt[i] < min_time) {
                min_time = rt[i];
                shortest = i;
            }
        }

        if(shortest == -1) {
            t++;
            continue;
        }

        // First time the process is getting CPU
        if(is_started[shortest] == 0) {
            start_time[shortest] = t;
            is_started[shortest] = 1;
        }

        rt[shortest]--;
        t++;

        if(rt[shortest] == 0) {
            completed++;
            ct[shortest] = t;
            tat[shortest] = ct[shortest] - at[shortest];
            wt[shortest] = tat[shortest] - bt[shortest];
            rt_time[shortest] = start_time[shortest] - at[shortest]; // Response Time
            avg_wt += wt[shortest];
            avg_tat += tat[shortest];
            avg_rt += rt_time[shortest];
        }
    }

    printf("\nP#\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for(i = 0; i < n; i++) {
        printf("P[%d]\t%d\t%d\t%d\t%d\t%d\t%d\n", i+1, at[i], bt[i], ct[i], tat[i], wt[i], rt_time[i]);
    }

    printf("\nAverage Waiting Time: %.2f", avg_wt/n);
    printf("\nAverage Turnaround Time: %.2f", avg_tat/n);
    printf("\nAverage Response Time: %.2f\n", avg_rt/n);

    return 0;
}
