#ifndef POSIX_TIMESTAMPS_P_GIO_CHANGE_H
#define POSIX_TIMESTAMPS_P_GIO_CHANGE_H

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

struct profile_info_struct* profile_gio_change_chmod_file(testenv_struct* env);
struct profile_info_struct* profile_gio_change_chown_file(testenv_struct* env);

struct profile_info_struct* profile_gio_change_chmod_symlink(testenv_struct* env);
struct profile_info_struct* profile_gio_change_chown_symlink(testenv_struct* env);

struct profile_info_struct* profile_gio_change_chmod_symlink_notFollow(testenv_struct* env);
struct profile_info_struct* profile_gio_change_chown_symlink_notFollow(testenv_struct* env);

struct profile_info_struct* profile_gio_change_chmod_dir(testenv_struct* env);
struct profile_info_struct* profile_gio_change_chown_dir(testenv_struct* env);

#endif //POSIX_TIMESTAMPS_P_GIO_CHANGE_H
