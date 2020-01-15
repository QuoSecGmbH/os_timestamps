#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <time.h> 

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
    
    time_t s = attr->st_mtim.tv_sec;
    long ns = attr->st_mtim.tv_nsec;
    char* buf = ctime(&s);
    buf[strlen(buf)-1] = 0;
    printf("M: %s - ns: %9ld\n", buf, ns);
    
//     s = attr->st_atim.tv_sec;
//     ns = attr->st_atim.tv_nsec;
//     buf = ctime(&s);
//     buf[strlen(buf)-1] = 0;
//     printf("A: %s - ns: %9ld\n", buf, ns);
    
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
    char* path = (char*) "standalone.fprintf_fflush";
    char* path_marker = (char*) "standalone.fprintf_fflush.marker";
    
    FILE* fdm = fopen(path_marker, "wb");
    if (fdm == NULL) {
        printf("Error opening/creating file.\n");
        return 1;
    }
    struct stat* attr_fdm_1 = file_timestamps_ns(fdm);
//         fwrite("!", 1, 1, fdm);
    FILE* fd = fopen(path, "wb");
    if (fd == NULL) {
        printf("Error opening/creating file.\n");
        return 1;
    }
    struct stat* attr_fd_1 = file_timestamps_ns(fd);
//         fwrite("!", 1, 1, fdm);
    sleep(1);
//         fwrite("!", 1, 1, fdm);
    fprintf(fd, "%s\n", "fprintf test");
//         fwrite("!", 1, 1, fdm);
    fflush(fd);
    struct stat* attr_fd_2 = file_timestamps_ns(fd);
    
    fwrite("!", 1, 1, fdm);
//     fclose(fdm);
//     struct stat* attr_fdm_2 = path_timestamps_ns(path_marker);
    struct stat* attr_fdm_2 = file_timestamps_ns(fdm);
    attr_fdm_2 = file_timestamps_ns(fdm);
    
    
    printf("standalone.fprintf_fflush.marker after creation:\n");
    print_attr(attr_fdm_1);
    
    printf("standalone.fprintf_fflush after creation:\n");
    print_attr(attr_fd_1);
    
    printf("standalone.fprintf_fflush after fprintf+fflush:\n");
    print_attr(attr_fd_2);
    
    printf("standalone.fprintf_fflush.marker fwrite+fclose:\n");
    print_attr(attr_fdm_2);
    
    return 0; 
}

