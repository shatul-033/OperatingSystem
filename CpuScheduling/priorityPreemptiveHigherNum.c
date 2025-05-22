#include <stdio.h>
#define MAX 100

int main() {
    int n, i, j;
    int at[MAX], bt[MAX], pr[MAX], ct[MAX], wt[MAX], tat[MAX], rt[MAX];
    int completed[MAX] = {0};
    float avg_wt = 0, avg_tat = 0, avg_rt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("P[%d] Arrival Time: ", i+1);
        scanf("%d", &at[i]);
        printf("P[%d] Burst Time: ", i+1);
        scanf("%d", &bt[i]);
        printf("P[%d] Priority (higher number = higher priority): ", i+1);
        scanf("%d", &pr[i]);
        rt[i] = -1;  // Initialize response time
    }

    int t = 0, completed_count = 0;

    while(completed_count < n) {
        int idx = -1;
        int highest_priority = -1;

        // Find process with highest priority (bigger number = higher priority)
        for(i = 0; i < n; i++) {
            if(at[i] <= t && completed[i] == 0) {
                if(pr[i] > highest_priority) {
                    highest_priority = pr[i];
                    idx = i;
                }
                // If same priority, choose earlier arrival
                else if(pr[i] == highest_priority && at[i] < at[idx]) {
                    idx = i;
                }
            }
        }

        if(idx != -1) {
            if(rt[idx] == -1) {
                rt[idx] = t - at[idx];
            }
            t += bt[idx];
            ct[idx] = t;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            completed[idx] = 1;
            completed_count++;
            avg_wt += wt[idx];
            avg_tat += tat[idx];
            avg_rt += rt[idx];
        } else {
            t++;  // CPU is idle
        }
    }

    printf("\nP#\tAT\tBT\tPri\tCT\tTAT\tWT\tRT\n");
    for(i = 0; i < n; i++) {
        printf("P[%d]\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", i+1, at[i], bt[i], pr[i], ct[i], tat[i], wt[i], rt[i]);
    }

    printf("\nAverage Waiting Time: %.2f", avg_wt/n);
    printf("\nAverage Turnaround Time: %.2f", avg_tat/n);
    printf("\nAverage Response Time: %.2f\n", avg_rt/n);

    return 0;
}
// nano priority.c       # কোড লিখে save করুন (Ctrl+O, Enter, Ctrl+X)
// gcc priority.c -o priority
// ./priority
