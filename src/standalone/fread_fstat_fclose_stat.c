#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <time.h> 
#include <stdlib.h>

#ifdef __linux__
#include <linux/stat.h>
#endif

struct stat* file_timestamps_ns(FILE *f);
struct stat* path_timestamps_ns(char* path);
int main(int argc, char* argv[]);
void print_attr(struct stat* attr);

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

struct stat* file_timestamps_ns(FILE *f) {
    struct stat* attr = (struct stat*) calloc(sizeof(struct stat), 1);
    int res = fstat(fileno(f), attr);
    if (res != 0){
        printf("fstat error, errno %d\n", errno);
        return NULL;
    }
    
    if (attr == NULL){
        printf("ERROR: print_file_timestamps_s - attr is NULL\n");
        return NULL;
    }
    
    return attr;
}

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

int main(int argc, char* argv[]){
    char* path = (char*) "standalone.fwrite_fstat_fclose_stat";
    
    FILE* fd = fopen(path, "wb");
    if (fd == NULL) {
        printf("Error opening/creating file.\n");
        return 1;
    }
    char* buf = "Hello this is a test.";
    fwrite(buf, 1, strlen(buf), fd);
    fclose(fd);
    
    struct stat* attr_fd_1 = path_timestamps_ns(path);
    
    sleep(1);
    
    fd = fopen(path, "rb");    
    char buf2[6];
    fread(buf2, 5, 1, fd);
    printf("read: %s\n", buf2);
    
    struct stat* attr_fd_2 = file_timestamps_ns(fd);
    struct stat* attr_fd_3 = file_timestamps_ns(fd);
    
    sleep(1);
    
    struct stat* attr_fd_4 = file_timestamps_ns(fd);
    
    sleep(1);
    
    fclose(fd);
    struct stat* attr_fd_5 = path_timestamps_ns(path);
    
    sleep(1);
    
    struct stat* attr_fd_6 = path_timestamps_ns(path);
    
    printf("After creation:\n");
    print_attr(attr_fd_1);
    
    printf("After fread (fstat):\n");
    print_attr(attr_fd_2);
    
    printf("After fread+fstat (fstat):\n");
    print_attr(attr_fd_3);
    
    printf("After fread+fstat+fstat+sleep(1):\n");
    print_attr(attr_fd_4);
    
    printf("After fread+fstat+fstat+sleep(1)+fclose (stat):\n");
    print_attr(attr_fd_5);
    
    printf("After fread+fstat+fstat+sleep(1)+fclose+sleep(1) (stat):\n");
    print_attr(attr_fd_6);
    
    return 0; 
}

