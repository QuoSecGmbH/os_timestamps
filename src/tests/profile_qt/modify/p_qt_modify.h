#ifndef POSIX_TIMESTAMPS_P_QT_MODIFY_H
#define POSIX_TIMESTAMPS_P_QT_MODIFY_H

#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <QtCore/QFile>
#include <QtCore/QDebug>
#include <QDir>

extern "C" {
#include "log.h"
#include "current_time.h"
#include "file_ts.h"
#include "misc.h"
#include "profile.h"
};

struct profile_info_struct* profile_gio_modify_file_writeOnly(testenv_struct* env);
struct profile_info_struct* profile_qt_modify_symlink_writeOnly(testenv_struct* env);
struct profile_info_struct* profile_qt_modify_file_append(testenv_struct* env);
struct profile_info_struct* profile_qt_modify_symlink_append(testenv_struct* env);
struct profile_info_struct* profile_qt_modify_file_readWrite(testenv_struct* env);
struct profile_info_struct* profile_qt_modify_symlink_readWrite(testenv_struct* env);

#endif //POSIX_TIMESTAMPS_P_QT_MODIFY_H
