#ifndef POS_FILECREATION_H
#define POS_FILECREATION_H

#include "log.h"
#include "current_time.h"
#include "file_ts.h"
#include "misc.h"
#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include "profile.h"

struct profile_info_struct* profileos_filecreation_interface(testenv_struct* env);
struct profile_info_struct* profileos_filecreation_interface_newhardlink(testenv_struct* env);
struct profile_info_struct* profileos_filecreation_interface_dir(testenv_struct* env);

struct profile_info_struct* profileos_filecreation_interface_intosymlinkdir(testenv_struct* env);
struct profile_info_struct* profileos_filecreation_interface_symlink(testenv_struct* env);
struct profile_info_struct* profileos_filecreation_interface_symlink_dir(testenv_struct* env);

struct profile_info_struct* profileos_filecreation_utilities(testenv_struct* env);
struct profile_info_struct* profileos_filecreation_utilities_newhardlink(testenv_struct* env);
struct profile_info_struct* profileos_filecreation_utilities_dir(testenv_struct* env);

struct profile_info_struct* profileos_filecreation_utilities_intosymlinkdir(testenv_struct* env);
struct profile_info_struct* profileos_filecreation_utilities_symlink(testenv_struct* env);
struct profile_info_struct* profileos_filecreation_utilities_symlink_dir(testenv_struct* env);

#endif
