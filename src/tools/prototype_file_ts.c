#ifndef PROTOTYPE_FILE_TS_C
#define PROTOTYPE_FILE_TS_C

#include "prototype_file_ts.h"

int main (int argc, char **argv){
    
  if (argc >= 3){
    print_path_timestamps_lstat_ns(argv[1]);
  }
  else if (argc >= 2){
    print_path_timestamps_ns(argv[1]);
  }
  else {
    printf("ERROR: need one argument (path)\n");
  }
}


#endif
