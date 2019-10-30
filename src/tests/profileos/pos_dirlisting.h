#ifndef POS_DIRLISTING_H
#define POS_DIRLISTING_H

#include "log.h"
#include "current_time.h"
#include "file_ts.h"
#include "misc.h"
#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include "profile.h"

struct profile_info_struct* profileos_dirlisting_interface_notempty(testenv_struct* env);
struct profile_info_struct* profileos_dirlisting_interface_empty(testenv_struct* env);
struct profile_info_struct* profileos_dirlisting_utilities_notempty(testenv_struct* env);
struct profile_info_struct* profileos_dirlisting_utilities_empty(testenv_struct* env);


#endif
