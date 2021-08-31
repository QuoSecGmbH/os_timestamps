#ifndef PLOT_FREAD_FSTAT_C
#define PLOT_FREAD_FSTAT_C

#include "plot_fread_fstat.h"

struct timespec* delta(struct timespec* ts_wait){
    char* base_name = "plot.fread_fstat.file";
    char* buf_name = (char*) calloc(sizeof(char), strlen(base_name)+9+9);
    sprintf(buf_name, "%s_%04d.%09lu", base_name, ts_wait->tv_sec, ts_wait->tv_nsec);
    char* path = misc_concat("./", buf_name);
    
    unlink(path);
    path = (char*) misc_concat_ensure_file_exists_filled(path, "", 10, s_0s, ns_0ns, stdout, stderr, __func__);
    
    FILE* fd = fopen(path, "rb");
    if (fd == NULL) {
        log_warning(stdout, stderr, "%s - %s %s", __func__, "error opening/creating file", path);
        return NULL;
    }
    
//     struct timespec* ts_before = current_time_ns_fslike_osspecific();
//     struct stat_macb* file_stat_before = get_path_timestamps(path);
//     struct timespec* ts_before = &(file_stat_before->st_mtim);
    struct timespec* ts_before = current_time_ns();
    
    char* buf = (char*) calloc(3, sizeof(char));
    int n_read = fread(buf, 1, 2, fd);
    
    if (n_read != 2){
        log_warning(stdout, stderr, "%s - %s", __func__, "could not read data from file");
        return NULL;
    }
    
    nanosleep(ts_wait, NULL);
    
//     struct stat_macb* file_stat = get_file_timestamps(fd);
    struct stat_macb* file_stat = get_path_timestamps(path);
    struct timespec* ts_diff = misc_timespec_diff_ts2_ts1(ts_before, &(file_stat->st_atim));
    
    fclose(fd);
    return ts_diff;
}

int main (int argc, char **argv){
    current_time_setup_local_timemarker(stdout, stderr);
    current_time_setup_local_timemarkerdir(stdout, stderr);
    
    FILE* csv_file = fopen("plot.fread_fstat.csv", "wb");
//     FILE* csv_file = log_open_csv("plot.fread_fstat.csv");
//     log_csv_add_line(csv_file, 2, "x", "delta(x)");
//     FILE* csv_file = log_open_csv_append("plot.fread_fstat.csv");
    
    int sec;
    int msec;
    int n_repeat = 1;
    int n;
    for (sec = 0; sec < 100; sec++){
        printf("sec: %d\n", sec);
        for (msec = 0; msec < 1; msec ++){
            printf("  msec: %d\n", msec);
            struct timespec* ts_wait = (struct timespec*) calloc(sizeof(struct timespec), 1);
            ts_wait->tv_sec = sec;
            ts_wait->tv_nsec = ns_1ms*1000*msec;
            long ns_wait = (ts_wait->tv_sec)*ns_1s + ts_wait->tv_nsec;
            
            for (n = 0; n < n_repeat; n++){
               struct timespec* ts_delta =  delta(ts_wait);
               long ns_delta = (ts_delta->tv_sec)*ns_1s + ts_delta->tv_nsec;
               
//                char buf_wait[20];
//                sprintf(buf_wait, "%lu", ns_wait);
//                
//                char buf_delta[20];
//                sprintf(buf_delta, "%lu", ns_delta);
               
               
//                printf("    %s: %s\n", buf_wait, buf_delta);
               printf("    %lu: %lu\n", ns_wait, ns_delta);
//                log_csv_add_line(csv_file, 2, buf_wait, buf_delta);
               fprintf(csv_file, "%lu %lu\n", ns_wait, ns_delta);
               fflush(csv_file);
            }
        }
    }
}
#endif
