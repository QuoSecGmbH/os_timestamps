#ifndef POS_FILEACCESS_H
#define POS_FILEACCESS_H

#include "log.h"
#include "current_time.h"
#include "file_ts.h"
#include "misc.h"
#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include "profile.h"

struct profile_info_struct* profileos_fileaccess_interface(testenv_struct* env);
struct profile_info_struct* profileos_fileaccess_interface_symlink(testenv_struct* env);
struct profile_info_struct* profileos_fileaccess_utilities(testenv_struct* env);
struct profile_info_struct* profileos_fileaccess_utilities_symlink(testenv_struct* env);

struct profile_info_struct* profileos_symlink_readlink_interface(testenv_struct* env);
struct profile_info_struct* profileos_symlink_readlink_interface_dir(testenv_struct* env);
struct profile_info_struct* profileos_symlink_readlink_utilities(testenv_struct* env);
struct profile_info_struct* profileos_symlink_readlink_utilities_dir(testenv_struct* env);


#endif
