#ifndef PROTOTYPE_STD_TS_C
#define PROTOTYPE_STD_TS_C

#include "prototype_std_ts.h"

int main (int argc, char **argv){
  if (argc == 5){
    print_file_timestamps_ns(stdout);
    printf("stdout\n---\n");
    print_file_timestamps_ns(stderr);
    printf("stderr\n");
    printf("---\n");
    print_file_timestamps_ns(stdin);
    printf("stdin\n");
  }
  else if (argc == 4){
    print_file_timestamps_ns(stdin);
    printf("stdin\n");
  }
  else if (argc == 3){
    print_file_timestamps_ns(stderr);
    printf("stderr\n");
  }
  else if (argc == 2){
    print_file_timestamps_ns(stdout);
    printf("stdout\n");
  }
  else {
    printf("ERROR: need arguments (1 arg - stdout, 2 args - stderr, 3 args - stdin, 4 args - stdout+stderr+stdin)\n");
  }
}


#endif
