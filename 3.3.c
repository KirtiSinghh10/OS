#include <stdio.h>
#include <limits.h>

#define MAX 100

struct Process {
    int id;
    int at;
    int bt;
    int rt;
    int deadline;
    int period;
    int share;
    int ct, wt, tat;
};

int gantt_id[MAX];
int gantt_time[MAX];
int g = 0;

void addGantt(int id, int time) {
    gantt_id[g] = id;
    gantt_time[g] = time;
    g++;
}

void printGantt() {
    printf("\nGantt Chart:\n|");

    for (int i = 0; i < g - 1; i++) {
        if (gantt_id[i] == -1)
            printf(" IDLE |");
        else
            printf(" P%d |", gantt_id[i]);
    }

    printf("\n0");
    for (int i = 1; i < g; i++) {
        printf("   %d", gantt_time[i]);
    }
    printf("\n");
}

float cpuUtil(int busy, int total) {
    if (total == 0) return 0;
    return ((float)busy / total) * 100;
}

/* ================= PREEMPTIVE EDF ================= */
void EDF(struct Process p[], int n) {
    printf("\n===== PREEMPTIVE EDF =====\n");

    g = 0;
    int time = 0, done = 0, busy = 0;

    for (int i = 0; i < n; i++)
        p[i].rt = p[i].bt;

    while (done < n) {
        int idx = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0) {
                if (idx == -1 || p[i].deadline < p[idx].deadline)
                    idx = i;
            }
        }

        if (idx == -1) {
            addGantt(-1, time);
            time++;
            continue;
        }

        addGantt(p[idx].id, time);

        p[idx].rt--;
        busy++;
        time++;

        if (p[idx].rt == 0) {
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            done++;
        }
    }

    addGantt(-2, time);

    printGantt();
    printf("CPU Utilization: %.2f%%\n", cpuUtil(busy, time));
}

/* ================= PREEMPTIVE RMS ================= */
void RMS(struct Process p[], int n) {
    printf("\n===== PREEMPTIVE RMS =====\n");

    g = 0;
    int time = 0, done = 0, busy = 0;

    for (int i = 0; i < n; i++)
        p[i].rt = p[i].bt;

    while (done < n) {
        int idx = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0) {
                if (idx == -1 || p[i].period < p[idx].period)
                    idx = i;
            }
        }

        if (idx == -1) {
            addGantt(-1, time);
            time++;
            continue;
        }

        addGantt(p[idx].id, time);

        p[idx].rt--;
        busy++;
        time++;

        if (p[idx].rt == 0) {
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            done++;
        }
    }

    addGantt(-2, time);

    printGantt();
    printf("CPU Utilization: %.2f%%\n", cpuUtil(busy, time));
}

/* ================= PROPORTIONAL SHARE ================= */
void ProportionalShare(struct Process p[], int n) {
    printf("\n===== PROPORTIONAL SHARE =====\n");

    g = 0;
    int time = 0, done = 0, busy = 0;

    for (int i = 0; i < n; i++)
        p[i].rt = p[i].bt;

    while (done < n) {
        int executed = 0;

        for (int i = 0; i < n; i++) {
            if (p[i].rt > 0) {
                int slice = (p[i].share > 0) ? 1 : 0;

                if (slice > p[i].rt)
                    slice = p[i].rt;

                if (slice > 0) {
                    addGantt(p[i].id, time);

                    p[i].rt -= slice;
                    busy += slice;
                    time += slice;
                    executed = 1;

                    if (p[i].rt == 0) {
                        p[i].ct = time;
                        p[i].tat = p[i].ct - p[i].at;
                        p[i].wt = p[i].tat - p[i].bt;
                        done++;
                    }
                }
            }
        }

        if (!executed) {
            addGantt(-1, time);
            time++;
        }
    }

    addGantt(-2, time);

    printGantt();
    printf("CPU Utilization: %.2f%%\n", cpuUtil(busy, time));
}

/* ================= MAIN ================= */
int main() {
    int n;
    struct Process p[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;

        printf("\nProcess %d\n", i + 1);

        printf("Arrival Time: ");
        scanf("%d", &p[i].at);

        printf("Burst Time: ");
        scanf("%d", &p[i].bt);

        printf("Deadline (EDF): ");
        scanf("%d", &p[i].deadline);

        printf("Period (RMS): ");
        scanf("%d", &p[i].period);

        printf("Share: ");
        scanf("%d", &p[i].share);
    }

    EDF(p, n);
    RMS(p, n);
    ProportionalShare(p, n);

    return 0;
}
