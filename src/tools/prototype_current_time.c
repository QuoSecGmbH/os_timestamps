#ifndef PROTOTYPE_CURRENT_TIME_C
#define PROTOTYPE_CURRENT_TIME_C

#include "prototype_current_time.h"


int main (){
  print_current_time_s();
  print_current_time_ns();
  check_general_clock_res(NULL, NULL, NULL);
}


#endif
