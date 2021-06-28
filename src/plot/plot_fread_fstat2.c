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

void action_before(int mode, int n_file, FILE* f, char* file_path){
    if (mode == 0){
        char* buf = (char*) calloc(3, sizeof(char));
        int n_read = fread(buf, 1, 2, f);
        fflush(f);
    }
    else if (mode == 1){
        char* buf = (char*) calloc(3, sizeof(char));
        int n_read = fread(buf, 1, 2, f);
        struct stat* attr = (struct stat*) calloc(sizeof(struct stat), 1);
        fstat(fileno(f), attr);
    }
    else if (mode == 2){
        char* buf = (char*) calloc(3, sizeof(char));
        int n_read = fread(buf, 1, 2, f);
    }
}

void action_after(int mode, int n_file, FILE* f, char* file_path){
    switch (mode){
        case 0:
        case 1:
        case 2:
            fclose(f);
            break;
    }
}

int main (int argc, char **argv){
    current_time_setup_local_timemarker(stdout, stderr);
    current_time_setup_local_timemarkerdir(stdout, stderr);
    int n_warn_ts_a_dec = 0;
    
    int mode = 0;
    char* desc;
    char* csv_name;
    if (argc >= 2){
        mode = atoi(argv[1]);
    }
    else {
        printf("Missing mode, exiting.\n");
        return 1;
    }
    
    if (mode == 0){
        desc = "fopen+fread+fflush ... fclose";
        csv_name = "plot.delay.fread_fflush.csv";
    }
    else if (mode == 1){
        desc = "fopen+fread+fstat ... fclose";
        csv_name = "plot.delay.fread_fstat.csv";
    }
    else if (mode == 2){
        desc = "fopen+fread ... fclose";
        csv_name = "plot.delay.fread.csv";
    }
    else {
        printf("Unknown mode %d, exiting.\n", mode);
        return 1;
    }
    
    printf("Mode: %d - %s\n", mode, desc);
    FILE* csv_file = fopen(csv_name, "wb");
    
//     int s_wait_close=60;
    int s_wait_close=60;
//     long ns_wait_close = s_wait_close*ns_1s;
    struct timespec* ts_wait_close = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_wait_close->tv_sec = s_wait_close;
    ts_wait_close->tv_nsec = 0;

//     int s_delay_fopen=1;
    int s_delay_fopen=0;
    long ns_delay_fopen=1*ns_100ms;
//     long ns_delay_fopen=0;
//     long ns_delay_fopen = s_delay_fopen*ns_1s;
    struct timespec* ts_delay_fopen = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_delay_fopen->tv_sec = s_delay_fopen;
    ts_delay_fopen->tv_nsec = ns_delay_fopen;
    
//     int n_delays=3*600; // 3 minutes
    int n_delays=3*600; // 3 minutes

//     int n_fopen = 1;
    int n_fopen = 5;
    int n_files = n_delays * n_fopen;

    struct  timespec* files_ts_time_fopen_before[n_files]; 
    struct  timespec* files_ts_time_fopen_after[n_files]; 
    FILE* files_f[n_files];

    int d;
    int n;
    // Create empty files
    for (d = 0; d < n_delays; d++){
        for (n = 0; n < n_fopen; n++){
            int n_file = d*n_fopen+n;
            char* file_path = get_file_path(n_file);
            if (misc_file_exists(file_path) == 0){
                int r = unlink(file_path);
                if (r !=0){
                    printf("ERROR: unlink failed.\n");
                }
            }
            misc_concat_ensure_file_exists_filled(file_path, "", 10, s_0s, ns_0ns, stdout, stderr, __func__);
        }
    }
    
    printf("Delaying for 2 seconds after file creation (delay)\n");
    nanosleep(2*ns_1s, NULL);
   
    struct timespec* ts_start = current_time_ns_fslike_osspecific();
    misc_print_timespec("ts_start", ts_start);
  
    // fopen() + fread()
    for (d = 0; d < n_delays; d++){
        printf("Reading %d file(s) at step: %d (delay_fopen=%d s + %lu ns, n_delays=%d):\n", n_fopen, d, s_delay_fopen, ns_delay_fopen, n_delays);
        for (n = 0; n < n_fopen; n++){
            int n_file = d*n_fopen+n;
            char* file_path = get_file_path(n_file);
            struct timespec* ts_before = current_time_ns_fslike_osspecific();
            FILE* f = fopen(file_path, "rb");
            if (f == NULL) {
                log_warning(stdout, stderr, "%s - %s %s", __func__, "error opening/creating file", file_path);
                return NULL;
            }
            action_before(mode, n_file, f, file_path);
            struct timespec* ts_after = current_time_ns_fslike_osspecific();

            printf("%d read:\n", n_file);
            misc_print_timespec("  ts_before", ts_before);
            misc_print_timespec("  ts_after ", ts_after);

            files_f[n_file]=f;
            files_ts_time_fopen_before[n_file]=ts_before;
            files_ts_time_fopen_after[n_file]=ts_after;
        }
        nanosleep(ts_delay_fopen, NULL);
    }
   
    // delays
    printf("Delaying for %d seconds (wait_close)\n", s_wait_close);
    nanosleep(ts_wait_close, NULL);

    struct timespec* last_ts_A = NULL;
    
    // fclose and calculate
    for (d = 0; d < n_delays; d++){
        for (n = 0; n < n_fopen; n++){
            int n_file = d*n_fopen+n;
            char* file_path = get_file_path(n_file);
            struct timespec* ts_before = files_ts_time_fopen_before[n_file];
            struct timespec* ts_after= files_ts_time_fopen_after[n_file];
            FILE* f = files_f[n_file];
            if (f == NULL) {
                log_warning(stdout, stderr, "%s - %s %d", __func__, "got an invalid file descriptor", n_file);
                return NULL;
            }
            action_after(mode, n_file, f, file_path);
            
            struct stat_macb* file_stat = get_path_timestamps(file_path);
            struct timespec* ts_A = &(file_stat->st_atim);
            printf("%d:\n", n_file);
            misc_print_timespec("ts_before", ts_before);
            misc_print_timespec("ts_after", ts_after);
            misc_print_timespec("ts_A", ts_A);
            
            if (n_file != 0){
                if (misc_timespec_l(ts_A, last_ts_A) == 0){
                    printf("WARNING TS_A_DEC: %d_A < %d_A\n", n_file, n_file-1);
                    misc_print_timespec("  ts_A     ", ts_A);
                    misc_print_timespec("  last_ts_A", last_ts_A);
                    n_warn_ts_a_dec++;
                }
            }
            
            struct timespec* ts_delta;
            if (misc_timespec_leq_leq(ts_before, ts_A, ts_after) == 0){
                ts_delta = (struct timespec*) calloc(sizeof(struct timespec), 1);
                ts_delta->tv_sec = 0;
                ts_delta->tv_nsec = 0;
            }
            else {
                ts_delta = misc_timespec_diff_ts2_ts1(ts_after, ts_A);
            }
            
            misc_print_timespec("ts_delta", ts_delta);
            long ns_delta = (ts_delta->tv_sec)*ns_1s + ts_delta->tv_nsec;

//             misc_print_timespec("ts_start", ts_start);
//             misc_print_timespec("ts_before", ts_before);
            struct timespec* ts_delay = misc_timespec_diff_ts2_ts1(ts_start, ts_before);
            long ns_delay = (ts_delay->tv_sec)*ns_1s + ts_delay->tv_nsec;
            misc_print_timespec("ts_delay", ts_delay);
            printf("\n");

            
            fprintf(csv_file, "%lu %lu\n", ns_delay, ns_delta);
            
            last_ts_A = ts_A;
        }
    }
    
    fflush(csv_file);
    
    struct timespec* ts_end = current_time_ns_fslike_osspecific();
    misc_print_timespec("ts_end", ts_end);
    printf("n_warn_ts_a_dec: %d\n", n_warn_ts_a_dec);
}
#endif
