#ifndef U_NEW_MKDIR_H
#define U_NEW_MKDIR_H

#include "log.h"
#include "current_time.h"
#include "file_ts.h"
#include "misc.h"
#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include "profile.h"

int check_utilities_new_mkdir_new(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_utilities_new_mkdir_new_mac(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_utilities_new_mkdir_existing(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);

#endif
