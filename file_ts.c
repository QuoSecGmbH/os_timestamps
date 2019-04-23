#ifndef FILE_TS_C
#define FILE_TS_C

#include "file_ts.h"

int main (){
//   print_path_timestamps_s("/home/ath/fortime/tests/test");
  print_path_timestamps_ns("/home/ath/fortime/tests/test");
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

struct stat* get_path_timestamps(char *path) {
    struct stat* attr = (struct stat*) calloc(sizeof(struct stat), 1);
    int res = stat(path, attr);
    if (res != 0){
        printf("ERROR: get_path_timestamps_s - stat failed\n");
        return NULL;
    }
    
    return attr;
}

#endif
