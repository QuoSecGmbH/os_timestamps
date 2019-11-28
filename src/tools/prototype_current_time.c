#ifndef PROTOTYPE_CURRENT_TIME_C
#define PROTOTYPE_CURRENT_TIME_C

#include "prototype_current_time.h"


int main (int argc, char **argv){
  if (argc >= 3){
    current_time_setup_local_timemarker(stdout, stderr);
    current_time_setup_local_timemarkerdir(stdout, stderr);
    print_current_time_ns_fslike_osspecific();
  }
  else if (argc >= 2){
    int type = atoi(argv[1]);
    print_current_time_custom(type);
  }
  else {
    print_current_time_ns();
  }
  
}


#endif
