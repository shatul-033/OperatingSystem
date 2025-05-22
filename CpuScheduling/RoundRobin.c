#include <stdio.h>
#define MAX 100

int main() {
    int n, i, tq;
    int bt[MAX], at[MAX], rt[MAX], ct[MAX], tat[MAX], wt[MAX], rt_done[MAX];
    int t = 0, completed = 0;
    float avg_wt = 0, avg_tat = 0, avg_rt = 0;
6
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter time quantum: ");
    scanf("%d", &tq);

    for(i = 0; i < n; i++) {
        printf("P[%d] Arrival Time: ", i+1);
        scanf("%d", &at[i]);
        printf("P[%d] Burst Time: ", i+1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
        rt_done[i] = -1; // Not yet started
    }

    int queue[MAX], front = 0, rear = 0, mark[MAX] = {0};
    int visited[MAX] = {0};
    queue[rear++] = 0;
    mark[0] = 1;
    t = at[0];

    while(completed < n) {
        int idx = queue[front++];

        if(rt_done[idx] == -1) {
            rt_done[idx] = t - at[idx]; // response time = first CPU access - arrival
            avg_rt += rt_done[idx];
        }

        int exec_time = (rt[idx] > tq) ? tq : rt[idx];
        t += exec_time;
        rt[idx] -= exec_time;

        // Check for new arrivals
        for(i = 0; i < n; i++) {
            if(at[i] <= t && !mark[i]) {
                queue[rear++] = i;
                mark[i] = 1;
            }
        }

        if(rt[idx] > 0) {
            queue[rear++] = idx; // Not completed, enqueue again
        } else {
            completed++;
            ct[idx] = t;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            avg_tat += tat[idx];
            avg_wt += wt[idx];
        }

        if(front == rear) break; // Queue empty, done
    }

    // Output
    printf("\nP#\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for(i = 0; i < n; i++) {
        printf("P[%d]\t%d\t%d\t%d\t%d\t%d\t%d\n", i+1, at[i], bt[i], ct[i], tat[i], wt[i], rt_done[i]);
    }

    printf("\nAverage Waiting Time: %.2f", avg_wt/n);
    printf("\nAverage Turnaround Time: %.2f", avg_tat/n);
    printf("\nAverage Response Time: %.2f\n", avg_rt/n);

    return 0;
}
// gcc rr.c -o rr
// ./rr
