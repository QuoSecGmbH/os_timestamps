#ifndef PROFILEOS_H
#define PROFILEOS_H

#include "log.h"
#include "current_time.h"
#include "file_ts.h"
#include "misc.h"
#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include "profile.h"

struct profile_info_struct* profileos_filerename_interface_noreplace(testenv_struct* env);
struct profile_info_struct* profileos_filerename_interface_replace(testenv_struct* env);

#endif
