#define max 10
#include <stdio.h>
struct process {
int at; // Arrival Time
int bt; // Burst Time
int wt; // Waiting Time
int tat; // Turnaround Time
int ct; // Completion Time
int done; // Flag to indicate if process is completed
};
// Function to implement SJF non-preemptive scheduling
void SJF(struct process p[], int n)
{
int completed = 0;
int t = 0; // Current time
float total_wt = 0, total_tat = 0;
while (completed < n)
{
int idx = -1; // Use -1 to indicate no process found
int min_bt = 9999;
// Find the process with the minimum burst time among the arrived processes
for (int i = 0; i < n; i++)
{
if (p[i].at <= t && p[i].done == 0)
{
if (p[i].bt < min_bt)
{
min_bt = p[i].bt;
idx = i;
}

// If burst times are equal, choose the one with earlier arrival time
else if (p[i].bt == min_bt)
{
if (p[i].at < p[idx].at)
{
idx = i;
}
}
} //end if
} // end for
// If a process is found, schedule it
if (idx != -1)
{
p[idx].wt = t - p[idx].at;
p[idx].ct = t + p[idx].bt;
p[idx].tat = p[idx].ct - p[idx].at;
total_wt += p[idx].wt;
total_tat += p[idx].tat;
p[idx].done = 1;
completed++;
t = p[idx].ct; // Move time to the completion time of the current process
}
else {
t++; // If no process has arrived yet, increment time (CPU Idle)
}
} // end while
printf("\nID\tAT\tBT\tCT\tWT\tTAT\n");
for (int i = 0; i < n; i++)
{
printf("%d\t%d\t%d\t%d\t%d\t%d\n", i, p[i].at, p[i].bt, p[i].ct,
p[i].wt, p[i].tat);
}
printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
printf("Average Turnaround Time: %.2f\n", total_tat / n);
}

int main()
{
int n;
struct process p[max];
printf("Enter number of processes: ");
scanf("%d", &n);
for (int i = 0; i < n; i++)
{
printf("Enter arrival time for process %d: ", i);
scanf("%d", &p[i].at);
printf("Enter burst time for process %d: ", i);
scanf("%d", &p[i].bt);
p[i].done = 0; // Initialize all as not done
}
SJF(p, n);
return 0;
}
