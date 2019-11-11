#ifndef CURRENT_TIME_C
#define CURRENT_TIME_C

#include "current_time.h"

char* path_timemarker;
char* path_timemarkerdir;

void current_time_setup_local_timemarker(FILE* output_file, FILE* error_file){
    char current_pwd[256];
    char* retc = getcwd(current_pwd, 256);
    if (retc == NULL){
        log_warning(output_file, error_file, "%s - %s", __func__, "error getting current_pwd");
        path_timemarker = "/tmp/tmp_posixtest_timemarker";
    }
    else{
        path_timemarker = misc_concat(current_pwd, "/tmp_posixtest_timemarker");
    }
    
    log_info(output_file, error_file, "path_timemarker: %s", path_timemarker);
    misc_concat_ensure_file_exists(path_timemarker, "", 0, ns_after_open, output_file, error_file, __func__);
}

void current_time_setup_local_timemarkerdir(FILE* output_file, FILE* error_file){
    char current_pwd[256];
    char* retc = getcwd(current_pwd, 256);
    if (retc == NULL){
        log_warning(output_file, error_file, "%s - %s", __func__, "error getting current_pwd");
        path_timemarkerdir = "/tmp/tmp_posixtest_timemarker_dir/";
    }
    else {
        path_timemarkerdir = misc_concat(current_pwd, "/tmp_posixtest_timemarker_dir/");
    }
    
    log_info(output_file, error_file, "path_timemarkerdir: %s", path_timemarkerdir);
    misc_ensure_dir_exists(path_timemarkerdir, 0, ns_after_open, output_file, error_file, __func__);
}

void print_current_time_s(){
  time_t* rawtime = current_time_s();
  struct tm * timeinfo;
  timeinfo = localtime(rawtime);
  printf("%s", asctime(timeinfo) );
  free(rawtime);
}

time_t* current_time_s(){
  time_t* rawtime = (time_t*) calloc(sizeof(time_t), 1);
  time(rawtime);
  return rawtime;
}

void print_current_time_ns(){
  print_current_time_custom(CLOCK_REALTIME);
}

void print_current_time_ns_fslike_osspecific(){
  struct timespec* ts = current_time_ns_fslike_osspecific();
  struct tm * timeinfo;
  time_t rawtime = ts->tv_sec;
  timeinfo = localtime(&rawtime);
  char* buf = asctime(timeinfo);
  int n = strlen(buf);
  buf[n-1] = 0;
  printf("%s - s: %ld - ns: %9ld\n", buf, ts->tv_sec, ts->tv_nsec);
  free(ts);
}

void print_current_time_custom(int type){
  struct timespec* ts = current_time_custom(type);
  struct tm * timeinfo;
  time_t rawtime = ts->tv_sec;
  timeinfo = localtime(&rawtime);
  char* buf = asctime(timeinfo);
  int n = strlen(buf);
  buf[n-1] = 0;
  printf("%s - s: %ld - ns: %9ld\n", buf, ts->tv_sec, ts->tv_nsec);
  free(ts);
}

#ifdef __linux__
struct timespec* current_time_ns_linux_coarse(){
  // Linux kernel sets inode timestamps to clock CLOCK_REALTIME_COARSE
  return current_time_custom(CLOCK_REALTIME_COARSE);
}
#endif

#ifdef __FreeBSD__
struct timespec* current_time_ns_freebsd_coarse(){
// FreeBSD kernel sets inode timestamps to vfs_timestamp()
// There does not seem to be a way to call vfs_timestamp() from userland
// vfs_timestamp does:
//   1 - call microtime
//   2 - call TIMEVAL_TO_TIMESPEC
// Approximation is made by:
//   1 - calling kern_clock_gettime(CLOCK_REALTIME_PRECISE) that calls nanotime
//   2 - Floor to microsecond

  // 1:
  struct timespec* ts = current_time_custom(CLOCK_REALTIME_PRECISE);

  // 2:
  int rest = ts->tv_nsec % 1000;
  ts->tv_nsec = ts->tv_nsec - rest;

  return ts;
}
#endif


#ifdef __OpenBSD__
struct timespec* current_time_ns_openbsd_coarse(){
// OpenBSD kernel sets inode timestamp to getnanotime()
// There does not seem to be a way to call getnanotime() from userland
// There does not seem to be any way to access coarse times (get*) from userland
// Workaround is to write a file then read its M

  return current_time_ns_fslike_generic();
}
#endif


struct timespec* current_time_ns_fslike_generic(){
// Workaround in the general case is to write a file then read its M

  if (path_timemarker == NULL){
    fprintf(stderr, "ERROR (fatal): path_timemarker not set in %s\n", __func__);
    struct timespec* ts = (struct timespec*) calloc(sizeof(struct timespec*), 1);
    return ts;
  }
    
  FILE* fd = fopen(path_timemarker, "wb");
  if (fd == NULL) {
      printf("ERROR: current_time_ns_fslike_generic - can't open tmp_timemarker\n");
      struct timespec* ts = (struct timespec*) calloc(sizeof(struct timespec*), 1);
      return ts;
  }
  fwrite("!", 1, 1, fd);
  fclose(fd);

  struct stat* file_stat = get_path_timestamps(path_timemarker);
  return &(file_stat->st_mtim);
}

struct timespec* current_time_ns_fslike_generic_futimens(){
// Workaround in the general case is to write a file then read its M
// Does not write to the file
    
  if (path_timemarker == NULL){
    fprintf(stderr, "ERROR (fatal): path_timemarker not set in %s\n", __func__);
    struct timespec* ts = (struct timespec*) calloc(sizeof(struct timespec*), 1);
    return ts;
  }

  int fd = open(path_timemarker, O_RDWR);
  if (fd == -1) {
      printf("ERROR: current_time_ns_fslike_generic_futimens - can't open tmp_timemarker\n");
      struct timespec* ts = (struct timespec*) calloc(sizeof(struct timespec*), 1);
      return ts;
  }
  
  struct timespec* ts_now1 = (struct timespec*) calloc(sizeof(struct timespec), 1);
  struct timespec* ts_now2 = (struct timespec*) calloc(sizeof(struct timespec), 1);
  ts_now1->tv_nsec = UTIME_NOW;
  ts_now1->tv_sec = 0;
  ts_now2->tv_nsec = UTIME_NOW;
  ts_now2->tv_sec = 0;
    
  struct timespec times[2];
  times[0] = *ts_now1;
  times[1] = *ts_now2;
    
  int ret = futimens(fd, times);
  if (ret != 0) {
      printf("%s - %s %d\n", __func__, "futimens failed with errno", errno);
      struct timespec* ts = (struct timespec*) calloc(sizeof(struct timespec*), 1);
      return ts;
  }

  close(fd);
  
  struct stat* file_stat = get_path_timestamps(path_timemarker);
  return &(file_stat->st_mtim);
}

struct timespec* current_time_ns_fslike_generic_futimens_dir(){
// Workaround in the general case is to write a file then read its M
// Does not write to the directory
    
  if (path_timemarkerdir == NULL){
    fprintf(stderr, "ERROR (fatal): path_timemarkerdir not set in %s\n", __func__);
  }

  int fd = open(path_timemarkerdir, O_RDONLY);
  if (fd == -1) {
      printf("ERROR: current_time_ns_fslike_generic_futimens - can't open tmp_timemarker\n");
      struct timespec* ts = (struct timespec*) calloc(sizeof(struct timespec*), 1);
      return ts;
  }
  
  struct timespec* ts_now1 = (struct timespec*) calloc(sizeof(struct timespec), 1);
  struct timespec* ts_now2 = (struct timespec*) calloc(sizeof(struct timespec), 1);
  ts_now1->tv_nsec = UTIME_OMIT;
  ts_now1->tv_sec = 0;
  ts_now2->tv_nsec = UTIME_NOW;
  ts_now2->tv_sec = 0;
    
  struct timespec times[2];
  times[0] = *ts_now1;
  times[1] = *ts_now2;
    
  int ret = futimens(fd, times);
  if (ret != 0) {
      printf("%s - %s %d\n", __func__, "futimens failed with errno", errno);
      struct timespec* ts = (struct timespec*) calloc(sizeof(struct timespec*), 1);
      return ts;
  }

  close(fd);
  
  struct stat* file_stat = get_path_timestamps(path_timemarkerdir);
  return &(file_stat->st_mtim);
}


struct timespec* current_time_ns_fslike_osspecific(){
#ifdef __linux__
    return current_time_ns_linux_coarse();
#elif __FreeBSD__
    return current_time_ns_freebsd_coarse();
#elif __OpenBSD__
    return current_time_ns_openbsd_coarse();
#else
    return current_time_ns_fslike_generic_futimens_dir();
#endif
}

struct timespec* current_time_ns(){
  return current_time_custom(CLOCK_REALTIME);
}

struct timespec* current_time_custom(int type){
  struct timespec* ts = (struct timespec*) calloc(sizeof(struct timespec), 1);
  
  // POSIX-specified
  clock_gettime(type, ts);
  
  return ts;
}

int check_general_clock_res(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  struct timespec ts;
  int res = clock_getres(CLOCK_REALTIME, &ts);
  if (res != 0){
    log_error(output_file, error_file, "check_clock_res - clock_getres failed\n");
    return 1;
  }
  
  time_t s = ts.tv_sec;
  long ns = ts.tv_nsec;
  
  int result = 0;
  if (s != 0){
    log_warning(output_file, error_file, "Clock resolution is greater than 1s.");
    result = 2;
  }
  else if (ns > 20000000){
    log_warning(output_file, error_file, "Clock resolution is greater than 20 000 000ns.");
    result = 2;
  }
  else if (s != 0 && ns != 0){
    log_warning(output_file, error_file, "Clock resolution has both s and ns values.");
    result = 2;
  }
  
  printf ("INFO: Clock resolution is: %ld s - %ld ns (CLOCK_REALTIME)\n", s, ns);
  return result;
}


int check_general_clock_increments(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    int i = 0;
    struct timespec* ts = NULL;
    struct timespec* last_ts = NULL;
    
    int result = 0;
    for (i=0; i<100; i++){
        ts = current_time_ns();
        log_debug(output_file, error_file, "%ld - %ld", ts->tv_sec, ts->tv_nsec);
        
        if (i != 0){
            if (misc_timespec_leq(last_ts, ts) != 0){
                result = 2;
                free(last_ts);
                free(ts);
                break;
            }
            free(last_ts);
        }
        last_ts = ts;
    }
    free(ts);
    
    return result;
}

#endif
