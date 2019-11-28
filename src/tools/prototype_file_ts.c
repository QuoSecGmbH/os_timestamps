#ifndef PROTOTYPE_FILE_TS_C
#define PROTOTYPE_FILE_TS_C

#include "prototype_file_ts.h"

int main (int argc, char **argv){
    
  if (argc >= 4){
#ifdef __linux__
    printf("%s: (statx AT_SYMLINK_NOFOLLOW)\n", argv[1]);
    print_path_timestamps_statx_ns(argv[1], 0);
#endif
  }
  else if (argc >= 3){
    printf("%s: (lstat + B)\n", argv[1]);
    print_path_timestamps_lstat_ns(argv[1]);
  }
  else if (argc >= 2){
    printf("%s: (stat + B)\n", argv[1]);
    print_path_timestamps_ns(argv[1]);
  }
  else {
    printf("ERROR: need one argument (path)\n");
  }  
}


#endif
