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
#include "i_utimes.h"
#include "i_utime.h"
#include "i_file.h"
#include "i_fopen.h"

#include "i_file_w.h"
#include "i_file_w_fprintf.h"
#include "i_file_w_printf.h"
#include "i_file_w_fputc.h"
#include "i_file_w_fputs.h"
#include "i_file_w_fputwc.h"
#include "i_file_w_fputws.h"
#include "i_file_w_fwprintf.h"
#include "i_file_w_wprintf.h"
#include "i_file_w_fwrite.h"
#include "i_file_w_puts.h"

#include "i_file_r.h"
#include "i_file_r_fread.h"
#include "i_file_r_fgetc.h"
#include "i_file_r_getc.h"
#include "i_file_r_fgets.h"
#include "i_file_r_gets.h"
#include "i_file_r_getchar.h"
#include "i_file_r_getdelim.h"
#include "i_file_r_getline.h"
#include "i_file_r_fscanf.h"
#include "i_file_r_scanf.h"
#include "i_file_r_fwscanf.h"
#include "i_file_r_wscanf.h"

#include "i_file_new.h"
#include "i_file_ln.h"



int check_interfaces_exec_execvp(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_exec_execvp_local(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_attr_chmod(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_attr_chown_grp(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_attr_chown_usr(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_attr_chown_grp_usr(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_attr_chown_nochange(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
#endif
