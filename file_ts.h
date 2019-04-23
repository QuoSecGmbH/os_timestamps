#ifndef FILE_TS_H
#define FILE_TS_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

int main();
void print_path_timestamps_s(char *path);
void print_path_timestamps_ns(char *path);
struct stat* get_path_timestamps(char *path);
#endif
