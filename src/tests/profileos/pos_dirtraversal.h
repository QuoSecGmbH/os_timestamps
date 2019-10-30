#ifndef POS_DIRTRAVERSAL_H
#define POS_DIRTRAVERSAL_H

#include "log.h"
#include "current_time.h"
#include "file_ts.h"
#include "misc.h"
#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include "profile.h"

struct profile_info_struct* profileos_dirtraversal_interface(testenv_struct* env);
struct profile_info_struct* profileos_dirtraversal_utilities(testenv_struct* env);
struct profile_info_struct* profileos_dirtraversal_utilities_profileos(testenv_struct* env);


#endif
