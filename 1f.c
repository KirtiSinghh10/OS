#include <stdio.h>
#include <limits.h>

struct process {
    int pid;
    int at;  // Arrival Time
    int bt;  // Burst Time
    int rt;  // Remaining Time
    int wt;  // Waiting Time
    int tat; // Turnaround Time
};

void srtf(struct process p[], int n) {
    int completed = 0;
    int t = 0;
    int min_rt = INT_MAX;
    int shortest = -1;
    int finish_time;
    int check = 0;

    while (completed < n) {
        min_rt = INT_MAX;
        shortest = -1;
        check = 0;

        for (int i = 0; i < n; i++) {
            if ((p[i].at <= t) && (p[i].rt < min_rt) && p[i].rt > 0) {
                min_rt = p[i].rt;
                shortest = i;
                check = 1;
            }
        }

        if (check == 0) {
            t++;
            continue;
        }

        p[shortest].rt--;

        if (p[shortest].rt == 0) {
            completed++;
            finish_time = t + 1;
            p[shortest].tat = finish_time - p[shortest].at;
            p[shortest].wt = p[shortest].tat - p[shortest].bt;
            if (p[shortest].wt < 0) p[shortest].wt = 0;
        }
        t++;
    }

    float total_wt = 0, total_tat = 0;
    printf("\nPID\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].wt, p[i].tat);
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }
    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time and Burst Time for P%d: ", p[i].pid);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;
    }
    srtf(p, n);
    return 0;
}
