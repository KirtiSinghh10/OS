#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

bool isSafe(int n, int m,
            int allocation[MAX_PROCESSES][MAX_RESOURCES],
            int need[MAX_PROCESSES][MAX_RESOURCES],
            int available[MAX_RESOURCES],
            int safeSeq[MAX_PROCESSES])
{
    bool finish[MAX_PROCESSES] = {false};
    int work[MAX_RESOURCES];

    for (int i = 0; i < m; i++)
        work[i] = available[i];

    int count = 0;

    while (count < n)
    {
        bool found = false;

        for (int i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                bool canFinish = true;

                for (int j = 0; j < m; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        canFinish = false;
                        break;
                    }
                }

                if (canFinish)
                {
                    for (int k = 0; k < m; k++)
                        work[k] += allocation[i][k];

                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found)
            return false;
    }

    return true;
}

int main()
{
    int n, m;

    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int max[MAX_PROCESSES][MAX_RESOURCES];
    int need[MAX_PROCESSES][MAX_RESOURCES];
    int available[MAX_RESOURCES];
    int safeSeq[MAX_PROCESSES];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("Enter Allocation Matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter Maximum Matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter Available Resources:\n");
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &available[i]);
    }

    // Calculate Need Matrix

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // CHECK INITIAL SAFE STATE

    if (isSafe(n, m, allocation, need, available, safeSeq))
    {
        printf("\nSystem is initially in SAFE state.\n");

        printf("Safe Sequence: ");

        for (int i = 0; i < n; i++)
        {
            printf("P%d", safeSeq[i]);
        }

        printf("\n");
    }
    else
    {
        printf("\nSystem is NOT in safe state.\n");
        return 0;
    }

    // TAKE NEW REQUEST

    int processNum;
    int request[MAX_RESOURCES];

    printf("\nEnter process number making request: ");
    scanf("%d", &processNum);

    printf("Enter request:\n");

    for (int i = 0; i < m; i++)
    {
        scanf("%d", &request[i]);
    }

    // CHECK Request <= Need

    for (int i = 0; i < m; i++)
    {
        if (request[i] > need[processNum][i])
        {
            printf("Error: Process exceeded maximum need.\n");
            return 0;
        }
    }

    // CHECK Request <= Available

    for (int i = 0; i < m; i++)
    {
        if (request[i] > available[i])
        {
            printf("Resources not available. Process must wait.\n");
            return 0;
        }
    }

    // TEMPORARY ALLOCATION

    for (int i = 0; i < m; i++)
    {
        available[i] -= request[i];
        allocation[processNum][i] += request[i];
        need[processNum][i] -= request[i];
    }

    // CHECK SAFE STATE AGAIN

    if (isSafe(n, m, allocation, need, available, safeSeq))
    {
        printf("\nRequest can be granted.\n");

        printf("New Safe Sequence: ");

        for (int i = 0; i < n; i++)
        {
            printf("P%d", safeSeq[i]);

            if (i != n - 1)
                printf(" -> ");
        }

        printf("\n");
    }
    else
    {
        // ROLLBACK

        for (int i = 0; i < m; i++)
        {
            available[i] += request[i];
            allocation[processNum][i] -= request[i];
            need[processNum][i] += request[i];
        }

        printf("\nRequest cannot be granted. Unsafe state.\n");
    }

    return 0;
}
