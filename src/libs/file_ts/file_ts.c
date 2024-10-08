#ifndef FILE_TS_C
#define FILE_TS_C

#include "file_ts.h"

struct stat_macb* stat_macb_from_stat_add_b(struct stat* attr, char* path, int follow){
    struct stat_macb* attr_macb = (struct stat_macb*) calloc(sizeof(struct stat_macb), 1);
    
    memcpy((struct timespec*) &(attr_macb->st_mtim), &(attr->st_mtim), sizeof(struct timespec));
    memcpy((struct timespec*) &(attr_macb->st_atim), &(attr->st_atim), sizeof(struct timespec));
    memcpy((struct timespec*) &(attr_macb->st_ctim), &(attr->st_ctim), sizeof(struct timespec));
      
    int btim_set = 0;
#ifdef __linux__
    struct statx* attr_statx = get_path_timestamps_statx(path, follow);
    if (attr_statx != NULL){
        struct timespec* ts = (struct timespec*) calloc(sizeof(struct timespec), 1);
        ts->tv_nsec = attr_statx->stx_btime.tv_nsec;
        ts->tv_sec = attr_statx->stx_btime.tv_sec;
        memcpy((struct timespec*) &(attr_macb->st_btim), ts, sizeof(struct timespec));
        btim_set = 1;
    }
#elif __FreeBSD__
    memcpy((struct timespec*) &(attr_macb->st_btim), &(attr->st_birthtim), sizeof(struct timespec));
    btim_set = 1;
#elif __OpenBSD__
    memcpy((struct timespec*) &(attr_macb->st_btim), &(attr->__st_birthtim), sizeof(struct timespec));
    btim_set = 1;
#elif __APPLE__
    memcpy((struct timespec*) &(attr_macb->st_btim), &(attr->st_birthtimespec), sizeof(struct timespec));
    btim_set = 1;
#endif

    if (btim_set == 0){
        struct timespec* ts = (struct timespec*) calloc(sizeof(struct timespec), 1);
        ts->tv_nsec = 0;
        ts->tv_sec = 0;
    	memcpy((struct timespec*) &(attr_macb->st_btim), ts, sizeof(struct timespec));
    }
    
    attr_macb->st_ino = attr->st_ino;

    return attr_macb;
}

struct stat_macb* stat_macb_from_stat_no_b(struct stat* attr){
    struct stat_macb* attr_macb = (struct stat_macb*) calloc(sizeof(struct stat_macb), 1);
    
    memcpy((struct timespec*) &(attr_macb->st_mtim), &(attr->st_mtim), sizeof(struct timespec));
    memcpy((struct timespec*) &(attr_macb->st_atim), &(attr->st_atim), sizeof(struct timespec));
    memcpy((struct timespec*) &(attr_macb->st_ctim), &(attr->st_ctim), sizeof(struct timespec));

    struct timespec* ts = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts->tv_nsec = 0;
    ts->tv_sec = 0;
    memcpy((struct timespec*) &(attr_macb->st_btim), ts, sizeof(struct timespec));

    attr_macb->st_ino = attr->st_ino;

    return attr_macb;
}

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

void print_path_timestamps_s(char *path, char inode) {
    struct stat_macb* attr = get_path_timestamps(path);
    
    if (attr == NULL){
        printf("ERROR: print_path_timestamps_s - attr is NULL\n");
        return;
    }
    
    printf("M: %s", ctime(&(attr->st_mtim)));
    printf("A: %s", ctime(&(attr->st_atim)));
    printf("C: %s", ctime(&(attr->st_ctim)));
    printf("B: %s", ctime(&(attr->st_btim)));
}

void print_file_timestamps_s(FILE *f, char inode) {
    struct stat_macb* attr = get_file_timestamps(f);
    
    if (attr == NULL){
        printf("ERROR: print_file_timestamps_s - attr is NULL\n");
        return;
    }
    
    printf("M: %s", ctime(&(attr->st_mtim)));
    printf("A: %s", ctime(&(attr->st_atim)));
    printf("C: %s", ctime(&(attr->st_ctim)));
    printf("B: %s", ctime(&(attr->st_btim)));
}

void print_path_timestamps_ns(char *path, char inode) {
    struct stat_macb* attr = get_path_timestamps(path);
    
    if (attr == NULL){
        printf("ERROR: print_path_timestamps_ns - attr is NULL\n");
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
    
    s = attr->st_btim.tv_sec;
    ns = attr->st_btim.tv_nsec;
    buf = ctime(&s);
    buf[strlen(buf)-1] = 0;
    printf("B: %s - ns: %9ld\n", buf, ns);

    if (inode == 1) printf("I: %lu\n", attr->st_ino);
}

void print_path_timestamps_csv_ns(char *path, char print_inode, char print_path) {
    struct stat_macb* attr = get_path_timestamps(path);
    
    if (attr == NULL){
        printf("ERROR: print_path_timestamps_ns - attr is NULL\n");
        return;
    }
    
    time_t s_M = attr->st_mtim.tv_sec;
    long ns_M = attr->st_mtim.tv_nsec;
    
    time_t s_A = attr->st_atim.tv_sec;
    long ns_A = attr->st_atim.tv_nsec;
    
    time_t s_C = attr->st_ctim.tv_sec;
    long ns_c = attr->st_ctim.tv_nsec;
    
    time_t s_B = attr->st_btim.tv_sec;
    long ns_B = attr->st_btim.tv_nsec;

    if (print_path == 1){
        if (print_inode == 0) printf("%s,%d.%09ld,%d.%09ld,%d.%09ld,%d.%09ld\n", path, s_M, ns_M, s_A, ns_A, s_C, ns_c, s_B, ns_B);
        else printf("%s,%d.%09ld,%d.%09ld,%d.%09ld,%d.%09ld,%lu\n", path, s_M, ns_M, s_A, ns_A, s_C, ns_c, s_B, ns_B, attr->st_ino);

    }
    else {
        if (print_inode == 0) printf("%d.%09ld,%d.%09ld,%d.%09ld,%d.%09ld\n",s_M, ns_M, s_A, ns_A, s_C, ns_c, s_B, ns_B);
        else printf("%d.%09ld,%d.%09ld,%d.%09ld,%d.%09ld,%lu\n", s_M, ns_M, s_A, ns_A, s_C, ns_c, s_B, ns_B, attr->st_ino);
    }

}

void print_path_timestamps_lstat_ns(char *path, char inode) {
    struct stat_macb* attr = get_path_timestamps_lstat(path);
    
    if (attr == NULL){
        printf("ERROR: print_path_timestamps_lstat_ns - attr is NULL\n");
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
    
    s = attr->st_btim.tv_sec;
    ns = attr->st_btim.tv_nsec;
    buf = ctime(&s);
    buf[strlen(buf)-1] = 0;
    printf("B: %s - ns: %9ld\n", buf, ns);

    if (inode == 1) printf("I: %lu\n", attr->st_ino);
}

void print_file_timestamps_ns(FILE *f, char inode) {
    struct stat_macb* attr = get_file_timestamps(f);
    
    if (attr == NULL){
        printf("ERROR: print_file_timestamps_ns - attr is NULL\n");
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
    
    s = attr->st_btim.tv_sec;
    ns = attr->st_btim.tv_nsec;
    buf = ctime(&s);
    buf[strlen(buf)-1] = 0;
    printf("B: %s - ns: %9ld\n", buf, ns);
}

struct stat_macb** get_multi_path_timestamps(int watch_num, char** watch_array){
    struct stat_macb** multi_stat = calloc(sizeof(struct stat_macb*), watch_num);
    
    int i;
    for (i=0; i<watch_num; i++){
        multi_stat[i] = get_path_timestamps_lstat(watch_array[i]);
    }
    
    return multi_stat;
}

struct stat_macb* get_path_timestamps(char *path) {
    struct stat* attr = (struct stat*) calloc(sizeof(struct stat), 1);
    int res = stat(path, attr);
    if (res != 0){
        return NULL;
    }
    
    stat_macb* stat_macb = stat_macb_from_stat_add_b(attr, path, 1);

    free(attr);
    return stat_macb;
}

struct stat_macb* get_fd_timestamps(int fd) {
    struct stat* attr = (struct stat*) calloc(sizeof(struct stat), 1);
    int res = fstat(fd, attr);
    if (res != 0){
        return NULL;
    }
    
    stat_macb* stat_macb = stat_macb_from_stat_no_b(attr);
    free(attr);

    return stat_macb;
}

struct stat_macb* get_file_timestamps(FILE *f) {
    struct stat* attr = (struct stat*) calloc(sizeof(struct stat), 1);
    int res = fstat(fileno(f), attr);
    if (res != 0){
        return NULL;
    }
    
    stat_macb* stat_macb = stat_macb_from_stat_no_b(attr);
    free(attr);

    return stat_macb;
}

struct stat_macb* get_path_timestamps_lstat(char *path) {
    struct stat* attr = (struct stat*) calloc(sizeof(struct stat), 1);
    int res = lstat(path, attr);
    if (res != 0){
        return NULL;
    }
    
    stat_macb* stat_macb = stat_macb_from_stat_add_b(attr, path, 0);
    free(attr);

    return stat_macb;
}

#ifdef __linux__
struct statx* get_path_timestamps_statx(char *path, int follow) {
    struct statx* attr_statx = (struct statx*) calloc(sizeof(struct statx), 1);
    // man 2 statx
    // Note: There is no glibc wrapper for statx(); see NOTES.
    // NOTES
    // Glibc does not (yet) provide a wrapper for the statx() system call; call it using syscall(2).
    int flags = 0;
    if (follow == 0){
        flags |= AT_SYMLINK_NOFOLLOW;
    }
    
    unsigned int mask = STATX_ATIME | STATX_MTIME | STATX_CTIME | STATX_BTIME;
    int res = syscall(SYS_statx, AT_FDCWD, path, flags, mask, attr_statx);
    if (res != 0){
        fprintf(stderr, "ERROR: SYS_statx failed\n");
        return NULL;
    }
    
    return attr_statx;
}

void print_path_timestamps_statx_ns(char *path, int follow, char inode) {
    struct statx* attr_statx = get_path_timestamps_statx(path, follow);
    
    if (attr_statx == NULL){
        printf("ERROR: print_path_timestamps_statx_ns - attr is NULL\n");
        return;
    }
    
    time_t s = attr_statx->stx_mtime.tv_sec;
    long ns = attr_statx->stx_mtime.tv_nsec;
    char* buf = ctime(&s);
    buf[strlen(buf)-1] = 0;
    printf("M: %s - ns: %9ld\n", buf, ns);
    
    s = attr_statx->stx_atime.tv_sec;
    ns = attr_statx->stx_atime.tv_nsec;
    buf = ctime(&s);
    buf[strlen(buf)-1] = 0;
    printf("A: %s - ns: %9ld\n", buf, ns);
    
    s = attr_statx->stx_ctime.tv_sec;
    ns = attr_statx->stx_ctime.tv_nsec;
    buf = ctime(&s);
    buf[strlen(buf)-1] = 0;
    printf("C: %s - ns: %9ld\n", buf, ns);
    
    s = attr_statx->stx_btime.tv_sec;
    ns = attr_statx->stx_btime.tv_nsec;
    buf = ctime(&s);
    buf[strlen(buf)-1] = 0;
    printf("B: %s - ns: %9ld\n", buf, ns);

    if (inode == 1) printf("I: %llu\n", attr_statx->stx_ino);
}

void print_path_timestamps_statx_int_ns(char *path, int follow, char inode) {
    struct statx* attr_statx = get_path_timestamps_statx(path, follow);
    
    if (attr_statx == NULL){
        printf("ERROR: print_path_timestamps_statx_int_ns - attr is NULL\n");
        return;
    }
    
    time_t s = attr_statx->stx_mtime.tv_sec;
    long ns = attr_statx->stx_mtime.tv_nsec;
    printf("M: %d.%09ld\n", s, ns);
    
    s = attr_statx->stx_atime.tv_sec;
    ns = attr_statx->stx_atime.tv_nsec;
    printf("A: %d.%09ld\n", s, ns);
    
    s = attr_statx->stx_ctime.tv_sec;
    ns = attr_statx->stx_ctime.tv_nsec;
    printf("C: %d.%09ld\n", s, ns);
    
    s = attr_statx->stx_btime.tv_sec;
    ns = attr_statx->stx_btime.tv_nsec;
    printf("B: %d.%09ld\n", s, ns);

    if (inode == 1) printf("I: %llu\n", attr_statx->stx_ino);
}

#endif


#endif
