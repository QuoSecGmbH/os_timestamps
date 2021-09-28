#ifndef POSIX_TIMESTAMPS_P_GIO_COPY_H
#define POSIX_TIMESTAMPS_P_GIO_COPY_H

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

struct profile_info_struct* profile_gio_copy_file_new(testenv_struct* env);
struct profile_info_struct* profile_gio_copy_file_existing(testenv_struct* env);
struct profile_info_struct* profile_gio_copy_file_after_deleting(testenv_struct* env);

#endif //POSIX_TIMESTAMPS_P_GIO_COPY_H
