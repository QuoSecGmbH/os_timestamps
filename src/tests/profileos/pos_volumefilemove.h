#ifndef POS_VOLUMEFILEMOVE_H
#define POS_VOLUMEFILEMOVE_H

#include "log.h"
#include "current_time.h"
#include "file_ts.h"
#include "misc.h"
#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include "profile.h"

struct profile_info_struct* profileos_volumefilemove_interface_new(testenv_struct* env);
struct profile_info_struct* profileos_volumefilemove_interface_existing(testenv_struct* env);
struct profile_info_struct* profileos_volumefilemove_interface_dir_new(testenv_struct* env);
struct profile_info_struct* profileos_volumefilemove_interface_dir_existing(testenv_struct* env);

struct profile_info_struct* profileos_volumefilemove_utilities_new(testenv_struct* env);
struct profile_info_struct* profileos_volumefilemove_utilities_existing(testenv_struct* env);
struct profile_info_struct* profileos_volumefilemove_utilities_dir_new(testenv_struct* env);
// struct profile_info_struct* profileos_localfilemove_utilities_dir_existing(testenv_struct* env);

#endif
