/*
============================================================================
Name : 5.c
Author : Archis Kulkarni
Description : Write a program to print the system limitation of  
       a. maximum length of the arguments to the exec family of functions.  
       b. maximum number of simultaneous process per user id.  
       c. number of clock ticks (jiffy) per second.  
       d. maximum number of open files 
       e. size of a page 
       f. total number of pages in the physical memory 
       g. number of currently available pages in the physical memory.  
Date: 17-09-2024
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/resource.h>

int main() {
    struct rlimit limit;

    // maximum length of the arguments to the exec family of functions
    long max_arg_length = sysconf(_SC_ARG_MAX);
    if (max_arg_length == -1) {
        perror("pathconf");
        exit(EXIT_FAILURE);
    }
    

    //maximum number of simultaneous processes per user id
    if (getrlimit(RLIMIT_NPROC, &limit) == -1) {
        perror("getrlimit");
        exit(EXIT_FAILURE);
    }
    
    // number of clock ticks per second
    long clock_ticks = sysconf(_SC_CLK_TCK);
    if (clock_ticks == -1) {
        perror("sysconf");
        exit(EXIT_FAILURE);
    }

    //maximum number of open files
    if (getrlimit(RLIMIT_NOFILE, &limit) == -1) {
        perror("getrlimit");
        exit(EXIT_FAILURE);
    }
    // Size of a page
    long page_size = sysconf(_SC_PAGE_SIZE);
    if (page_size == -1) {
        perror("sysconf");
        exit(EXIT_FAILURE);
    }
   

    // total number of pages in the physical memory
    long total_pages = sysconf(_SC_PHYS_PAGES);
    if (total_pages == -1) {
        perror("sysconf");
        exit(EXIT_FAILURE);
    }
    //number of currently available pages in the physical memory
    long available_pages = sysconf(_SC_AVPHYS_PAGES);
    if (available_pages == -1) {
        perror("sysconf");
        exit(EXIT_FAILURE);
    }

	// printing all the values
	printf("Maximum length of arguments to exec family: %ld bytes\n", max_arg_length);
	printf("Maximum number of simultaneous processes per user ID: %lu\n", limit.rlim_cur);
	printf("Number of clock ticks per second: %ld\n", clock_ticks);
    printf("Maximum number of open files: %lu\n", limit.rlim_cur);
	printf("Size of a page: %ld bytes\n", page_size);
    printf("Total number of pages in physical memory: %ld\n", total_pages);
    printf("Number of currently available pages in physical memory: %ld\n", available_pages);

}


/* ./a.out
Maximum length of arguments to exec family: 2097152 bytes
Maximum number of simultaneous processes per user ID: 1024
Number of clock ticks per second: 100
Maximum number of open files: 1024
Size of a page: 4096 bytes
Total number of pages in physical memory: 1993815
Number of currently available pages in physical memory: 1784606
*/