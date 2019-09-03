#ifndef U_ED_H
#define U_ED_H

#include "log.h"
#include "current_time.h"
#include "file_ts.h"
#include "misc.h"
#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include "profile.h"

int check_utilities_ed_new_i_w_q(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_utilities_ed_new_i_w_q_mac(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_utilities_ed_existing_i_w_q(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_utilities_ed_existing_i_w_q_mc(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_utilities_ed_existing_i_wq(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_utilities_ed_existing_i_wq_mc(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_utilities_ed_existing_i_Q(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);

#endif
