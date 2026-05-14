#include <stdio.h>
struct process{
    int at;
    int wt;
    int bt;
    int tat;
    int ct;
};
#define max 10

void sort(struct process p[], int n ){
    for (int i=0; i<n-1; i++){
        for (int j=0; j<n-1-i; j++){
            if (p[j].at>p[j+1].at){
                struct process temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
}

void fcfs(struct process p[], int n){
    int t=0;
    for (int i=0; i<n; i++){
        if (p[i].at>t){
            t=p[i].at;
        }
        p[i].wt=t-p[i].at;
        p[i].ct=t+p[i].bt; // Calculate completion time
        p[i].tat=p[i].ct-p[i].at; // Calculate turn around time
        t=p[i].ct; // Update current time to completion time of current process
    }
    for (int i=0; i<n; i++){
        printf("\n PID: %d", i+1);
        printf("\n Arrival Time: %d", p[i].at);
        printf("\n Wait time: %d", p[i].wt);
        printf("\n Burst time: %d", p[i].bt);
        printf("\n Turn around time: %d", p[i].tat);
        printf("\n Completion time: %d", p[i].ct);
    }
    double atat=0.0;
    double awt=0.0;
    for (int i=0; i<n; i++){
        awt=awt+p[i].wt;
        atat=atat+p[i].tat;
    }
    atat=atat/n;
    printf("\nAvg turn around time: %.2f", atat); // Added newline
    awt=awt/n;
    printf("\nAvg wait time:%.2f", awt); // Added newline
}

int main(){
    int n;
    struct process p[max];
    printf("Enter number of processes:");
    scanf("%d", &n);
    for (int i=0; i<n; i++){
        printf("Enter arrival time:");
        scanf("%d", &p[i].at);
        printf("Enter burst time:");
        scanf("%d", &p[i].bt);
    }
    sort (p,n);
    fcfs( p, n);
    return 0;
}
