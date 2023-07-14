#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

struct process_struct
{
    int pid;
    int at;
    int bt;
    int ct, wt, tat, start_time;
    int bt_remaining;
    int visited;
} ps[100], temp;
int findmax(int a, int b)
{
    return a > b ? a : b;
}
void main()
{
    int n, index;
    int current_time = 0;
    int completed = 0, tq;
    printf("Enter total number of processes: ");
    scanf("%d", &n);
    int queue[100], front = -1, rear = -1;
    float sum_tat = 0, sum_wt = 0;

    for (int i = 0; i < n; i++)
    {
        printf("\nEnter Process %d AT and BT: ", i);
        scanf("%d%d", &ps[i].at, &ps[i].bt);
        ps[i].pid = i;
        ps[i].visited = 0;
        ps[i].bt_remaining = ps[i].bt;
    }
    printf("\nEnter time quanta: ");
    scanf("%d", &tq);
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (ps[j].at > ps[j + 1].at)
            {
                temp = ps[j];
                ps[j] = ps[j + 1];
                ps[j + 1] = temp;
            }
        }
    }
    front = rear = 0;
    queue[rear] = 0;
    ps[0].visited = 1;
    while (completed != n)
    {
        index = queue[front];
        front++;
        if (ps[index].bt_remaining == ps[index].bt)
        {
            current_time = findmax(current_time, ps[index].at);
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
        // selecting next to put into q
        for (int i = 1; i < n; i++)
        {
            if (ps[i].bt_remaining > 0 && ps[i].at <= current_time && ps[i].visited == 0)
            {
                queue[++rear] = i;
                ps[i].visited = 1;
            }
        }
        // if cpu process shd be put into q
        if (ps[index].bt_remaining > 0)
        {
            queue[++rear] = index;
        }
        // if q is empty
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
    printf("\nProcess No.\tAT\tCPU Burst Time\tStart Time\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t%d\t\t%d\t\t%d\t%d\t%d\n", i, ps[i].at, ps[i].bt, ps[i].start_time, ps[i].ct, ps[i].tat, ps[i].wt);
    }
    printf("\n");

    printf("\nAverage Turn Around time= %.2f", (float)sum_tat / n);
    printf("\nAverage Waiting Time= %.2f", (float)sum_wt / n);
}
