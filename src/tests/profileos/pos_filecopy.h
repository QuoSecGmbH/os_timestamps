#ifndef POS_FILECOPY_H
#define POS_FILECOPY_H

#include "log.h"
#include "current_time.h"
#include "file_ts.h"
#include "misc.h"
#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include "profile.h"

struct profile_info_struct* profileos_filecopy_interface_new(testenv_struct* env);
struct profile_info_struct* profileos_filecopy_interface_existing(testenv_struct* env);
struct profile_info_struct* profileos_volumefilecopy_interface_new(testenv_struct* env);
struct profile_info_struct* profileos_volumefilecopy_interface_existing(testenv_struct* env);
// struct profile_info_struct* profileos_filecopy_interface_dir_new(testenv_struct* env);
// struct profile_info_struct* profileos_filecopy_interface_dir_existing(testenv_struct* env);

struct profile_info_struct* profileos_filecopy_utilities_new(testenv_struct* env);
struct profile_info_struct* profileos_filecopy_utilities_existing(testenv_struct* env);
struct profile_info_struct* profileos_filecopy_utilities_dir_new_notempty(testenv_struct* env);
struct profile_info_struct* profileos_filecopy_utilities_dir_new_empty(testenv_struct* env);
struct profile_info_struct* profileos_volumefilecopy_utilities_new(testenv_struct* env);
struct profile_info_struct* profileos_volumefilecopy_utilities_existing(testenv_struct* env);
struct profile_info_struct* profileos_volumefilecopy_utilities_dir_new_notempty(testenv_struct* env);
struct profile_info_struct* profileos_volumefilecopy_utilities_dir_new_empty(testenv_struct* env);
// struct profile_info_struct* profileos_filecopy_utilities_dir_existing(testenv_struct* env);

#endif
