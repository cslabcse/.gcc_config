#include <stdio.h>
#include <limits.h>

struct process_struct
{
    int pid;
    int at;
    int bt;
    int ct, wt, tat, start_time, bt_remaining, is_completed;
} ps[100];

void main()
{
    int n;
    int is_first_process = 1;
    int current_time = 0;
    int completed = 0;
    printf("Enter total number of processes: ");
    scanf("%d", &n);
    int sum_tat = 0, sum_wt = 0, sum_rt = 0;

    for (int i = 0; i < n; i++)
    {
        printf("\nEnter Process %d Arrival Time: ", i);
        scanf("%d", &ps[i].at);
        ps[i].pid = i;
        ps[i].is_completed = 0;
    }

    for (int i = 0; i < n; i++)
    {
        printf("\nEnter Process %d Burst Time: ", i);
        scanf("%d", &ps[i].bt);
        ps[i].bt_remaining = ps[i].bt;
    }

    while (completed != n)
    {
        int min_index = -1;
        int min = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            if (ps[i].at <= current_time && ps[i].is_completed == 0)
            {
                if (ps[i].bt_remaining < min)
                {
                    min = ps[i].bt_remaining;
                    min_index = i;
                }
                if (ps[i].bt_remaining == min)
                {
                    if (ps[i].at < ps[min_index].at)
                    {
                        min = ps[i].bt_remaining;
                        min_index = i;
                    }
                }
            }
        }
        if (min_index == -1)
        {
            current_time++;
        }
        else
        {
            if (ps[min_index].bt_remaining == ps[min_index].bt)
            {
                ps[min_index].start_time = current_time;
                is_first_process = 0;
            }
            ps[min_index].bt_remaining -= 1;
            current_time++;
            printf("| P%d  %d", ps[min_index].pid, current_time);

            if (ps[min_index].bt_remaining == 0)
            {
                ps[min_index].ct = current_time;
                ps[min_index].tat = ps[min_index].ct - ps[min_index].at;
                ps[min_index].wt = ps[min_index].tat - ps[min_index].bt;

                sum_tat += ps[min_index].tat;
                sum_wt += ps[min_index].wt;
                completed++;
                ps[min_index].is_completed = 1;
                current_time = ps[min_index].ct;
            }
        }
    }
    printf("\nProcess No.\tAT\tCPU Burst Time\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("%d\t\t%d\t%d\t\t%d\t%d\t%d\n", ps[i].pid, ps[i].at, ps[i].bt, ps[i].ct, ps[i].tat, ps[i].wt);

    printf("\n");

    printf("\nAverage Turn Around time= %f ", (float)sum_tat / n);
    printf("\nAverage Waiting Time= %f ", (float)sum_wt / n);
}
