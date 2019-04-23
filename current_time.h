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

int main();
void print_current_time_seconds();
time_t* current_time_seconds();
void check_clock_res();
void print_current_time_ns();
struct timespec* current_time_ns();
#endif
