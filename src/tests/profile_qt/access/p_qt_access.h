#ifndef POSIX_TIMESTAMPS_P_QT_ACCESS_H
#define POSIX_TIMESTAMPS_P_QT_ACCESS_H

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

struct profile_info_struct* profile_qt_access_file_readOnly(testenv_struct* env);
struct profile_info_struct* profile_qt_access_file_readWrite(testenv_struct* env);
struct profile_info_struct* profile_qt_access_symlink_readOnly(testenv_struct* env);
struct profile_info_struct* profile_qt_access_symlink_readWrite(testenv_struct* env);

#endif //POSIX_TIMESTAMPS_P_QT_ACCESS_H
