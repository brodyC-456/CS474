#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

#define MAX_PROG_LEN 11 // Max terms in a "program"
#define MAX_PROCS 20 // Max number of processes
#define QUANTUM 40 // Time quantum, ms
#define MAX_INSTRUCTIONS 11

#define MIN(x,y) ((x)<(y)?(x):(y)) // Compute the minimum

// TODO: all the code!

struct process {
    int pid;
    enum state {ready, sleeping, exited} state;
    int time_sleep_remaining;
    int time_awake_remaining;
    int program_counter;
    int instructions[MAX_INSTRUCTIONS + 1];   
};

struct process table[MAX_PROCS];

void init_proc_table(void){
    for (int i = 0; i < MAX_PROCS; i++) {
        table[i].pid = i;
        table[i].state = ready;
        table[i].time_sleep_remaining = 0;
        table[i].time_awake_remaining = 0;
        table[i].program_counter = 0;
        memset(table[i].instructions, 0, sizeof(table[i].instructions));
    }
}

// Parses the command line by adding each instruction of each process to its instructions list
void parse_command_line(int argc, char **argv){
    for (int i = 0; i < argc - 1; i++){
        char *token;
        int j = 0;

        if ((token = strtok(argv[i + 1], ",")) != NULL) do {
            table[i].instructions[j++] = atoi(token);
        } while ((token = strtok(NULL, ",")) != NULL);
        table[i].time_awake_remaining = table[i].instructions[0];
    }  
}

// Finds the amount of time till the next process awakens, then advances all processes time_till_awake value.
int pass_time(int clock, int argc){
    int lowest_time_till_awake = 0;
    for (int i = 0; i < argc-1; i++){
        if (table[i].state == sleeping){
            if (lowest_time_till_awake == 0){
                lowest_time_till_awake = table[i].time_sleep_remaining;
            }
            else{
                lowest_time_till_awake = MIN(table[i].time_sleep_remaining, lowest_time_till_awake);
            }
        }
    }

    for (int i = 0; i < argc-1; i++){
        table[i].time_sleep_remaining -= lowest_time_till_awake;
    }
    clock += lowest_time_till_awake;
    return clock;
}

/**
 * Main.
 */
int main(int argc, char **argv)
{
    // Setting up some important variables
    int clock = 0;
    int all_exited = 0;
    struct queue *q = queue_new();
    init_proc_table();
    parse_command_line(argc, argv);
    

    // add all processes to the queue initially
    for (int i = 0; i < argc - 1; i++){
        queue_enqueue(q, table+i);
    }

    // Loop while there are still active processes
    while(all_exited != argc - 1){
        if (queue_is_empty(q)){
            clock = pass_time(clock, argc);
        }
        printf("=== Clock %i ms ===\n", clock);

        for (int i = 0; i < argc-1; i++){
            if (table[i].time_sleep_remaining <= 0 && table[i].state == sleeping){
                table[i].program_counter++;
                int cur_instruction = table[i].instructions[table[i].program_counter];
                if(cur_instruction == 0 && table[i].state != exited){
                    table[i].state = exited;
                    printf("PID %i: Exiting\n", table[i].pid);
                    all_exited++;
                }
                else{
                    table[i].state = ready;
                    table[i].time_awake_remaining = cur_instruction;
                    printf("PID %i: Waking up for %i ms\n", table[i].pid, cur_instruction);
                    queue_enqueue(q, table+i);
                }
            }
        }

        
        struct process *p = queue_dequeue(q);
        if (p == NULL){
            continue;
        }

        printf("PID %i: Running\n", p->pid);

        int runtime = MIN(p->time_awake_remaining, QUANTUM);
        p->time_awake_remaining -= runtime;

        for(int i = 0; i < argc-1; i++){
            if (table[i].state == sleeping){
                table[i].time_sleep_remaining -= runtime;
            }
        }

        if (p->time_awake_remaining > 0){
            queue_enqueue(q, p);
        }
        else{
            p->program_counter++;
            int cur_instruction = p->instructions[p->program_counter];
            if(cur_instruction == 0){
                p->state = exited;
                printf("PID %i: Exiting\n", p->pid);
                all_exited++;
            }
            else{
                p->state = sleeping;
                p->time_sleep_remaining = cur_instruction;
                printf("PID %i: Sleeping for %i ms\n", p->pid, cur_instruction);
            }
        }
        
        clock += runtime;
        printf("PID %i: Ran for %i ms\n", p->pid, runtime);
    }
    queue_free(q);
}
