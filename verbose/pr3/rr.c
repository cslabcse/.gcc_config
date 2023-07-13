#include <stdio.h>
#include <limits.h>
#include <stdlib.h> //for qsort

struct process_struct
{
    int pid;
    int at;
    int bt;
    int ct, wt, tat, start_time;
    int bt_remaining;
    int visited;
} ps[100];

int findmax(int a, int b)
{
    return a > b ? a : b;
}

int comparatorAT(const void *a, const void *b)
{
    int x = ((struct process_struct *)a)->at;
    int y = ((struct process_struct *)b)->at;
    if (x < y)
        return -1;
    else if (x >= y)
        return 1;
}

int comparatorPID(const void *a, const void *b)
{
    int x = ((struct process_struct *)a)->pid;
    int y = ((struct process_struct *)b)->pid;
    if (x < y)
        return -1;
    else if (x >= y)
        return 1;
}

void main()
{
    int n, index;
    int is_first_process = 1;
    int current_time = 0;
    int completed = 0, tq;
    printf("Enter total number of processes: ");
    scanf("%d", &n);
    int queue[100], front = -1, rear = -1;
    float sum_tat = 0, sum_wt = 0, sum_rt = 0;

    for (int i = 0; i < n; i++)
    {
        printf("\nEnter Process %d Arrival Time: ", i);
        scanf("%d", &ps[i].at);
        ps[i].pid = i;
        ps[i].visited = 0;
    }

    for (int i = 0; i < n; i++)
    {
        printf("\nEnter Process %d Burst Time: ", i);
        scanf("%d", &ps[i].bt);
        ps[i].bt_remaining = ps[i].bt;
    }

    printf("\nEnter time quanta: ");
    scanf("%d", &tq);

    // sort structure on the basis of Arrival time in increasing order
    qsort((void *)ps, n, sizeof(struct process_struct), comparatorAT);
    front = rear = 0;
    queue[rear] = 0;
    ps[0].visited = 1;

    while (completed != n)
    {
        index = queue[front];
        // q.pop();
        front++;

        if (ps[index].bt_remaining == ps[index].bt)
        {
            ps[index].start_time = findmax(current_time, ps[index].at);
            current_time = ps[index].start_time;
            is_first_process = 0;
        }

        if (ps[index].bt_remaining - tq > 0)
        {
            ps[index].bt_remaining -= tq;
            current_time += tq;
            printf("| P%d  %d", ps[index].pid, current_time);
        }

        else
        {
            current_time += ps[index].bt_remaining;
            ps[index].bt_remaining = 0;
            completed++;

            ps[index].ct = current_time;
            ps[index].tat = ps[index].ct - ps[index].at;
            ps[index].wt = ps[index].tat - ps[index].bt;
            printf("| P%d  %d", ps[index].pid, current_time);
            sum_tat += ps[index].tat;
            sum_wt += ps[index].wt;
        }
        // check which new Processes needs to be pushed to Ready Queue from Input list
        for (int i = 1; i < n; i++)
        {
            if (ps[i].bt_remaining > 0 && ps[i].at <= current_time && ps[i].visited == 0)
            {
                // q.push(i);
                queue[++rear] = i;
                ps[i].visited = 1;
            }
        }
        // check if Process on CPU needs to be pushed to Ready Queue
        if (ps[index].bt_remaining > 0)
        {
            // q.push(index);
            queue[++rear] = index;
        }

        // if queue is empty, just add one process from list, whose remaining burst time > 0
        if (front > rear)
        {
            for (int i = 1; i < n; i++)
            {
                if (ps[i].bt_remaining > 0)
                {
                    queue[rear++] = i;
                    ps[i].visited = 1;
                    break;
                }
            }
        }
    }

    qsort((void *)ps, n, sizeof(struct process_struct), comparatorPID);

    // Output
    printf("\nProcess No.\tAT\tCPU Burst Time\tStart Time\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t%d\t\t%d\t\t%d\t%d\t%d\n", i, ps[i].at, ps[i].bt, ps[i].start_time, ps[i].ct, ps[i].tat, ps[i].wt);
    }
    printf("\n");

    printf("\nAverage Turn Around time= %.2f", (float)sum_tat / n);
    printf("\nAverage Waiting Time= %.2f", (float)sum_wt / n);
}
