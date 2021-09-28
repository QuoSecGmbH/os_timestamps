#ifndef POSIX_TIMESTAMPS_P_QT_RENAME_H
#define POSIX_TIMESTAMPS_P_QT_RENAME_H

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

struct profile_info_struct* profile_qt_rename_directory_new(testenv_struct* env);
struct profile_info_struct* profile_qt_rename_file_new(testenv_struct* env);

#endif //POSIX_TIMESTAMPS_P_QT_RENAME_H
