#include <stdio.h>
#define MAX 100

int main() {
    int n, i, j;
    int at[MAX], bt[MAX], pr[MAX], ct[MAX], wt[MAX], tat[MAX], rt[MAX];
    float avg_wt = 0, avg_tat = 0, avg_rt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("P[%d] Arrival Time: ", i+1);
        scanf("%d", &at[i]);
        printf("P[%d] Burst Time: ", i+1);
        scanf("%d", &bt[i]);
        printf("P[%d] Priority (lower number = higher priority): ", i+1);
        scanf("%d", &pr[i]);
    }

    // Sort by arrival time, then priority
    for(i = 0; i < n-1; i++) {
        for(j = i+1; j < n; j++) {
            if(at[i] > at[j] || (at[i] == at[j] && pr[i] > pr[j])) {
                int temp;
                temp = at[i]; at[i] = at[j]; at[j] = temp;
                temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
                temp = pr[i]; pr[i] = pr[j]; pr[j] = temp;
            }
        }
    }

    int t = 0;
    for(i = 0; i < n; i++) {
        if(t < at[i]) t = at[i];
        rt[i] = t - at[i];
        wt[i] = t - at[i];
        ct[i] = t + bt[i];
        tat[i] = ct[i] - at[i];

        avg_wt += wt[i];
        avg_rt += rt[i];
        avg_tat += tat[i];

        t += bt[i];
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
