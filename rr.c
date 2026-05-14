#include <stdio.h>

struct process
{
    int at;
    int bt;
    int rt;
    int wt;
    int tat;
    int ct;
};

#define max 100

void RoundRobin(struct process p[], int n, int tq)
{
    int t = 0, completed = 0;
    int queue[max], front = 0, rear = 0, visited[max] = {0};

    for (int i = 0; i < n; i++)
    {
        p[i].rt = p[i].bt;
    }


    for (int i = 0; i < n; i++)
    {
        if (p[i].at == 0)
        {
            queue[rear++] = i;
            visited[i] = 1;
        }
    }

    if (rear == 0)
    {
        int min_at = p[0].at, idx = 0;
        for (int i = 1; i < n; i++)
        {
            if (p[i].at < min_at)
            {
                min_at = p[i].at;
                idx = i;
            }
        }

        t = p[idx].at;
        queue[rear++] = idx;
        visited[idx] = 1;
    }

    while (completed < n)
    {
        int idx = queue[front++];

        if (p[idx].rt > 0)
        {
            if (p[idx].rt > tq)
            {
                t += tq;
                p[idx].rt -= tq;
            }
            else
            {
                t += p[idx].rt;
                p[idx].ct = t;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                p[idx].rt = 0;
                completed++;
            }


            for (int i = 0; i < n; i++)
            {
                if (i != idx && !visited[i] && p[i].at <= t)
                {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }

            if (p[idx].rt > 0)
            {
                queue[rear++] = idx;
            }
        }
        if (front == rear && completed < n)
        {
            for (int i = 0; i < n; i++)
            {
                if (!visited[i])
                {
                    t = (t < p[i].at) ? p[i].at : t;
                    queue[rear++] = i;
                    visited[i] = 1;
                    break;
                }
            }
        }
    }

    printf("\nID\tAT\tBT\tCT\tWT\tTAT\n");
    float total_wt = 0, total_tat = 0;

    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               i, p[i].at, p[i].bt, p[i].ct, p[i].wt, p[i].tat);

        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
}

int main()
{
    int n, tq;
    struct process p[max];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("Enter arrival time for process %d: ", i);
        scanf("%d", &p[i].at);

        printf("Enter burst time for process %d: ", i);
        scanf("%d", &p[i].bt);
    }

    printf("Enter time quantum: ");
    scanf("%d", &tq);

    RoundRobin(p, n, tq);

    return 0;
}
