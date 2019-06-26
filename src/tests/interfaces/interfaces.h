#ifndef INTERFACES_H
#define INTERFACES_H

#include "log.h"
#include "current_time.h"
#include "file_ts.h"
#include "misc.h"
#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

#include "i_futimens.h"
#include "i_utimensat.h"

int check_interfaces_exec_execvp(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_exec_execvp_local(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_attr_chmod(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_attr_chown_grp(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_attr_chown_usr(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_attr_chown_grp_usr(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_attr_chown_nochange(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
#endif
