#ifndef PROTOTYPE_FILE_TS_C
#define PROTOTYPE_FILE_TS_C

#include "prototype_file_ts.h"

int main (int argc, char **argv){
   
    if (argc < 2){
        printf("ERROR: need one argument (path)\n");
        return 1;
    }
  
    char* path = argv[1];
    int mode = 0;
    if (argc >= 3){
        mode = atoi(argv[2]);
    }

    char inode = 0;
    if (argc >= 4){
        if (strcmp(argv[3], "-i") == 0 || strcmp(argv[3], "--print-inode") == 0) inode = 1;
    }

    if (mode == 1){
        print_path_timestamps_csv_ns(argv[1], inode, 1);
    }
    else if (mode == 11){
        print_path_timestamps_csv_ns(argv[1], inode, 0);
    }
    else if (mode == 2){
        printf("%s: (lstat + B)\n", path);
        print_path_timestamps_lstat_ns(path, inode);
    }
    else if (mode == 3){
        #ifdef __linux__
        printf("%s: (statx AT_SYMLINK_NOFOLLOW)\n", argv[1]);
        print_path_timestamps_statx_ns(argv[1], 0, inode);
        #endif
    }
    else if (mode == 4){
        #ifdef __linux__
        printf("%s: (statx AT_SYMLINK_NOFOLLOW (int))\n", argv[1]);
        print_path_timestamps_statx_int_ns(argv[1], 0, inode);
        #endif
    }
    else {
        printf("%s: (stat + B)\n", path);
        print_path_timestamps_ns(path, inode);
    }
}


#endif
