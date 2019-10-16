#ifndef POS_FILERENAME_H
#define POS_FILERENAME_H

#include "log.h"
#include "current_time.h"
#include "file_ts.h"
#include "misc.h"
#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include "profile.h"

struct profile_info_struct* profileos_filerename_interface_new(testenv_struct* env);
struct profile_info_struct* profileos_filerename_interface_existing(testenv_struct* env);
struct profile_info_struct* profileos_filerename_interface_dir_new(testenv_struct* env);
struct profile_info_struct* profileos_filerename_interface_dir_existing(testenv_struct* env);

struct profile_info_struct* profileos_filerename_utilities_new(testenv_struct* env);
struct profile_info_struct* profileos_filerename_utilities_existing(testenv_struct* env);
struct profile_info_struct* profileos_filerename_utilities_dir_new(testenv_struct* env);
// struct profile_info_struct* profileos_filerename_utilities_dir_existing(testenv_struct* env);

#endif
