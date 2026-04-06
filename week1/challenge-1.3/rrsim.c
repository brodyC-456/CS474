#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

#define MAX_PROCS 10 // Max number of processes
#define QUANTUM 40 // Time quantum, ms
#define MIN(x,y) ((x)<(y)?(x):(y)) // Compute the minimum

/**
 * Process information.
 */
struct process {
    int pid;
    int time_awake_remaining;
};

/**
 * The process table.
 */
struct process table[MAX_PROCS];

/**
 * Initialize the process table.
 */
void init_proc_table(void)
{
    for (int i = 0; i < MAX_PROCS; i++) {
        table[i].pid = i;
        table[i].time_awake_remaining = 0;
    }
}

/**
 * Parse the command line.
 */
void parse_command_line(int argc, char **argv)
{
    for (int i = 0; i < argc - 1; i++){
        table[i].time_awake_remaining = atoi(argv[i+1]);
    }
}

/**
 * Main.
 */
int main(int argc, char **argv)
{
    struct queue *q = queue_new();

    init_proc_table();

    parse_command_line(argc, argv);

    // TODO
    int clock = 0;
    int exited = 0;
    int num_jobs = argc-1;

    for (int i = 0; i < num_jobs; i++){
        queue_enqueue(q, table+i);
    }

    while(exited != num_jobs){

        
        // Clock
        printf("== Clock %i ms ==\n", clock);
        struct process *p = queue_dequeue(q);
        printf("PID %i: Running\n", p->pid);

        int runtime = p->time_awake_remaining;

        // If it uses less than its full time slice, print based on time_awake_remaining
        if (p->time_awake_remaining < QUANTUM){
            clock += p->time_awake_remaining;
            p->time_awake_remaining -= p->time_awake_remaining;
        }
        // If it uses its full timeslice use quantum
        else{
            runtime = QUANTUM;
            p->time_awake_remaining -= QUANTUM;
            clock += QUANTUM;
        }

        printf("PID %i: Ran for %i ms\n", p->pid, runtime);

        if (p->time_awake_remaining > 0){
            queue_enqueue(q, p);
        }
        else{
            exited += 1;
        }
    }
    

    queue_free(q);
}
