#ifndef CURRENT_TIME_C
#define CURRENT_TIME_C

#include "current_time.h"


// int main (){
//   print_current_time_seconds();
//   print_current_time_ns();
//   check_clock_res();
// }

void print_current_time_s(){
  time_t* rawtime = current_time_s();
  struct tm * timeinfo;
  timeinfo = localtime(rawtime);
  printf("%s", asctime(timeinfo) );
}

time_t* current_time_s(){
  time_t* rawtime = (time_t*) calloc(sizeof(time_t), 1);
  time(rawtime);
  return rawtime;
}

void print_current_time_ns(){
  print_current_time_custom(CLOCK_REALTIME);
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
}

struct timespec* current_time_ns_coarse(){
  // For inode purposes, the kernel uses CLOCK_REALTIME_COARSE with function ktime_get_coarse_real_ts64 (previously current_kernel_time)
  // This is less precise than CLOCK_REALTIME but saves time
  return current_time_custom(CLOCK_REALTIME);
}

struct timespec* current_time_ns(){
  return current_time_custom(CLOCK_REALTIME);
}

struct timespec* current_time_custom(int type){
  struct timespec* ts = (struct timespec*) calloc(sizeof(struct timespec), 1);
  
  clock_gettime(type, ts);
  
  return ts;
}

int check_general_clock_res(FILE* csv_file, FILE* output_file, FILE* error_file){
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


int check_general_clock_increments(FILE* csv_file, FILE* output_file, FILE* error_file){
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
                break;
            }
        }
        last_ts = ts;
    }
    
    return result;
}

#endif
