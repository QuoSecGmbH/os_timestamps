#ifndef FILE_TS_H
#define FILE_TS_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#ifdef __linux__
#include <sys/syscall.h>
#include <linux/stat.h>
#endif

#if defined(__APPLE__) 
#define st_atim st_atimespec
#define st_ctim st_ctimespec
#define st_mtim st_mtimespec
#endif

typedef struct stat_macb{
    struct timespec st_atim;  /* Time of last access */
    struct timespec st_mtim;  /* Time of last modification */
    struct timespec st_ctim;  /* Time of last status change */
    struct timespec st_btim;
    ino_t st_ino;
} stat_macb;

struct stat_macb* stat_macb_from_stat_add_b(struct stat* attr, char* path, int follow);
struct stat_macb* stat_macb_from_stat_no_b(struct stat* attr);

int stat_succeeds(char *path);
void print_path_timestamps_s(char *path, char inode);
void print_file_timestamps_s(FILE *f, char inode);
void print_path_timestamps_ns(char *path, char inode);
void print_path_timestamps_csv_ns(char *path, char print_inode, char print_path);
void print_path_timestamps_lstat_ns(char *path, char inode);
void print_file_timestamps_ns(FILE *f, char inode);
struct stat_macb* get_path_timestamps(char *path);
struct stat_macb** get_multi_path_timestamps(int watch_num, char** watch_array);
struct stat_macb* get_path_timestamps_lstat(char *path);
struct stat_macb* get_file_timestamps(FILE *f);
struct stat_macb* get_fd_timestamps(int fd);


#ifdef __linux__
struct statx* get_path_timestamps_statx(char *path, int follow);
void print_path_timestamps_statx_ns(char *path, int follow, char inode);
void print_path_timestamps_statx_int_ns(char *path, int follow, char inode);
#endif

#endif
