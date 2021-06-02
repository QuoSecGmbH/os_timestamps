#ifndef PLOT_FREAD_FSTAT2_C
#define PLOT_FREAD_FSTAT2_C

#include "plot_fread_fstat2.h"

char* get_file_path(int n){
    char* base_name = "plot.fread_fstat2.file";
    char* buf_name = (char*) calloc(sizeof(char), strlen(base_name)+10);
    sprintf(buf_name, "%s_%08d", base_name, n);
    //    char* path = misc_concat("./", buf_name);
    return buf_name;
}

int main (int argc, char **argv){
    current_time_setup_local_timemarker(stdout, stderr);
    current_time_setup_local_timemarkerdir(stdout, stderr);
    FILE* csv_file = fopen("plot.fread_fstat2.csv", "wb");
    
    int s_wait_close=60;
//     long ns_wait_close = s_wait_close*ns_1s;
    struct timespec* ts_wait_close = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_wait_close->tv_sec = s_wait_close;
    ts_wait_close->tv_nsec = 0;

    int s_delay_fopen=1;
//     long ns_delay_fopen=1*ns_100ms;
    long ns_delay_fopen=0;
//     long ns_delay_fopen = s_delay_fopen*ns_1s;
    struct timespec* ts_delay_fopen = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_delay_fopen->tv_sec = s_delay_fopen;
    ts_delay_fopen->tv_nsec = ns_delay_fopen;
    
    int n_delays=60; // 3 minutes
//     int n_delays=3*600; // 3 minutes

    int n_fopen = 1;
//     int n_fopen = 5;
    int n_files = n_delays * n_fopen;

    struct  timespec* files_ts_time_fopen[n_files]; 
    FILE* files_fd[n_files];

    int d;
    int n;
    // Create empty files
    for (d = 0; d < n_delays; d++){
        for (n = 0; n < n_fopen; n++){
            int n_file = d*n_fopen+n;
            char* file_path = get_file_path(n_file);
            misc_concat_ensure_file_exists_filled(file_path, "", 10, s_0s, ns_0ns, stdout, stderr, __func__);
        }
    }
   
    struct timespec* ts_start = current_time_ns_fslike_osspecific();
    misc_print_timespec("ts_start", ts_start);
  
    // fopen() + fread()
    for (d = 0; d < n_delays; d++){
        printf("Creating %d files at step: %d (delay_fopen=%d s + %lu ns, n_delays=%d)\n", n_fopen, d, s_delay_fopen, ns_delay_fopen, n_delays);
        for (n = 0; n < n_fopen; n++){
            int n_file = d*n_fopen+n;
            char* file_path = get_file_path(n_file);
            struct timespec* ts_before = current_time_ns_fslike_osspecific();
            FILE* fd = fopen(file_path, "rb");
            if (fd == NULL) {
                log_warning(stdout, stderr, "%s - %s %s", __func__, "error opening/creating file", file_path);
                return NULL;
            }
            char* buf = (char*) calloc(3, sizeof(char));
            int n_read = fread(buf, 1, 2, fd);
            fflush(fd);
            get_fd_timestamps(fd);
//             fclose(fd);
            
            files_fd[n_file]=fd;
            files_ts_time_fopen[n_file]=ts_before;
        }
        nanosleep(ts_delay_fopen, NULL);
    }
   
    // delays
    printf("Delaying for %d seconds (wait_close)\n", s_wait_close);
    nanosleep(ts_wait_close, NULL);

    // fclose and calculate
    for (d = 0; d < n_delays; d++){
        for (n = 0; n < n_fopen; n++){
            int n_file = d*n_fopen+n;
            char* file_path = get_file_path(n_file);
            struct timespec* ts_before = files_ts_time_fopen[n_file];
            FILE* fd = files_fd[n_file];
            if (fd == NULL) {
                log_warning(stdout, stderr, "%s - %s %d", __func__, "got an invalid file descriptor", n_file);
                return NULL;
            }
//             fsync(fd);
            fclose(fd);
            
            struct stat_macb* file_stat = get_path_timestamps(file_path);
            struct timespec* ts_A = &(file_stat->st_atim);
            misc_print_timespec("ts_before", ts_before);
            misc_print_timespec("ts_A", ts_A);
            struct timespec* ts_delta = misc_timespec_diff_ts2_ts1(ts_before, ts_A);
            misc_print_timespec("ts_delta", ts_delta);
            long ns_delta = (ts_delta->tv_sec)*ns_1s + ts_delta->tv_nsec;

//             misc_print_timespec("ts_start", ts_start);
//             misc_print_timespec("ts_before", ts_before);
            struct timespec* ts_delay = misc_timespec_diff_ts2_ts1(ts_start, ts_before);
            long ns_delay = (ts_delay->tv_sec)*ns_1s + ts_delay->tv_nsec;
            misc_print_timespec("ts_delay", ts_delay);
            printf("\n");

            
            fprintf(csv_file, "%lu %lu\n", ns_delay, ns_delta);
        }
    }
    
    fflush(csv_file);
    
    struct timespec* ts_end = current_time_ns_fslike_osspecific();
    misc_print_timespec("ts_end", ts_end);
}
#endif
