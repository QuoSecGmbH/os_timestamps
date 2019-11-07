#ifndef POS_FILECHANGE_H
#define POS_FILECHANGE_H

#include "log.h"
#include "current_time.h"
#include "file_ts.h"
#include "misc.h"
#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include "profile.h"


struct profile_info_struct* profileos_filechange_interface_chmod(testenv_struct* env);
struct profile_info_struct* profileos_filechange_interface_chown(testenv_struct* env);
struct profile_info_struct* profileos_filechange_utilities_chmod(testenv_struct* env);
struct profile_info_struct* profileos_filechange_utilities_chown(testenv_struct* env);

struct profile_info_struct* profileos_filechange_interface_chmod_symlink(testenv_struct* env);
struct profile_info_struct* profileos_filechange_interface_chown_symlink(testenv_struct* env);
struct profile_info_struct* profileos_filechange_utilities_chmod_symlink(testenv_struct* env);
struct profile_info_struct* profileos_filechange_utilities_chown_symlink(testenv_struct* env);

struct profile_info_struct* profileos_filechange_interface_chmod_dir(testenv_struct* env);
struct profile_info_struct* profileos_filechange_interface_chown_dir(testenv_struct* env);
struct profile_info_struct* profileos_filechange_utilities_chmod_dir(testenv_struct* env);
struct profile_info_struct* profileos_filechange_utilities_chown_dir(testenv_struct* env);

#endif
