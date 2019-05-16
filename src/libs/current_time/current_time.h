#ifndef CURRENT_TIME_H
#define CURRENT_TIME_H

// #pragma once 

// #include <sys/time.h>
#include <time.h>
// int clock_gettime(clockid_t clock_id, struct timespec *tp);

// #include <linux/time.h>
// #include <bits/types/clockid_t.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"
#include "misc.h"

// int main();
void print_current_time_s();
time_t* current_time_s();
int check_general_clock_res(FILE* csv_file, FILE* outpuy_file, FILE* error_file);
int check_general_clock_increments(FILE* csv_file, FILE* output_file, FILE* error_file);
void print_current_time_ns();
struct timespec* current_time_ns();
struct timespec* current_time_ns_coarse();
#endif
