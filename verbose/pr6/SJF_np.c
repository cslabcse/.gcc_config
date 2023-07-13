#include <stdio.h>
#include <limits.h>

struct process_struct
{
    int pid;
    int at;
    int bt;
    int ct, wt, tat;
} ps[100];

int main()
{

    int n;
    int is_completed[100] = {0}, is_first_process = 1;
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
    }

    for (int i = 0; i < n; i++)
    {
        printf("\nEnter Process %d Burst Time: ", i);
        scanf("%d", &ps[i].bt);
    }

    while (completed != n)
    {
        // find process with min. burst time in ready queue at current time
        int min_index = -1;
        int minimum = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            if (ps[i].at <= current_time && is_completed[i] == 0)
            {
                if (ps[i].bt < minimum)
                {
                    minimum = ps[i].bt;
                    min_index = i;
                }
                if (ps[i].bt == minimum)
                {
                    if (ps[i].at < ps[min_index].at)
                    {
                        minimum = ps[i].bt;
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
            current_time += ps[min_index].bt;
            ps[min_index].ct = current_time;
            ps[min_index].tat = ps[min_index].ct - ps[min_index].at;
            ps[min_index].wt = ps[min_index].tat - ps[min_index].bt;

            sum_tat += ps[min_index].tat;
            sum_wt += ps[min_index].wt;

            completed++;
            is_completed[min_index] = 1;
            current_time = ps[min_index].ct;
            is_first_process = 0;
            printf("| P%d  %d", ps[min_index].pid, current_time);
        }
    }

    // Output
    printf("\nProcess No.\tAT\tCPU Burst Time\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("%d\t\t%d\t%d\t\t%d\t%d\t%d\n", ps[i].pid, ps[i].at, ps[i].bt, ps[i].ct, ps[i].tat, ps[i].wt);

    printf("\n");

    printf("\nAverage Turn Around time= %f ", (float)sum_tat / n);
    printf("\nAverage Waiting Time= %f ", (float)sum_wt / n);
}
