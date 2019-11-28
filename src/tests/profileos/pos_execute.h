#ifndef POS_EXECUTE_H
#define POS_EXECUTE_H

#include "log.h"
#include "current_time.h"
#include "file_ts.h"
#include "misc.h"
#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include "profile.h"

struct profile_info_struct* profileos_execute_system_interface(testenv_struct* env);
struct profile_info_struct* profileos_execute_system_utilities(testenv_struct* env);
struct profile_info_struct* profileos_execute_local_interface(testenv_struct* env);
struct profile_info_struct* profileos_execute_local_interface_symlink(testenv_struct* env);
struct profile_info_struct* profileos_execute_local_interface_intosymlinkdir(testenv_struct* env);
struct profile_info_struct* profileos_execute_local_utilities(testenv_struct* env);
struct profile_info_struct* profileos_execute_local_utilities_symlink(testenv_struct* env);
struct profile_info_struct* profileos_execute_local_utilities_intosymlinkdir(testenv_struct* env);


#endif
