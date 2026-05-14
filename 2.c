#include <stdio.h>
#define MAX 100

struct Process
{
    int id;
    int at;   // Arrival Time
    int bt;   // Burst Time
    int ct;   // Completion Time
    int wt;   // Waiting Time
    int tat;  // Turnaround Time
    int queue; // 0 = System, 1 = User
    int done; // Completion flag
};

int main()
{
    int n;
    struct Process all[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input
    for (int i = 0; i < n; i++)
    {
        all[i].id = i + 1;

        printf("\nProcess %d\n", all[i].id);

        printf("Enter arrival time: ");
        scanf("%d", &all[i].at);

        printf("Enter burst time: ");
        scanf("%d", &all[i].bt);

        printf("Enter type (0 = System, 1 = User): ");
        scanf("%d", &all[i].queue);

        all[i].done = 0;
    }

    int completed = 0, currentTime = 0;

    // Scheduling logic (Fixed)
    while (completed < n)
    {
        int idx = -1;

        for (int i = 0; i < n; i++)
        {
            if (!all[i].done && all[i].at <= currentTime)
            {
                if (idx == -1 ||
                    all[i].queue < all[idx].queue || // System first
                    (all[i].queue == all[idx].queue && all[i].at < all[idx].at))
                {
                    idx = i;
                }
            }
        }

        // If no process is ready, move time forward
        if (idx == -1)
        {
            currentTime++;
            continue;
        }

        // Execute process
        all[idx].wt = currentTime - all[idx].at;
        all[idx].ct = currentTime + all[idx].bt;
        all[idx].tat = all[idx].ct - all[idx].at;

        currentTime = all[idx].ct;
        all[idx].done = 1;
        completed++;
    }

    // Output
    printf("\nID\tType\tAT\tBT\tCT\tWT\tTAT\n");

    float totalWT = 0, totalTAT = 0;

    for (int i = 0; i < n; i++)
    {
        printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\n",
               all[i].id,
               all[i].queue == 0 ? "System" : "User",
               all[i].at,
               all[i].bt,
               all[i].ct,
               all[i].wt,
               all[i].tat);

        totalWT += all[i].wt;
        totalTAT += all[i].tat;
    }

    printf("\nAverage Waiting Time: %.2f", totalWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);

    return 0;
}
