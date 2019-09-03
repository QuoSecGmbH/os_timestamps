#ifndef FILE_TS_H
#define FILE_TS_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

int stat_succeeds(char *path);
void print_path_timestamps_s(char *path);
void print_file_timestamps_s(FILE *f);
void print_path_timestamps_ns(char *path);
void print_file_timestamps_ns(FILE *f);
struct stat* get_path_timestamps(char *path);
struct stat** get_multi_path_timestamps(int watch_num, char** watch_array);
struct stat* get_path_timestamps_lstat(char *path);
struct stat* get_file_timestamps(FILE *f);
struct stat* get_fd_timestamps(int fd);
#endif
