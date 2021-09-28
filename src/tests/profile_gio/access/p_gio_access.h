#ifndef POSIX_TIMESTAMPS_P_GIO_ACCESS_H
#define POSIX_TIMESTAMPS_P_GIO_ACCESS_H

#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <glib.h>
#include <gio/gio.h>

#include "log.h"
#include "current_time.h"
#include "file_ts.h"
#include "misc.h"
#include "profile.h"

struct profile_info_struct* profile_gio_access_file(testenv_struct* env);
struct profile_info_struct* profile_gio_access_symlink(testenv_struct* env);


#endif //POSIX_TIMESTAMPS_P_GIO_ACCESS_H
