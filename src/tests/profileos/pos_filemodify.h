#ifndef POS_FILEMODIFY_H
#define POS_FILEMODIFY_H

#include "log.h"
#include "current_time.h"
#include "file_ts.h"
#include "misc.h"
#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include "profile.h"

struct profile_info_struct* profileos_filemodify_interface_wb(testenv_struct* env);
struct profile_info_struct* profileos_filemodify_interface_rp(testenv_struct* env);
struct profile_info_struct* profileos_filemodify_interface_a(testenv_struct* env);
struct profile_info_struct* profileos_filemodify_utilities(testenv_struct* env);

struct profile_info_struct* profileos_filemodify_interface_wb_symlink(testenv_struct* env);
struct profile_info_struct* profileos_filemodify_interface_rp_symlink(testenv_struct* env);
struct profile_info_struct* profileos_filemodify_interface_a_symlink(testenv_struct* env);
struct profile_info_struct* profileos_filemodify_utilities_symlink(testenv_struct* env);
#endif
