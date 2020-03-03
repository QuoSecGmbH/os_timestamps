#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <sys/stat.h>

#ifdef __linux__
#include <linux/stat.h>
#endif

struct stat* path_timestamps_ns(char* path) {
    struct stat* attr = (struct stat*) calloc(sizeof(struct stat), 1);
    int res = stat(path, attr);
    if (res != 0){
        printf("stat error, errno %d\n", errno);
        return NULL;
    }
    
    if (attr == NULL){
        printf("ERROR: print_file_timestamps_s - attr is NULL\n");
        return NULL;
    }
    
    return attr;
}

void print_attr(struct stat* attr){
    if (attr == NULL){
        printf("ERROR: print_path_timestamps_ns - attr is NULL\n");
        return;
    }
    
//     time_t s = attr->st_mtim.tv_sec;
//     long ns = attr->st_mtim.tv_nsec;
//     char* buf = ctime(&s);
//     buf[strlen(buf)-1] = 0;
//     printf("M: %s - ns: %9ld\n", buf, ns);
    
    time_t s = attr->st_atim.tv_sec;
    long ns = attr->st_atim.tv_nsec;
    char* buf = ctime(&s);
    buf[strlen(buf)-1] = 0;
    printf("A: %s - ns: %9ld\n", buf, ns);
    
//     s = attr->st_ctim.tv_sec;
//     ns = attr->st_ctim.tv_nsec;
//     buf = ctime(&s);
//     buf[strlen(buf)-1] = 0;
//     printf("C: %s - ns: %9ld\n", buf, ns);
}

int main(int argc, char* argv[]){
    char* path = (char*) "standalone.fread_wait";
    unlink(path);
    
    FILE* fd = fopen(path, "wb");
    if (fd == NULL) {
        printf("Error opening/creating file.\n");
        return 1;
    }
    char* buf = "Hello this is a test.";
    fwrite(buf, 1, strlen(buf), fd);
    fclose(fd);
    
    struct stat* f_stat = path_timestamps_ns(path);
    printf("After creation:\n");
    print_attr(f_stat);
    
    struct timespec* ts_wait = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_wait->tv_sec = 1;
    ts_wait->tv_nsec = 0;
    nanosleep(ts_wait, NULL);
    
    fd = fopen(path, "rb");
    if (fd == NULL) {
        printf("Error opening/creating file\n");
        return 1;
    }
    
    char* buf2 = (char*) calloc(3, sizeof(char));
    int n_read = fread(buf2, 1, 2, fd);
    
    if (n_read != 2){
        printf("Could not read data from file\n");
        return 1;
    }
    
    while (1 == 1){
        nanosleep(ts_wait, NULL);
    }
    
    fclose(fd);
}
