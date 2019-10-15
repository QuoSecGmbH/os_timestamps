#ifndef FILE_TS_C
#define FILE_TS_C

#include "file_ts.h"

int stat_succeeds(char *path) {
    struct stat* attr = (struct stat*) calloc(sizeof(struct stat), 1);
    int res = stat(path, attr);
    free(attr);
    if (res != 0){
        // stat failed
        return 1;
    }
    
    // stat succeeded
    return 0;
}

void print_path_timestamps_s(char *path) {
    struct stat* attr = get_path_timestamps(path);
    
    if (attr == NULL){
        printf("ERROR: print_path_timestamps_s - attr is NULL\n");
        return;
    }
    
    printf("M: %s", ctime(&(attr->st_mtime)));
    printf("A: %s", ctime(&(attr->st_atime)));
    printf("C: %s", ctime(&(attr->st_ctime)));
}

void print_file_timestamps_s(FILE *f) {
    struct stat* attr = get_file_timestamps(f);
    
    if (attr == NULL){
        printf("ERROR: print_path_timestamps_s - attr is NULL\n");
        return;
    }
    
    printf("M: %s", ctime(&(attr->st_mtime)));
    printf("A: %s", ctime(&(attr->st_atime)));
    printf("C: %s", ctime(&(attr->st_ctime)));
}

void print_path_timestamps_ns(char *path) {
    struct stat* attr = get_path_timestamps(path);
    
    if (attr == NULL){
        printf("ERROR: print_path_timestamps_s - attr is NULL\n");
        return;
    }
    
    time_t s = attr->st_mtim.tv_sec;
    long ns = attr->st_mtim.tv_nsec;
    char* buf = ctime(&s);
    buf[strlen(buf)-1] = 0;
    printf("M: %s - ns: %9ld\n", buf, ns);
    
    s = attr->st_atim.tv_sec;
    ns = attr->st_atim.tv_nsec;
    buf = ctime(&s);
    buf[strlen(buf)-1] = 0;
    printf("A: %s - ns: %9ld\n", buf, ns);
    
    s = attr->st_ctim.tv_sec;
    ns = attr->st_ctim.tv_nsec;
    buf = ctime(&s);
    buf[strlen(buf)-1] = 0;
    printf("C: %s - ns: %9ld\n", buf, ns);
}

void print_path_timestamps_lstat_ns(char *path) {
    struct stat* attr = get_path_timestamps_lstat(path);
    
    if (attr == NULL){
        printf("ERROR: print_path_timestamps_s - attr is NULL\n");
        return;
    }
    
    time_t s = attr->st_mtim.tv_sec;
    long ns = attr->st_mtim.tv_nsec;
    char* buf = ctime(&s);
    buf[strlen(buf)-1] = 0;
    printf("M: %s - ns: %9ld\n", buf, ns);
    
    s = attr->st_atim.tv_sec;
    ns = attr->st_atim.tv_nsec;
    buf = ctime(&s);
    buf[strlen(buf)-1] = 0;
    printf("A: %s - ns: %9ld\n", buf, ns);
    
    s = attr->st_ctim.tv_sec;
    ns = attr->st_ctim.tv_nsec;
    buf = ctime(&s);
    buf[strlen(buf)-1] = 0;
    printf("C: %s - ns: %9ld\n", buf, ns);
}

void print_file_timestamps_ns(FILE *f) {
    struct stat* attr = get_file_timestamps(f);
    
    if (attr == NULL){
        printf("ERROR: print_path_timestamps_s - attr is NULL\n");
        return;
    }
    
    time_t s = attr->st_mtim.tv_sec;
    long ns = attr->st_mtim.tv_nsec;
    char* buf = ctime(&s);
    buf[strlen(buf)-1] = 0;
    printf("M: %s - ns: %9ld\n", buf, ns);
    
    s = attr->st_atim.tv_sec;
    ns = attr->st_atim.tv_nsec;
    buf = ctime(&s);
    buf[strlen(buf)-1] = 0;
    printf("A: %s - ns: %9ld\n", buf, ns);
    
    s = attr->st_ctim.tv_sec;
    ns = attr->st_ctim.tv_nsec;
    buf = ctime(&s);
    buf[strlen(buf)-1] = 0;
    printf("C: %s - ns: %9ld\n", buf, ns);
}

struct stat** get_multi_path_timestamps(int watch_num, char** watch_array){
    struct stat** multi_stat = calloc(sizeof(struct stat*), watch_num);
    
    int i;
    for (i=0; i<watch_num; i++){
        multi_stat[i] = get_path_timestamps_lstat(watch_array[i]);
    }
    
    return multi_stat;
}

struct stat* get_path_timestamps(char *path) {
    struct stat* attr = (struct stat*) calloc(sizeof(struct stat), 1);
    int res = stat(path, attr);
    if (res != 0){
        return NULL;
    }
    
    return attr;
}

struct stat* get_fd_timestamps(int fd) {
    struct stat* attr = (struct stat*) calloc(sizeof(struct stat), 1);
    int res = fstat(fd, attr);
    if (res != 0){
        return NULL;
    }
    
    return attr;
}

struct stat* get_file_timestamps(FILE *f) {
    struct stat* attr = (struct stat*) calloc(sizeof(struct stat), 1);
    int res = fstat(fileno(f), attr);
    if (res != 0){
        return NULL;
    }
    
    return attr;
}

struct stat* get_path_timestamps_lstat(char *path) {
    struct stat* attr = (struct stat*) calloc(sizeof(struct stat), 1);
    int res = lstat(path, attr);
    if (res != 0){
        return NULL;
    }
    
    return attr;
}

#endif
