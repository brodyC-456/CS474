#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MEM_SIZE 16384  // MUST equal PAGE_SIZE * PAGE_COUNT
#define PAGE_SIZE 256  // MUST equal 2^PAGE_SHIFT
#define PAGE_COUNT 64
#define PAGE_SHIFT 8  // Shift page number this much

#define PTP_OFFSET 64 // How far offset in page 0 is the page table pointer table

// Simulated RAM
unsigned char mem[MEM_SIZE];

//
// Convert a page,offset into an address
//
int get_address(int page, int offset)
{
    return (page << PAGE_SHIFT) | offset;
}

//
// Initialize RAM
//
void initialize_mem(void)
{
    memset(mem, 0, MEM_SIZE);

    int zpfree_addr = get_address(0, 0);
    mem[zpfree_addr] = 1;  // Mark zero page as allocated
}

//
// Get the page table page for a given process
//
unsigned char get_page_table(int proc_num)
{
    int ptp_addr = get_address(0, PTP_OFFSET + proc_num);
    return mem[ptp_addr];
}

// Locates the first free page then allocates it as in use
int find_free_page(){
    for(int i = 0; i < PAGE_COUNT; i++){
        // get the address for a specific page number in the free table
        int addr = get_address(0, i);
        // If its not set, set it and return the location!
        if (mem[addr] == 0){
            mem[addr] = 1;
            return i;
        }
    }
    // If we dont have enough memory return an error code
    return -1;
}

int allocate_data_pages(int proc_num, int page_count){
    // For every page we need to allocate, find a free page, allocate it, then store the page in the processes page table
    for(int i = 0; i < page_count; i++){
        int page_loc = find_free_page();
        // If memory allocation fails, return a failure flag
        if(page_loc == -1){
            return -1;
        }

        int entry_addr = get_address(get_page_table(proc_num), i);
        mem[entry_addr] = page_loc;
    }
    // Return 1 upon success
    return 1;
}

//
// Allocate pages for a new process
//
// This includes the new process page table and page_count data pages.
//
void new_process(int proc_num, int page_count)
{
    // Allocate the processes page table
    int page_table_loc = find_free_page();
    if (page_table_loc == -1){
        printf("OOM: proc %d: page table\n", proc_num);
        return;
    }
    // Store its page number in the ptp table in page 0
    int ptp_addr = get_address(0, PTP_OFFSET + proc_num);
    mem[ptp_addr] = page_table_loc;

    // Allocate all the data pages
    if(allocate_data_pages(proc_num, page_count) == -1){
        printf("OOM: proc %d: data page\n", proc_num);
        return;
    }   
}

//
// Print the free page map
//
// Don't modify this
//
void print_page_free_map(void)
{
    printf("--- PAGE FREE MAP ---\n");

    for (int i = 0; i < 64; i++) {
        int addr = get_address(0, i);

        printf("%c", mem[addr] == 0? '.': '#');

        if ((i + 1) % 16 == 0)
            putchar('\n');
    }
}

//
// Print the address map from virtual pages to physical
//
// Don't modify this
//
void print_page_table(int proc_num)
{
    printf("--- PROCESS %d PAGE TABLE ---\n", proc_num);

    // Get the page table for this process
    int page_table = get_page_table(proc_num);

    // Loop through, printing out used pointers
    for (int i = 0; i < PAGE_COUNT; i++) {
        int addr = get_address(page_table, i);

        int page = mem[addr];

        if (page != 0) {
            printf("%02x -> %02x\n", i, page);
        }
    }
}

//
// Main -- process command line
//
int main(int argc, char *argv[])
{
    assert(PAGE_COUNT * PAGE_SIZE == MEM_SIZE);

    if (argc == 1) {
        fprintf(stderr, "usage: ptsim commands\n");
        return 1;
    }
    
    initialize_mem();

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "pfm") == 0) {
            print_page_free_map();
        }
        else if (strcmp(argv[i], "ppt") == 0) {
            int proc_num = atoi(argv[++i]);
            print_page_table(proc_num);
        }
        // Command line parsing for np
        else if (strcmp(argv[i], "np") == 0) {
            int proc_num = atoi(argv[++i]);
            int num_pages = atoi(argv[++i]);
            new_process(proc_num, num_pages);
        }
    }
}
