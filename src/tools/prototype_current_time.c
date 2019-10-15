#ifndef PROTOTYPE_CURRENT_TIME_C
#define PROTOTYPE_CURRENT_TIME_C

#include "prototype_current_time.h"


int main (int argc, char **argv){
  if (argc >= 3){
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
