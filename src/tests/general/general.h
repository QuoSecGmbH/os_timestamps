#ifndef GENERAL_H
#define GENERAL_H

#include "log.h"
#include "current_time.h"
#include "file_ts.h"
#include "misc.h"

int check_general_new_file(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_general_new_file_mac_eq(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);

#endif
