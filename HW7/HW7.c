#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
    bool completed;
} Process;

void print_gantt_chart(Process schedule[], int count) {
    printf("Gantt Chart: ");
    for (int i = 0; i < count; i++) {
        printf("| P%d ", schedule[i].pid);
    }
    printf("|\n");
}

void print_table_and_averages(Process proc[], int n) {
    printf("PID\tAT\tBT\tWT\tTAT\tRT\n");
    float total_wt = 0, total_tat = 0, total_rt = 0;

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               proc[i].pid,
               proc[i].arrival_time,
               proc[i].burst_time,
               proc[i].waiting_time,
               proc[i].turnaround_time,
               proc[i].response_time);

        total_wt += proc[i].waiting_time;
        total_tat += proc[i].turnaround_time;
        total_rt += proc[i].response_time;
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Response Time: %.2f\n\n", total_rt / n);
}

void fcfs_schedule(Process input_proc[], int n) {
    Process *proc = (Process *)malloc(n * sizeof(Process));
    for (int i = 0; i < n; i++) {
        proc[i] = input_proc[i];
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (proc[j].arrival_time > proc[j + 1].arrival_time ||
               (proc[j].arrival_time == proc[j + 1].arrival_time && proc[j].pid > proc[j + 1].pid)) {
                Process temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }

    int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < proc[i].arrival_time) {
            current_time = proc[i].arrival_time;
        }

        proc[i].response_time = current_time - proc[i].arrival_time;
        proc[i].waiting_time = proc[i].response_time;
        proc[i].completion_time = current_time + proc[i].burst_time;
        proc[i].turnaround_time = proc[i].completion_time - proc[i].arrival_time;

        current_time = proc[i].completion_time;
    }

    printf("FCFS \n");
    print_gantt_chart(proc, n);
    print_table_and_averages(proc, n);

    free(proc);
}

void sjf_schedule(Process input_proc[], int n) {
    Process *proc = (Process *)malloc(n * sizeof(Process));
    Process *schedule = (Process *)malloc(n * sizeof(Process));

    for (int i = 0; i < n; i++) {
        proc[i] = input_proc[i];
        proc[i].completed = false;
    }

    int current_time = 0;
    int completed_count = 0;

    while (completed_count < n) {
        int idx = -1;
        int min_burst = 1e9;

        for (int i = 0; i < n; i++) {
            if (!proc[i].completed && proc[i].arrival_time <= current_time) {
                if (proc[i].burst_time < min_burst) {
                    min_burst = proc[i].burst_time;
                    idx = i;
                } else if (proc[i].burst_time == min_burst) {
                    if (proc[i].arrival_time < proc[idx].arrival_time ||
                       (proc[i].arrival_time == proc[idx].arrival_time && proc[i].pid < proc[idx].pid)) {
                        idx = i;
                    }
                }
            }
        }

        if (idx == -1) {
            int min_arrival = 1e9;
            for (int i = 0; i < n; i++) {
                if (!proc[i].completed && proc[i].arrival_time < min_arrival) {
                    min_arrival = proc[i].arrival_time;
                }
            }
            current_time = min_arrival;
            continue;
        }

        proc[idx].response_time = current_time - proc[idx].arrival_time;
        proc[idx].waiting_time = proc[idx].response_time;
        proc[idx].completion_time = current_time + proc[idx].burst_time;
        proc[idx].turnaround_time = proc[idx].completion_time - proc[idx].arrival_time;
        proc[idx].completed = true;

        schedule[completed_count] = proc[idx];
        current_time = proc[idx].completion_time;
        completed_count++;
    }

    printf("SJF\n");
    print_gantt_chart(schedule, n);
    print_table_and_averages(schedule, n);

    free(proc);
    free(schedule);
}

int main(void) {
    int n;
    printf("Enter the number of processes: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 1;
    }

    Process *proc = (Process *)malloc(n * sizeof(Process));
    if (proc == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter the arrival time and burst time for process %d: ", i + 1);
        if (scanf("%d %d", &proc[i].arrival_time, &proc[i].burst_time) != 2) {
            free(proc);
            return 1;
        }
        proc[i].completed = false;
    }

    printf("\n");
    fcfs_schedule(proc, n);
    sjf_schedule(proc, n);

    free(proc);
    return 0;
}