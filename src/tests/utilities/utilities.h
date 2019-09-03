#ifndef UTILITIES_H
#define UTILITIES_H

#include "log.h"
#include "current_time.h"
#include "file_ts.h"
#include "misc.h"
#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include "profile.h"

#include "u_cp.h"
#include "u_new_touch.h"
#include "u_new_mkdir.h"
#include "u_new_mkfifo.h"
#include "u_mv.h"
#include "u_rm_rm.h"
#include "u_rm_rmdir.h"
#include "u_rm_unlink.h"
#include "u_ln.h"
#include "u_ls.h"
#include "u_vi.h"
#include "u_ed.h"
#include "u_ex.h"

int check_utilities_attr_chmod_new(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_utilities_attr_chmod_same(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);

#endif
