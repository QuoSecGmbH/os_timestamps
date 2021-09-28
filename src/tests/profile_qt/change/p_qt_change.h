#ifndef POSIX_TIMESTAMPS_P_QT_CHANGE_H
#define POSIX_TIMESTAMPS_P_QT_CHANGE_H

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

struct profile_info_struct* profile_qt_change_chmod_file(testenv_struct* env);
struct profile_info_struct* profile_qt_change_chmod_symlink(testenv_struct* env);
struct profile_info_struct* profile_qt_change_chmod_dir(testenv_struct* env);

#endif //POSIX_TIMESTAMPS_P_QT_CHANGE_H
